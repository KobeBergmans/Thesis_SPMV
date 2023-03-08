/**
 * @file BlockCOH.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Implementation of row-distributed block CO-H scheme
 * 
 * Based on:
 *   A.-J. N. Yzelman and D. Roose. High-level strategies for parallel sharedmemory sparse matrix-vector multiplication. 
 *   IEEE Transactions on Parallel and Distributed Systems, 25(1):116–125, 2014.
 * 
 * TODO: Parallel implementation
 * TODO: ICRS instead of CRS on block level
 * TODO: Find efficient blocksize (look at Yzelman source code)
 * TODO: Look into compression
 * TODO: See if row partitioning can be done more effectively
 * TODO: Do something about empty blocks
 */

#ifndef PWM_BLOCKCOH_HPP
#define PWM_BLOCKCOH_HPP

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <cmath>

#include "../Matrix/Triplet.hpp"
#include "../Matrix/SparseMatrix.hpp"
#include "../Util/TripletToCRS.hpp"

typedef uint16_t index_t;

#define LOW_BITMASK  0b00000000000000001111111111111111
#define HIGH_BITMASK 0b11111111111111110000000000000000
#define COORD_BITS 16

namespace pwm {
    template<typename T, typename int_type>
    class BlockCOH: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Array of pointers which correspond to the compressed CRS row starting indices
            index_t** row_start;

            // Array of pointers which correspond to the compressed CRS column indices
            index_t** col_ind;

            // Array of pointers which correspond to the data in each block per processor
            T** data;

            // Array of pointers which correspond to the row jump arrays for BICRS on the block level per processor
            int_type** row_jump;

            // Array of pointers which correspond to the row jump arrays for BICRS on the block level per processor
            int_type** col_jump;

            // Row number where each of the partitions start
            int_type* thread_row_start;

            // Amount of threads
            int threads;

            // Blocksize for each thread
            int_type* beta;

            // Amount of bits for block indices for each thread
            int_type* block_bits;

            // Amount of vertical blocks per thread
            int_type* vertical_blocks;

            // Amount of horizontal blocks per thread
            int_type* horizontal_blocks;

            // Amount of nonzeros per thread
            int_type* thread_nnz;

        private:
            /**
             * @brief Ensures a correct rotation of the row and column for the next level of the hilbert curve
             * 
             * @param size Size of the original matrix, must be a power of 2
             * @param row Row of element
             * @param col Column of element
             * @param row_region specifies in which row region the current element lies
             * @param col_region specifies in which column region the current element lies
             */
            void hilbertRotate(int_type size, int_type* row, int_type* col, int_type row_region, int_type col_region) {
                if (row_region == 0) {
                    if (col_region == 1) {
                        *col = size - 1 - *col;
                        *row = size - 1 - *row;
                    }

                    // Swap row and column
                    int_type temp = *col;
                    *col = *row;
                    *row = temp;
                }
            }

            /**
             * @brief Converts a matrix element to an index on the Hilbert curve
             * 
             * https://en.wikipedia.org/wiki/Hilbert_curve
             * 
             * @param size Size of the original matrix, must be a power of 2
             * @param row Row of element
             * @param col Column of element
             * @return int_type index of the element on the hilbert curve
             */
            int_type rowColToHilbert(int_type size, int_type row, int_type col) {
                int_type row_region, col_region; 
                int_type index = 0;
                for (int_type check_size = size/2; check_size > 0; check_size /= 2) {
                    row_region = (row & check_size) > 0;
                    col_region = (col & check_size) > 0;
                    index += check_size*check_size*((3*col_region) ^ row_region);
                    hilbertRotate(size, &row, &col, row_region, col_region);
                }

                return index;
            }

