/**
 * @file CSB.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Implementation of CSB scheme
 * 
 * Based on:
 *   A. Buluç, J. T. Fineman, M. Frigo, J. R. Gilbert, and C. E. Leiserson. Parallel
 *   sparse matrix-vector and matrix-transpose-vector multiplication using compressed sparse blocks. 
 *   In Proceedings of the Twenty-First Annual Symposium
 *   on Parallelism in Algorithms and Architectures, SPAA ’09, pages 233–244, New
 *   York, NY, USA, 2009. Association for Computing Machinery.
 * 
 * TODO: Make blocksize dependent on matrix: only initial implementation for now
 * TODO: Avoid first touch
 * TODO: Check what the O_DIM_CONST should be
 */


#ifndef PWM_CSB_HPP
#define PWM_CSB_HPP

#define O_DIM_CONST 3
#define O_BETA_CONST 3

#include <cassert>
#include <algorithm>
#include <cmath>

#include "../Matrix/SparseMatrix.hpp"

#include "../Util/VectorUtill.hpp"
#include "../Util/Math.hpp"
#include "../Util/TripletToCRS.hpp"

typedef uint32_t compress_t;
typedef uint16_t index_t;

#define LOW_BITMASK  0b00000000000000001111111111111111
#define HIGH_BITMASK 0b11111111111111110000000000000000
#define COORD_BITS 16

namespace pwm {
    template<typename T, typename int_type>
    class CSB: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Array of compressed indices, highest 16 bits correspond to the row and the lowest 16 bits to the column
            compress_t* ind;

            // Values corresponding to row and column indices
            T* data;

            // Pointer to the start of each block
            int_type* blk_ptr;

            // Amount of horizontal blocks
            int_type horizontal_blocks;

            // Amount of vertical blocks
            int_type vertical_blocks;

            // Amount of threads to be used
            int threads;

            // Blocksize
            int_type beta;

            // Amount of bits for block indices
            int_type block_bits;

        private:
            /**
             * @brief Transforms compressed index to the corresponding row index
             * 
             * @param input Compressed input parameter
             * @return index_t Corresponding row index
             */
            inline index_t fromCompressedToRow(const compress_t input) {
                return (index_t)((input & HIGH_BITMASK) >> COORD_BITS);
            }

            /**
             * @brief Transforms compressed index to the corresponding column index
             * 
             * @param input Compressed input parameter
             * @return index_t Corresponding column index
             */
            inline index_t fromCompressedToCol(const compress_t input) {
                return (index_t)(input & LOW_BITMASK);
            }
            
            /**
             * @brief Transforms row and column index to compressed index
             * 
             * @param row Row index to be compressed
             * @param col Column index to be compressed
             * @return compress_t Compressed integer
             */
            inline compress_t fromIndicesToCompressed(const index_t row, const index_t col) {
                return ((compress_t)row << COORD_BITS) | (compress_t)col;
            }

            /**
             * @brief Sets the blocksize and block bits for the imported matrix
             */
            void setBlockSizeParam() {
                int_type minimal_size = std::min(this->nor, this->noc);

                // Maximum of 16 is specified because row and column indices are stored as uint16_t
                block_bits = std::min<int_type>(16, (int_type)(std::ceil(std::log2(std::sqrt((double)minimal_size)))));
                beta = (int_type)(std::pow(2, block_bits));
            }

            /**
             * @brief Transforms block coordinate to index for blk_ptr array
             * 
             * @param block_row Row index of block
             * @param block_column Column index of block
             * @return int_type index of given block in blk_ptr array
             */
            inline int_type blockCoordToIndex(const int_type block_row, const int_type block_column) {
                assert(0 <= block_row);
                assert(block_row < vertical_blocks);
                assert(0 <= block_column);
                assert(block_column < horizontal_blocks);

                return block_row*vertical_blocks + block_column;
            }

            /**
             * @brief Compares 2 coordinates to obtain a Z-Morton ordering
             * 
             * For now we expect that the int_type is an unsigned type
             * 
             * Z-Morton ordering is equal to sorting the bit-interleaved pattern y(k) x(k) y(k-1) x(k-1) ... y(0) x(0):
             * So we first check if the first "needed" bit of y, then the one of x.
             * This is done until we find a discrepancy between both values
             * 
             * @param x1 X-coord of first element
             * @param y1 Y-coord of first element
             * @param x2 X-coord of second element
             * @param y2 Y-coord of second element
             * @return true if the first element is smaller than or equal to the second element
             * @return false if the first element is larger than the second element
             */
            bool zMortonCompare(const index_t x1, const index_t y1, const index_t x2, const index_t y2) {
                bool set_1, set_2;
                for (int bit_nb = block_bits-1; bit_nb >= 0; --bit_nb) {
                    // Check y bit
                    set_1 = (y1 >> bit_nb) & 1;
                    set_2 = (y2 >> bit_nb) & 1;

                    if (set_2 && !set_1) { // 1 < 2
                        return true;
                    } else if (set_1 && !set_2) { // 1 > 2
                        return false;
                    }

                    // Check x bit
                    set_1 = (x1 >> bit_nb) & 1;
                    set_2 = (x2 >> bit_nb) & 1;

                    if (set_2 && !set_1) { // 1 < 2
                        return true;
                    } else if (set_1 && !set_2) { // 1 > 2
                        return false;
                    }
                }

                // 1 == 2
                return true;
            }

