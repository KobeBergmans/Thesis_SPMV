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
 * TODO: Make blocksize dependent on matrix
 * TODO: Integer compression
 * TODO: Poisson matrix input
 * TODO: Avoid first touch
 * TODO: Check what the O_DIM_CONST should be
 * TODO: Add parallelism
 * TODO: Check if chunk array can be made quicker
 */


#ifndef PWM_CSB_HPP
#define PWM_CSB_HPP

#define BETA 8
#define COORD_BITS 3
#define O_DIM_CONST 3
#define O_BETA_CONST 3

#include <cassert>
#include <algorithm>

#include "../Matrix/SparseMatrix.hpp"

#include "../Util/VectorUtill.hpp"
#include "../Util/Math.hpp"

namespace pwm {
    template<typename T, typename int_type>
    class CSB: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Row indices for matrix entries
            int_type* row_ind;

            // Column indices for matrix entries
            int_type* col_ind;

            // Values corresponding to row and column indices
            T* data;

            // Pointer to the start of each block
            int_type* blk_ptr;

            // Amount of horizontal blocks
            int_type horizontal_blocks;

            // Amount of vertical blocks
            int_type vertical_blocks;

        private:
            int_type blockColumnRowToIndex(const int_type block_row, const int_type block_column) {
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
            bool zMortonCompare(const int_type x1, const int_type y1, const int_type x2, const int_type y2) {
                bool set_1, set_2;
                for (int bit_nb = COORD_BITS-1; bit_nb >= 0; --bit_nb) {
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
             * @brief Sorts the given block using Z-Morton ordering
             * 
             * @param coords Array consisting of 2 pointers, pointing to the column and row indices respectively
             * @param data data of given block indices
             */
            void sortBlock(int_type** coords, std::vector<T> data) {
                // Simple bubble sort implementation
                for (size_t j = 0; j < data.size(); ++j) {
                    for (size_t i = 1; i < data.size() - j; ++i) {
                        if (!zMortonCompare(coords[0][i-1], coords[1][i-1], coords[0][i], coords[1][i])) {
                            pwm::swapArrayElems<T, int_type>(coords, data.data(), 2, i-1, i);
                        }
                    }
                }
            }

            /**
             * @brief Binary search for the division point as explained in the paper
             * 
             * @param indices Row or column indices for which the division point is calculated
             * @param dim dimension of the original matrix
             * @param start starting index for binary search
             * @param end ending index for binary search
             * @return int_type smallest index s for which (indices[s] & dim/2) != 0
             */
            int_type binarySearchDivisionPoint(const int_type* indices, const int_type half_dim, int_type start, int_type end) {
                while (start < end) {
                    int_type middle = (start+end)/2;
                    
                    if ((indices[middle] & half_dim) == 0) {
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
                // Perform serial computation if there are not too many nonzeros
                if (end - start <= dim*O_DIM_CONST) {
                    for (int_type i = start; i < end; ++i) {
                        y[row_ind[i]] = y[row_ind[i]] + data[i]*x[col_ind[i]];
                    }

                    return;
                }

                // There are too much nonzeros so we do a recursive subdivision (M00, M01, M10, M11)
                int_type half_dim = dim / 2;

                // Calculate splitting points
                int_type s2 = binarySearchDivisionPoint(row_ind, half_dim, start, end); // Split between M00, M01 and M10, M11
                int_type s1 = binarySearchDivisionPoint(col_ind, half_dim, start, s2-1); // Split between M00 and M01
                int_type s3 = binarySearchDivisionPoint(col_ind, half_dim, s2, end); // Split between M10 and M11

                // In parallel do:
                blockMult(start, s1-1, half_dim, x, y); // M00
                blockMult(s3, end, half_dim, x, y); // M11

                // In parallel do:
                blockMult(s1, s2-1, half_dim, x, y); // M01
                blockMult(s2, s3-1, half_dim, x, y); // M10
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
                int_type first_block_index = blockColumnRowToIndex(block_row, block_column_start);
                int_type am_blocks = (block_column_end - block_column_start);
                int_type block_index, x_offset;

                for (int_type block_nb = 0; block_nb <= am_blocks; ++block_nb) {
                    block_index = first_block_index + block_nb;
                    x_offset = block_nb*BETA;

                    for (int_type i = blk_ptr[block_index]; i < blk_ptr[block_index+1]; ++i) {
                        y[row_ind[i]] = y[row_ind[i]] + data[i]*x[x_offset + col_ind[i]];
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
                        int_type block_index = blockColumnRowToIndex(block_row, left_chunk);
                        int_type start = blk_ptr[block_index];
                        int_type end = blk_ptr[block_index+1];

                        blockMult(start, end, BETA, x, y);
                    } else {
                        // The chunk consists of multiple blocks and thus is sparse
                        sparseRowMult(block_row, left_chunk, right_chunk, x, y);
                    }
                    
                    return;
                }

                // Blockrow contains multiple chunks thus we subdivide
                int_type middle = integerCeil<int_type>(chunks_length, 2) - 1; // Middle chunk index
                int_type x_middle = BETA*(chunks[middle] - chunks[0]); // Middle of x vector

                // Initialize vector for temporary results
                T* temp_res = new T[BETA];
                std::fill(temp_res, temp_res+BETA, 0.);

                // In parallel do:
                blockRowMult(block_row, chunks, middle+1, x, y);
                blockRowMult(block_row, chunks+middle, chunks_length-middle, x+x_middle, temp_res);

                // Add temporary result serially
                for (int_type i = 0; i < BETA; ++i) {
                    y[i] = y[i] + temp_res[i];
                }

                delete [] temp_res;
            }

        public:
            // Base constructor
            CSB() {}

            // Base constructor
            CSB(int threads) {}

            /**
             * @brief Input the CSB matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partitions_am) {
                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;

                horizontal_blocks = pwm::integerCeil<int_type>(this->noc, BETA);
                vertical_blocks = pwm::integerCeil<int_type>(this->nor, BETA);

                row_ind = new int_type[this->nnz];
                col_ind = new int_type[this->nnz];
                data = new T[this->nnz];
                blk_ptr = new int_type[horizontal_blocks*vertical_blocks+1];
                blk_ptr[0] = 0;

                // Sort triplets on row value
                int_type** coords = new int_type*[2];
                coords[0] = input.row_coord;
                coords[1] = input.col_coord;
                sortCoordsForCRS<T, int_type>(coords, input.data, 2, 0, this->nnz-1);

                // Generate CSB structure per block row
                int_type triplet_index = 0;
                int_type csb_index = 0;
                int_type blk_ptr_index = 1;
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    // Data structures which keep track of indices and data in each block
                    std::vector<std::vector<int_type>> block_row_ind(horizontal_blocks, std::vector<int_type>());
                    std::vector<std::vector<int_type>> block_col_ind(horizontal_blocks, std::vector<int_type>());
                    std::vector<std::vector<T>> block_data(horizontal_blocks, std::vector<T>());

                    // Loop over all indices in triplet structure which are part of this block row
                    while (triplet_index < this->nnz && input.row_coord[triplet_index] < (block_row+1)*BETA) {
                        int_type block_index = input.col_coord[triplet_index] / BETA;
                        block_row_ind[block_index].push_back(input.row_coord[triplet_index] % BETA);
                        block_col_ind[block_index].push_back(input.col_coord[triplet_index] % BETA);
                        block_data[block_index].push_back(input.data[triplet_index]);

                        triplet_index++;
                    }

                    // Sort blocks in Morton-Z order
                    for (int_type block_column = 0; block_column < horizontal_blocks; ++block_column) {
                        coords[0] = block_col_ind[block_column].data();
                        coords[1] = block_row_ind[block_column].data();
                        sortBlock(coords, block_data[block_column]);
                    }

                    // Initialize CSB datastructures
                    for (int_type block_col = 0; block_col < horizontal_blocks; ++block_col) {
                        for (size_t i = 0; i < block_row_ind[block_col].size(); ++i) {
                            row_ind[csb_index] = block_row_ind[block_col][i];
                            col_ind[csb_index] = block_col_ind[block_col][i];
                            data[csb_index] = block_data[block_col][i];

                            csb_index++;
                        }

                        blk_ptr[blk_ptr_index] = csb_index;
                        blk_ptr_index++;
                    }
                }

                delete [] coords;
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

                std::cout << "m: " << m << ", n: " << n << std::endl;
                pwm::printVector(temp_mat.row_coord, temp_mat.nnz);
                pwm::printVector(temp_mat.col_coord, temp_mat.nnz);
                pwm::printVector(temp_mat.data, temp_mat.nnz);

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

                // Parallel for:
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    int* chunks = new int[horizontal_blocks]; // Worst case that all blocks are a separate chunk
                    int_type chunk_index = 0;
                    chunks[chunk_index++] = -1;

                    int_type first_block_index = blockColumnRowToIndex(block_row, 0);

                    int_type count = 0;
                    for (int_type block_col = 0; block_col <= horizontal_blocks - 2; ++block_col) {
                        // Add elements of current block to count
                        count = count + blk_ptr[first_block_index+block_col+1]-blk_ptr[first_block_index+block_col];

                        // Check if next block will exceed the maximum number of nz
                        if (count + blk_ptr[first_block_index+block_col+2]-blk_ptr[first_block_index+block_col+1] > BETA*O_BETA_CONST) {
                            chunks[chunk_index++] = block_col;
                            count = 0;
                        }
                    }

                    // Add last block to end the last chunk
                    chunks[chunk_index++] = vertical_blocks-1; 

                    // Perform block row multiplication
                    blockRowMult(block_row, chunks, chunk_index, x, y+block_row*BETA);

                    delete [] chunks;
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