            /**
             * @brief Returns row and column corresponding to index on hilbert curve
             * 
             * @param size Size of the original matrix, must be a power of 2
             * @param hilbert Hilbert coordinate of element
             * @return std::tuple<int_type, int_type> Row and column coordinate of element
             */
            std::tuple<int_type, int_type> hilbertToRowCol(int_type size, int_type hilbert) {
                int_type row_region, col_region;
                int_type row = 0;
                int_type col = 0;

                for (int_type check_size = 1; check_size < size; check_size *= 2) {
                    col_region = 1 & (hilbert/2);
                    row_region = 1 & (hilbert ^ col_region);
                    hilbertRotate(size, &row, &col, row_region, col_region);
                    row += check_size * row_region;
                    col += check_size * col_region;
                    hilbert /= 4;
                }

                return std::make_tuple(row, col);
            }

            /**
             * @brief Compares two matrix elements for the hilbert order
             * 
             * Calculates the coordinate on the hilbert curve of both elements and then compares
             * 
             * TODO: This is not optimal and slow...
             * 
             * @param size Size of the matrix, this must be a power of 2
             * @param row1 Row of first element
             * @param col1 Column of first element
             * @param row2 Row of second element
             * @param col2 Column of second element
             * @return true if the first element is before or equal to the second element in Hilbert order
             * @return false if the first element is after than the second element in Hilbert order
             */
            bool hilbertCompare(int_type size, int_type row1, int_type col1, int_type row2, int_type col2) {
                return rowColToHilbert(size, row1, col1) <= rowColToHilbert(size, row2, col2);
            }

            /**
             * @brief Calculates the blocksize for each thread
             */
            void setBlockSizeParams() {
                beta = new int_type[threads];
                block_bits = new int_type[threads];

                int_type minimal_size;
                for (int pid = 0; pid < threads; ++pid) {
                    // Maximum of 16 is specified because row and column indices should fit in 4 bytes
                    minimal_size = std::min<int_type>(calculateNOR(pid), this->noc);
                    int_type lg_sqrt_size = (int_type)(std::ceil(std::log2(std::sqrt((double)minimal_size))));
                    block_bits[pid] = std::min<int_type>(16, lg_sqrt_size);
                    beta[pid] = std::pow(2, block_bits[pid]);
                }
            }

            /**
             * @brief Gives the amount of rows for each thread
             * 
             * @param pid Thread index
             */
            inline int_type calculateNOR(int pid) {
                if (pid != threads - 1) return thread_row_start[pid+1]-thread_row_start[pid];
                else return this->nor - thread_row_start[pid];
            }

            /**
             * @brief Quicksort partition function
             * 
             * @param coords Array which contains 2 pointers, pointing to the column and row indices respectively
             * @param data data of the block which needs to be partitioned
             * @param low Starting index of data
             * @param high Ending index of data
             * @param orig_size Size of the area that is sorted
             * @param pid Thread number corresponding to the given area
             * @return int_type Returns partitioning point
             */
            int_type partitionBlock(int_type** coords, T* data, int_type low, int_type high, int_type orig_size, int pid) {
                // Select pivot (rightmost element)
                int_type pivotRow = (coords[0][high]-thread_row_start[pid]) / beta[pid];
                int_type pivotCol = coords[1][high] / beta[pid];

                // Points to biggest element
                int_type i = low;
                for (int j = low; j < high; ++j) {
                    if (hilbertCompare(orig_size / beta[pid], (coords[0][j]-thread_row_start[pid]) / beta[pid], coords[1][j]/ beta[pid], pivotRow, pivotCol)) {
                        // If element is smaller than pivot swap it with i+1
                        pwm::swapArrayElems<T, int_type, int_type>(coords, data, 2, i, j);
                        i++;
                    }
                }

                // Swap pivot with the greatest element at i+1
                pwm::swapArrayElems<T, int_type, int_type>(coords, data, 2, i, high);

                // return the partitioning point
                return i;
            }