            /**
             * @brief Partition function of quicksort
             * 
             * @param coords Array which contains 2 pointers, pointing to the column and row indices respectively
             * @param data data of the block which needs to be partitioned
             * @param low Starting index of data
             * @param high Ending index of data
             * @return int_type Returns partitioning point
             */
            int_type partitionBlock(compress_t* coords, std::vector<T>& data, int_type low, int_type high) {
                // Select pivot (rightmost element)
                index_t pivotRow = fromCompressedToRow(coords[high]);
                index_t pivotCol = fromCompressedToCol(coords[high]);

                // Points to biggest element
                int_type i = low;
                for (int j = low; j < high; ++j) {
                    if (zMortonCompare(fromCompressedToCol(coords[j]), fromCompressedToRow(coords[j]), pivotCol, pivotRow)) {
                        // If element is smaller than pivot swap it with i+1
                        pwm::swapArrayElems<T, compress_t, int_type>(coords, data, i, j);
                        i++;
                    }
                }

                // Swap pivot with the greatest element at i+1
                pwm::swapArrayElems<T, compress_t, int_type>(coords, data, i, high);

                // return the partitioning point
                return i;
            }

            /**
             * @brief Sorts the given block using Z-Morton ordering
             * 
             * Makes use of quicksort implementation (see sortOnCoord in Util/TripletToCRS.hpp)
             * 
             * @param coords Array consisting of 2 pointers, pointing to the column and row indices respectively
             * @param data data of given block indices
             * @param low starting index of data to be sorted
             * @param high ending index of data to be sorted
             */
            void sortBlock(compress_t* coords, std::vector<T>& data, int_type low, int_type high) {
                if (low < high) {
                    // Random permutation of rightmost element
                    pwm::swapArrayElems<T, compress_t, int_type>(coords, data, (((int_type)rand()) % (high-low)) + low, high); 
                    int_type middle = partitionBlock(coords, data, low, high);

                    if (middle > 0) {
                        sortBlock(coords, data, low, middle - 1);
                    }
                    sortBlock(coords, data, middle + 1, high);
                }
            }

            /**
             * @brief Binary search for the division point as explained in row
             * 
             * @param dim dimension of the original matrix
             * @param start starting index for binary search
             * @param end ending index for binary search
             * @return int_type smallest index s for which (indices[s] & dim/2) != 0
             */
            int_type binarySearchDivisionPointRow(const int_type half_dim, int_type start, int_type end) {
                while (start < end) {
                    int_type middle = (start+end)/2;
                    
                    index_t middle_index = fromCompressedToRow(ind[middle]);
                    if ((middle_index & (index_t)half_dim) == 0) {
                        start = middle + 1;
                    } else {
                        end = middle;
                    }
                }

                return start;
            }

            /**
             * @brief Binary search for the division point in column
             * 
             * @param dim dimension of the original matrix
             * @param start starting index for binary search
             * @param end ending index for binary search
             * @return int_type smallest index s for which (indices[s] & dim/2) != 0
             */
            int_type binarySearchDivisionPointColumn(const int_type half_dim, int_type start, int_type end) {
                while (start < end) {
                    int_type middle = (start+end)/2;
                    
                    index_t middle_index = fromCompressedToCol(ind[middle]);
                    if ((middle_index & (index_t)half_dim) == 0) {
                        start = middle + 1;
                    } else {
                        end = middle;
                    }
                }

                return start;
            }

