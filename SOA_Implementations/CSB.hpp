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
 */


#ifndef PWM_CSB_HPP
#define PWM_CSB_HPP

#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdint>

#include "../Matrix/SparseMatrix.hpp"

#include "../Util/VectorUtill.hpp"
#include "../Util/Math.hpp"
#include "../Util/TripletToCRS.hpp"
#include "../Util/Constants.hpp"

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

            // If the matrix has balanced blockrows we can provide a further optimization (see mv)
            bool balanced_block_rows;

        private:
            /**
             * @brief Transforms compressed index to the corresponding row index
             * 
             * @param input Compressed input parameter
             * @return compress_index_t Corresponding row index
             */
            inline compress_index_t fromCompressedToRow(const compress_t input) {
                return (compress_index_t)((input & HIGH_BITMASK) >> COORD_BITS);
            }

            /**
             * @brief Transforms compressed index to the corresponding column index
             * 
             * @param input Compressed input parameter
             * @return compress_index_t Corresponding column index
             */
            inline compress_index_t fromCompressedToCol(const compress_t input) {
                return (compress_index_t)(input & LOW_BITMASK);
            }
            
            /**
             * @brief Transforms row and column index to compressed index
             * 
             * @param row Row index to be compressed
             * @param col Column index to be compressed
             * @return compress_t Compressed integer
             */
            inline compress_t fromIndicesToCompressed(const compress_index_t row, const compress_index_t col) {
                return ((compress_t)row << COORD_BITS) | (compress_t)col;
            }

            /**
             * @brief Sets the blocksize and block bits for the imported matrix
             */
            void setBlockSizeParam() {
                const int_type minimal_size = std::min(this->nor, this->noc);

                // Maximum of 16 is specified because row and column indices should fit in 4 bytes
                const int_type lg_sqrt_size = (int_type)(std::ceil(std::log2(std::sqrt((double)minimal_size))));
                block_bits = std::min<int_type>(16, 3+lg_sqrt_size);
                beta = (int_type)(std::pow(2, block_bits));

                while (block_bits > lg_sqrt_size) {
                    // Check if x and y fit in the L2 cache per block
                    if (sizeof(T)*CHAR_BIT*beta*2 > L2_CACHE_SIZE_MB*L2_CACHE_MULT*1e6*8) {
                        block_bits -= 1;
                        beta = (int_type)(std::pow(2, block_bits));
                    } else {
                        break;
                    }
                }
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
            bool zMortonCompare(const compress_index_t x1, const compress_index_t y1, const compress_index_t x2, const compress_index_t y2) {
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
            int_type partitionBlock(compress_t* coords, std::vector<T>& data, const int_type low, const int_type high) {
                // Select pivot (rightmost element)
                compress_index_t pivotRow = fromCompressedToRow(coords[high]);
                compress_index_t pivotCol = fromCompressedToCol(coords[high]);

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
            void sortBlock(compress_t* coords, std::vector<T>& data, const int_type low, const int_type high) {
                if (low < high) {
                    // Random permutation of rightmost element
                    pwm::swapArrayElems<T, compress_t, int_type>(coords, data, (((int_type)rand()) % (high-low)) + low, high); 
                    const int_type middle = partitionBlock(coords, data, low, high);

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
                    
                    compress_index_t middle_index = fromCompressedToRow(ind[middle]);
                    if ((middle_index & (compress_index_t)half_dim) == 0) {
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
                    
                    compress_index_t middle_index = fromCompressedToCol(ind[middle]);
                    if ((middle_index & (compress_index_t)half_dim) == 0) {
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
             * @param cutoff Indicates the maximum number of nonzeros in the block for serial computation
             */
            void blockMult(const int_type start, const int_type end, const int_type dim, const T* x, T* y, const int_type cutoff) {          
                assert(end >= start);

                // Perform serial computation if there are not too many nonzeros
                if (end - start <= cutoff) {
                    compress_index_t row_ind, col_ind;
                    for (int_type i = start; i <= end; ++i) {
                        row_ind = fromCompressedToRow(ind[i]);
                        col_ind = fromCompressedToCol(ind[i]);
                        y[row_ind] = y[row_ind] + data[i]*x[col_ind];
                    }

                    return;
                }

                // There are too much nonzeros so we do a recursive subdivision (M00, M01, M10, M11)
                const int_type half_dim = dim / 2;

                // Calculate splitting points
                const int_type s2 = binarySearchDivisionPointRow(half_dim, start, end); // Split between M00, M01 and M10, M11
                const int_type s1 = binarySearchDivisionPointColumn(half_dim, start, s2-1); // Split between M00 and M01
                const int_type s3 = binarySearchDivisionPointColumn(half_dim, s2, end); // Split between M10 and M11

                const int_type new_cutoff = std::max<int_type>(cutoff/2, MIN_NNZ_TO_PAR);
                
                // M00
                if (s1-1 >= start) {
                    #pragma omp task priority(1)
                    blockMult(start, s1-1, half_dim, x, y, new_cutoff);
                }
                
                // M11
                if (end >= s3) {
                    #pragma omp task priority(1)
                    blockMult(s3, end, half_dim, x, y, new_cutoff);
                }

                #pragma omp taskwait

                // M01
                if (s2-1 >= s1) {
                    #pragma omp task priority(1)
                    blockMult(s1, s2-1, half_dim, x, y, new_cutoff);
                }
                
                // M10
                if (s3-1 >= s2) {
                    #pragma omp task priority(1)
                    blockMult(s2, s3-1, half_dim, x, y, new_cutoff);
                }
                
                #pragma omp taskwait
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
                const int_type first_block_index = blockCoordToIndex(block_row, block_column_start);
                const int_type am_blocks = (block_column_end - block_column_start)+1;
                
                int_type block_index, x_offset;
                compress_index_t row_ind, col_ind;
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
                    const int_type left_chunk = chunks[0]+1;
                    const int_type right_chunk = chunks[1];

                    if (left_chunk == right_chunk) {
                        // Chunk is a single block
                        int_type block_index = blockCoordToIndex(block_row, left_chunk);
                        int_type start = blk_ptr[block_index];
                        int_type end = blk_ptr[block_index+1]-1;

                        blockMult(start, end, beta, x, y, std::max<int_type>(beta*O_DIM_CONST, MIN_NNZ_TO_PAR));
                    } else {
                        // The chunk consists of multiple blocks and thus is sparse
                        sparseRowMult(block_row, left_chunk, right_chunk, x, y);
                    }
                                        
                    return;
                }
                
                // Blockrow contains multiple chunks thus we subdivide
                const int_type middle = integerCeil<int_type>(chunks_length, 2) - 1; // Middle chunk index
                const int_type x_middle = beta*(chunks[middle] - chunks[0]); // Middle of x vector

                // Create pointer to temp array and use a Mutex to check if the first mult is already finished
                omp_lock_t temp_lock;
                omp_init_lock(&temp_lock);
                omp_set_lock(&temp_lock);

                T* temp_res = NULL;

                #pragma omp task shared(temp_lock, x, y, chunks) priority(51)
                {
                    blockRowMult(block_row, chunks, middle+1, x, y);
                    omp_unset_lock(&temp_lock);
                }

                #pragma omp task shared(temp_lock, x, y, chunks, temp_res) priority(50)
                {
                    if (omp_test_lock(&temp_lock)) {
                        // First result is already calculated so we don't need temp vector
                        blockRowMult(block_row, chunks+middle, chunks_length-middle, x+x_middle, y);
                    } else {
                        // Initialize temp result
                        temp_res = new T[std::min((block_row+1)*beta, this->nor) - block_row*beta];
                        std::fill(temp_res, temp_res+std::min((block_row+1)*beta, this->nor) - block_row*beta, 0.);

                        blockRowMult(block_row, chunks+middle, chunks_length-middle, x+x_middle, temp_res);
                    }
                }

                #pragma omp taskwait

                // If a temp vector was initialized we need to sequentially add the results
                if (temp_res != NULL) {
                    for (int_type i = 0; i < std::min((block_row+1)*beta, this->nor) - block_row*beta; ++i) {
                        y[i] += temp_res[i];
                    }

                    delete [] temp_res;
                }

                omp_destroy_lock(&temp_lock);
            }

        public:
            // Base constructor
            CSB() {}

            // Base constructor
            CSB(int threads): threads(threads) {}

            // Deconstructor
            ~CSB() {
                delete [] ind;
                delete [] data;
                delete [] blk_ptr;
                
                ind = NULL;
                data = NULL;
                blk_ptr = NULL;
            }

            /**
             * @brief Input the CSB matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partitions_am) {
                omp_set_num_threads(threads);

                this->noc = input->col_size;
                this->nor = input->row_size;
                this->nnz = input->nnz;

                setBlockSizeParam();

                horizontal_blocks = pwm::integerCeil<int_type>(this->noc, beta);
                vertical_blocks = pwm::integerCeil<int_type>(this->nor, beta);

                ind = new compress_t[this->nnz];
                data = new T[this->nnz];
                blk_ptr = new int_type[horizontal_blocks*vertical_blocks+1];
                blk_ptr[0] = 0;

                // Keep track of nnz's in each blockrow
                double* blockrow_nnz = new double[vertical_blocks];

                // Sort triplets on row value
                int_type** coords = new int_type*[2];
                coords[0] = input->row_coord;
                coords[1] = input->col_coord;
                sortOnCoord<T, int_type, int_type, 2>(coords, input->data, 0, this->nnz-1);
                delete [] coords;
                
                #pragma omp parallel
                #pragma omp single
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    #pragma omp task firstprivate(block_row)
                    {
                        double temp_nnz = 0.;

                        // Data structures which keep track of indices and data in each block
                        std::vector<std::vector<compress_t>> block_ind(horizontal_blocks, std::vector<compress_t>());
                        std::vector<std::vector<T>> block_data(horizontal_blocks, std::vector<T>());

                        // Calculate triplet and csb index by finding the first element which belongs to this block_row
                        int_type triplet_index = pwm::binarySearchLeftMost(input->row_coord, block_row*beta, this->nnz);
                        int_type csb_index = triplet_index;

                        // Calculate block pointer index
                        int_type blk_ptr_index = block_row*horizontal_blocks+1;

                        // Loop over all indices in triplet structure which are part of this block row
                        int_type block_index;
                        compress_t index;
                        while (triplet_index < this->nnz && input->row_coord[triplet_index] < (block_row+1)*beta) {
                            block_index = input->col_coord[triplet_index] / beta;

                            index = fromIndicesToCompressed(input->row_coord[triplet_index] % beta, input->col_coord[triplet_index] % beta);
                            block_ind[block_index].push_back(index);
                            block_data[block_index].push_back(input->data[triplet_index]);

                            triplet_index++;
                            temp_nnz += 1.;
                        }

                        blockrow_nnz[block_row] = temp_nnz;

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

                // Check if matrix is balanced
                // This happens if no blockrow has twice the nnz on a blockrow than the average nnz per blockrow
                balanced_block_rows = true;

#ifndef CSB_ALWAYS_BALANCED
                const double block_row_avg = std::accumulate(blockrow_nnz, blockrow_nnz+vertical_blocks, 0.0) / vertical_blocks;
                for (int_type i = 0; i < vertical_blocks; ++i) {
                    if (blockrow_nnz[i] > 2*block_row_avg) {
                        balanced_block_rows = false;
                        break;
                    }
                }
#endif

#ifndef NDEBUG
                if (balanced_block_rows) std::cout << "The CSB matrix is balanced" << std::endl;
                else std::cout << "The CSB matrix is unbalanced" << std::endl;
#endif

                delete [] blockrow_nnz;
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

                loadFromTriplets(&temp_mat, partitions);
            }

            /**
             * @brief Sparse matrix vector product calculation
             * 
             * Uses work-stealing scheduling of OpenMP Tasks
             * Tasks are block rows which can be split up as described in the CSB paper
             * 
             * @param x Vector to be multiplied with the matrix
             * @param y Result vector
             */
            void mv(const T* x, T* y) {
                if (balanced_block_rows) {
                    #pragma omp parallel
                    #pragma omp single
                    for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                        #pragma omp task firstprivate(block_row) priority(100)
                        {
                            std::fill(y+block_row*beta, y+std::min((block_row+1)*beta, this->nor), 0.);

                            // Perform balanced block row multiplication
                            sparseRowMult(block_row, 0, horizontal_blocks-1, x, y+block_row*beta);
                        }
                    }
                } else {
                    #pragma omp parallel
                    #pragma omp single
                    for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                        #pragma omp task firstprivate(block_row) priority(100)
                        {
                            std::fill(y+block_row*beta, y+std::min((block_row+1)*beta, this->nor), 0.);

                            int* chunks = new int[horizontal_blocks+1]; // Worst case that all blocks are a separate chunk
                            chunks[0] = -1;
                            int_type chunk_index = 1;

                            int_type first_block_index = blockCoordToIndex(block_row, 0);

                            int_type count = 0;
                            for (int_type block_col = 0; block_col < horizontal_blocks - 1; ++block_col) {
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

                            // Perform unbalanced block row multiplication
                            blockRowMult(block_row, chunks, chunk_index, x, y+block_row*beta);

                            delete [] chunks;
                        }
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
            void powerIteration(T* x, T* y, const int_type it) {
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