            /**
             * @brief Sorts the nonzeros using hilbert order on the blocklevel
             * 
             * Makes use of quicksort implementation (see sortOnCoord in Util/TripletToCRS.hpp)
             * 
             * @param coords Array consisting of 2 pointers, pointing to the column and row indices respectively
             * @param data data of given block indices
             * @param low starting index of data to be sorted
             * @param high ending index of data to be sorted
             * @param orig_size Size of the area that is sorted
             * @param pid Thread number corresponding to the given area
             */
            void sortForHilbertBlocks(int_type** coords, T* data, int_type low, int_type high, int_type orig_size, int pid) {
                if (low < high) {
                    // Random permutation of rightmost element
                    pwm::swapArrayElems<T, int_type, int_type>(coords, data, 2, (((int_type)rand()) % (high-low)) + low, high); 

                    int_type middle = partitionBlock(coords, data, low, high, orig_size, pid);

                    if (middle > 0) {
                        sortForHilbertBlocks(coords, data, low, middle - 1, orig_size, pid);
                    }
                    sortForHilbertBlocks(coords, data, middle + 1, high, orig_size, pid);
                }
            }

            /**
             * @brief Transform hilbert block from input triplet matrix to CRS format
             * 
             * @param input Triplet input matrix
             * @param block_start Starting index of the block
             * @param block_end Ending index of the block
             * @param hilbert_coord Hilbert coordinate of the block
             * @param triplet_index Starting index of the thread in the input matrix
             * @param pid Thread number corresponding to the given area
             */
            void transformHilbertBlockToCRS(pwm::Triplet<T, int_type>* input, int_type block_start, int_type block_end, int_type hilbert_coord, int_type triplet_index, int pid) {
                // Transform triplet indices to block indices
                index_t* block_row_ind = new index_t[block_end-block_start];
                index_t* block_col_ind = new index_t[block_end-block_start];

                for (int_type j = 0; j < block_end-block_start; ++j) {
                    block_row_ind[j] = (index_t)(((input->row_coord+block_start+triplet_index)[j] - thread_row_start[pid]) % beta[pid]);
                    block_col_ind[j] = (index_t)((input->col_coord+block_start+triplet_index)[j] % beta[pid]);
                }

                // Store block as CRS format
                pwm::TripletToCRS<T, index_t, int_type>(block_row_ind, block_col_ind, input->data+block_start+triplet_index, row_start[pid]+(beta[pid]+1)*hilbert_coord, col_ind[pid]+block_start, data[pid]+block_start, block_end-block_start, beta[pid]);

                delete [] block_row_ind;
                delete [] block_col_ind;
            }

            

        public:
            // Base constructor
            BlockCOH() {}

            // Base constructor
            BlockCOH(int threads): threads(threads) {}

            // Deconstructor
            ~BlockCOH() {}