            /**
             * @brief Multiply dense subblock with input vector by performing a splitting of the block if there are too many nonzeros
             * 
             * @param start Starting index of data in matrix
             * @param end Ending index of data in matrix
             * @param dim Dimension of subblock
             * @param x Part of input vector corresponding to the given block
             * @param y Part of output vector corresponding to the given block
             */
            void blockMult(const int_type start, const int_type end, const int_type dim, const T* x, T* y) {              
                assert(end >= start);

                index_t row_ind, col_ind;

                // Perform serial computation if there are not too many nonzeros
                if (end - start <= dim*O_DIM_CONST) {
                    for (int_type i = start; i <= end; ++i) {
                        row_ind = fromCompressedToRow(ind[i]);
                        col_ind = fromCompressedToCol(ind[i]);
                        y[row_ind] = y[row_ind] + data[i]*x[col_ind];
                    }

                    return;
                }

                // There are too much nonzeros so we do a recursive subdivision (M00, M01, M10, M11)
                index_t half_dim = dim / 2;

                // Calculate splitting points
                int_type s2 = binarySearchDivisionPointRow(half_dim, start, end); // Split between M00, M01 and M10, M11
                int_type s1 = binarySearchDivisionPointColumn(half_dim, start, s2-1); // Split between M00 and M01
                int_type s3 = binarySearchDivisionPointColumn(half_dim, s2, end); // Split between M10 and M11

                #pragma omp parallel
                #pragma omp single nowait
                {
                    #pragma omp taskgroup
                    {
                        #pragma omp task
                        if (s1-1 >= start) blockMult(start, s1-1, half_dim, x, y); // M00

                        #pragma omp task
                        if (end >= s3) blockMult(s3, end, half_dim, x, y); // M11
                    }
                    
                    #pragma omp task
                    if (s2-1 >= s1) blockMult(s1, s2-1, half_dim, x, y); // M01

                    #pragma omp task
                    if (s3-1 >= s2) blockMult(s2, s3-1, half_dim, x, y); // M10
                }
            }

            /**
             * @brief Multiply sparse block row
             * 
             * @param block_row Block row index
             * @param block_column_start Column index of first block to be multiplied
             * @param block_column_end Column index of last block to be multiplied
             * @param x Input vector
             * @param y Part of output vector corresponding to the current block row
             */
            void sparseRowMult(const int_type block_row, const int_type block_column_start, const int_type block_column_end, const T* x, T* y) {
                int_type first_block_index = blockCoordToIndex(block_row, block_column_start);
                int_type am_blocks = (block_column_end - block_column_start)+1;
                int_type block_index, x_offset;

                index_t row_ind, col_ind;
                for (int_type block_nb = 0; block_nb < am_blocks; ++block_nb) {
                    block_index = first_block_index + block_nb;
                    x_offset = block_nb*beta;

                    for (int_type i = blk_ptr[block_index]; i < blk_ptr[block_index+1]; ++i) {
                        row_ind = fromCompressedToRow(ind[i]);
                        col_ind = fromCompressedToCol(ind[i]);
                        y[row_ind] = y[row_ind] + data[i]*x[x_offset + col_ind];
                    }
                }
            }
            
            /**
             * @brief Multiplies a chunk of a blockrow or subdivides a blockrow if it contains more than 1 chunk
             * 
             * @param block_row_index Index of the given blockrow
             * @param chunks Array which indicates the different chunks in the current blockrow
             * @param chunks_length Length of chunks array
             * @param x Input vector
             * @param y Output vector corresponding to the given blockrow
             */
            void blockRowMult(const int_type block_row, const int* chunks, const int_type chunks_length, const T* x, T* y) {
                // Check if the blockrow is a single chunk
                if (chunks_length == 2) {
                    int_type left_chunk = chunks[0]+1;
                    int_type right_chunk = chunks[1];

                    if (left_chunk == right_chunk) {
                        // Chunk is a single block
                        int_type block_index = blockCoordToIndex(block_row, left_chunk);
                        int_type start = blk_ptr[block_index];
                        int_type end = blk_ptr[block_index+1]-1;

                        blockMult(start, end, beta, x, y);
                    } else {
                        // The chunk consists of multiple blocks and thus is sparse
                        sparseRowMult(block_row, left_chunk, right_chunk, x, y);
                    }
                                        
                    return;
                }
                
                #pragma omp parallel
                #pragma omp single nowait
                {
                    // Blockrow contains multiple chunks thus we subdivide
                    int_type middle = integerCeil<int_type>(chunks_length, 2) - 1; // Middle chunk index
                    int_type x_middle = beta*(chunks[middle] - chunks[0]); // Middle of x vector

                    // Initialize vector for temporary results
                    T* temp_res = new T[beta];
                    std::fill(temp_res, temp_res+beta, 0.);

                    #pragma omp taskgroup
                    {
                        #pragma omp task
                        blockRowMult(block_row, chunks, middle+1, x, y);

                        #pragma omp task
                        blockRowMult(block_row, chunks+middle, chunks_length-middle, x+x_middle, temp_res);
                    }
                        
                    // Add temporary result serially
                    for (int_type i = 0; i < beta; ++i) {
                        y[i] = y[i] + temp_res[i];
                    }

                    delete [] temp_res;
                }
            }

        public:
            // Base constructor
            CSB() {}

            // Base constructor
            CSB(int threads): threads(threads) {}

            /**
             * @brief Input the CSB matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partitions_am) {
                omp_set_num_threads(threads);

                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;

                setBlockSizeParam();

                horizontal_blocks = pwm::integerCeil<int_type>(this->noc, beta);
                vertical_blocks = pwm::integerCeil<int_type>(this->nor, beta);

                ind = new compress_t[this->nnz];
                data = new T[this->nnz];
                blk_ptr = new int_type[horizontal_blocks*vertical_blocks+1];
                blk_ptr[0] = 0;

                // Sort triplets on row value
                int_type** coords = new int_type*[2];
                coords[0] = input.row_coord;
                coords[1] = input.col_coord;
                sortOnCoord<T, int_type>(coords, input.data, 2, 0, this->nnz-1);
                delete [] coords;

                // Generate CSB structure per block row
                int_type triplet_index = 0;
                int_type csb_index = 0;
                int_type blk_ptr_index = 1;

                // Data structures which keep track of indices and data in each block
                std::vector<std::vector<compress_t>> block_ind(horizontal_blocks);
                std::vector<std::vector<T>> block_data(horizontal_blocks);
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    std::fill(block_ind.begin(), block_ind.end(), std::vector<compress_t>());
                    std::fill(block_data.begin(), block_data.end(), std::vector<T>());

                    // Loop over all indices in triplet structure which are part of this block row
                    while (triplet_index < this->nnz && input.row_coord[triplet_index] < (block_row+1)*beta) {
                        int_type block_index = input.col_coord[triplet_index] / beta;

                        compress_t index = fromIndicesToCompressed(input.row_coord[triplet_index] % beta, input.col_coord[triplet_index] % beta);
                        block_ind[block_index].push_back(index);
                        block_data[block_index].push_back(input.data[triplet_index]);

                        triplet_index++;
                    }

                    // Sort blocks in Morton-Z order
                    for (int_type block_column = 0; block_column < horizontal_blocks; ++block_column) {
                        if (block_ind[block_column].size() > 0) {
                            sortBlock(block_ind[block_column].data(), block_data[block_column], 0, block_ind[block_column].size()-1);
                        }                        
                    }

                    // Initialize CSB datastructures
                    for (int_type block_col = 0; block_col < horizontal_blocks; ++block_col) {
                        for (size_t i = 0; i < block_ind[block_col].size(); ++i) {
                            ind[csb_index] = block_ind[block_col][i];
                            data[csb_index] = block_data[block_col][i];

                            csb_index++;
                        }

                        blk_ptr[blk_ptr_index] = csb_index;
                        blk_ptr_index++;
                    }
                }
            }

            /**
             * @brief Input the CSB matrix as a poisson matrix
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             * @param partitions Not used
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                // This is a quick and dirty way
                pwm::Triplet<T, int_type> temp_mat;
                temp_mat.generatePoisson(m, n);

                loadFromTriplets(temp_mat, partitions);
            }

            /**
             * @brief Sparse matrix vector product calculation
             * 
             * Uses work-stealing scheduling of TBB
             * Tasks are block rows which can be split up as described in the CSB paper
             * 
             * @param x Vector to be multiplied with the matrix
             * @param y Result vector
             */
            void mv(const T* x, T* y) {
                std::fill(y, y+this->nor, 0.);

                #pragma omp parallel
                #pragma omp single
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    #pragma omp task
                    {
                        int* chunks = new int[horizontal_blocks]; // Worst case that all blocks are a separate chunk
                        int_type chunk_index = 0;
                        chunks[chunk_index++] = -1;

                        int_type first_block_index = blockCoordToIndex(block_row, 0);

                        int_type count = 0;
                        for (int_type block_col = 0; block_col <= horizontal_blocks - 2; ++block_col) {
                            // Add elements of current block to count
                            count = count + blk_ptr[first_block_index+block_col+1]-blk_ptr[first_block_index+block_col];

                            // Check if next block will exceed the maximum number of nz
                            if (count + blk_ptr[first_block_index+block_col+2]-blk_ptr[first_block_index+block_col+1] > beta*O_BETA_CONST) {
                                chunks[chunk_index++] = block_col;
                                count = 0;
                            }
                        }

                        // Add last block to end the last chunk
                        chunks[chunk_index++] = horizontal_blocks-1; 

                        // Perform block row multiplication
                        blockRowMult(block_row, chunks, chunk_index, x, y+block_row*beta);

                        delete [] chunks;
                    }
                }
            }

            /**
             * @brief Power method
             * 
             * @param x Input vector to start power method
             * @param it Amount of iterations
             * @return T* Resulting vector
             */
            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int i = 0; i < it; ++i) {
                    if (i % 2 == 0) {
                        this->mv(x,y);
                        pwm::normalize(y, this->nor);
                    } else {
                        this->mv(y,x);
                        pwm::normalize(x, this->nor);
                    }
                }
            }
    };
} // namespace pwm


#endif // PWM_CSB_HPP