            /**
             * @brief Input the row distributed block CO-H matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             * @param partitions_am unused
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partitions_am) {
                omp_set_num_threads(threads);

                this->noc = input->col_size;
                this->nor = input->row_size;
                this->nnz = input->nnz;

                // Distribute the matrix rows per thread
                thread_nnz = new int_type[threads];
                int_type* row_nnz = new int_type[this->nor];
                std::fill(row_nnz, row_nnz+this->nor, 0);
                for (int_type i = 0; i < input->nnz; ++i) {
                    row_nnz[input->row_coord[i]]++;
                }

                thread_row_start = new int_type[threads];
                thread_row_start[0] = 0;
                int_type row_start_index = 1;
                int_type row_sum = 0;
                int pid = 0;
                for (int_type i = 0; i < this->nor; ++i) {
                    row_sum += row_nnz[i];

                    if (row_sum > this->nnz / threads && pid != threads - 1) {
                        thread_nnz[pid++] = row_sum - row_nnz[i];
                        thread_row_start[row_start_index++] = i;
                        row_sum = row_nnz[i];
                    }
                }

                thread_nnz[pid] = row_sum;

                delete [] row_nnz;

                // Sort original matrix on rows
                int_type** coords = new int_type*[2];
                coords[0] = input->row_coord;
                coords[1] = input->col_coord;
                sortOnCoord<T, int_type, int_type>(coords, input->data, 2, 0, this->nnz-1);

                // Calculate block size for each thread
                setBlockSizeParams();

                // Generate datastructures for each thread
                row_start = new index_t*[threads];
                col_ind = new index_t*[threads];
                data = new T*[threads];
                horizontal_blocks = new int_type[threads];
                vertical_blocks = new int_type[threads];

                // Indices datastructures
                int_type triplet_index = 0;
                int_type hilbert_size, hilbert_coord, block_start;

                // Create and fill datastructures for each thread
                for (int pid = 0; pid < threads; ++pid) {
                    // Create datastructures
                    horizontal_blocks[pid] = pwm::integerCeil<int_type>(this->noc, beta[pid]);
                    vertical_blocks[pid] = pwm::integerCeil<int_type>(calculateNOR(pid), beta[pid]);

                    std::cout << "Horizontal blocks: " << horizontal_blocks[pid] << ", Vertical blocks: " << vertical_blocks[pid] << std::endl;

                    row_start[pid] = new index_t[(beta[pid]+1)*horizontal_blocks[pid]*vertical_blocks[pid]]; // Beta + 1 elements per block
                    col_ind[pid] = new index_t[thread_nnz[pid]];
                    data[pid] = new T[thread_nnz[pid]];

                    // Fill row start with zeros to compensate for empty blocks
                    std::fill(row_start[pid], row_start[pid]+(beta[pid]+1)*horizontal_blocks[pid]*vertical_blocks[pid], 0);

                    // Sort the elements for this thread using the hilbert sorting method
                    hilbert_size = std::max<int_type>(calculateNOR(pid), this->noc);
                    hilbert_size = (int_type)std::pow<double>(2., std::ceil(std::log2((double)hilbert_size)));
                    sortForHilbertBlocks(coords, input->data, triplet_index, triplet_index + thread_nnz[pid]-1, hilbert_size, pid);

                    // Track all the indices in each Hilbert block and use Triplet to CRS in each block
                    block_start = 0;
                    hilbert_coord = rowColToHilbert(hilbert_size / beta[pid], (input->row_coord[0]-thread_row_start[pid]) / beta[pid], input->col_coord[0] / beta[pid]);

                    for (int_type i = 0; i < thread_nnz[pid]; ++i) {
                        // Check if we reached the end of the block
                        if (rowColToHilbert(hilbert_size, (input->row_coord[triplet_index+i]-thread_row_start[pid]) / beta[pid], input->col_coord[triplet_index+i] / beta[pid]) != hilbert_coord) {

                            std::cout << "End of block reached, i=" << i << std::endl;

                            transformHilbertBlockToCRS(input, block_start, i, hilbert_coord, triplet_index, pid);

                            // set datastructures for next block
                            block_start = i;
                            hilbert_coord = rowColToHilbert(hilbert_size, (input->row_coord[triplet_index+i]-thread_row_start[pid]) / beta[pid], input->col_coord[triplet_index+i] / beta[pid]);

                            std::cout << "New block hilbert coord: " << hilbert_coord << std::endl;
                        } 
                    }

                    // Also convert the last block
                    transformHilbertBlockToCRS(input, block_start, thread_nnz[pid], hilbert_coord, triplet_index, pid);

                    // Update triplet_index
                    triplet_index += thread_nnz[pid];

                    std::cout << "Row start: " << std::endl;
                    pwm::printVector(row_start[pid], (beta[pid]+1)*horizontal_blocks[pid]*vertical_blocks[pid]);
                    std::cout << "col indices: " << std::endl;
                    pwm::printVector(col_ind[pid], thread_nnz[pid]);
                    std::cout << "data: " << std::endl;
                    pwm::printVector(data[pid], thread_nnz[pid]);
                }

                delete [] coords;
            }

            /**
             * @brief Input the Block CO-H matrix as a poisson matrix
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
             * @param x Vector to be modified with the matrix
             * @param y Result vector
             */
            void mv(const T* x, T* y) {
                std::fill(y, y+this->nor, 0.);

                return;
            }

            /**
             * @brief Power method
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm is it is uneven
             * @param y Vector to store calculations, contains the output at the end of the algorithm if it is even
             * @param it Amount of iterations
             */
            void powerMethod(T* x, T* y, const int_type it) {
                return;
            }

    };
} // namespace pwm


#endif // PWM_BLOCKCOH_HPP