/**
 * @file CSB.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Implementation of CSB scheme
 * 
 * Based on:
 *   A. Buluc, J. Gilbert, and V. B. Shah. 13. Implementing Sparse Matrices
 *   for Graph Algorithms, pages 287–313. Society for Industrial and Applied
 *   Mathematics, 2011
 * 
 * TODO: Make blocksize dependent on matrix
 * TODO: Integer compression
 * TODO: Poisson matrix input
 * TODO: Avoid first touch
 */


#ifndef PWM_CSB_HPP
#define PWM_CSB_HPP

#define BETA 8
#define COORD_BITS 3

#include "../Matrix/SparseMatrix.hpp"

#include "../Util/VectorUtill.hpp"

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

        private:
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

        public:
            // Base constructor
            CSB() {}

            // Base constructor
            CSB(int threads) {}

            /**
             * @brief Input the CSB matrix as a poisson matrix
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             * @param partitions Not used
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                return;
            }

            /**
             * @brief Input the CSB matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partitions_am) {
                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;

                int_type horizontal_blocks = this->noc/BETA + (this->noc % BETA != 0);
                int_type vertical_blocks = this->nor/BETA + (this->nor % BETA != 0);

                row_ind = new int_type[this->nnz];
                col_ind = new int_type[this->nnz];
                data = new T[this->nnz];
                blk_ptr = new int_type[horizontal_blocks*vertical_blocks];

                // Sort triplets on row value
                int_type** coords = new int_type*[2];
                coords[0] = input.row_coord;
                coords[1] = input.col_coord;
                sortCoordsForCRS<T, int_type>(coords, input.data, 2, 0, this->nnz-1);

                // Generate CSB structure per block row
                int_type triplet_index = 0;
                int_type csb_index = 0;
                int_type blk_ptr_index = 0;
                for (int_type block_row = 0; block_row < vertical_blocks; ++block_row) {
                    // Data structures which keep track of indices and data in each block
                    std::vector<std::vector<int_type>> block_row_ind(horizontal_blocks, std::vector<int_type>());
                    std::vector<std::vector<int_type>> block_col_ind(horizontal_blocks, std::vector<int_type>());
                    std::vector<std::vector<T>> block_data(horizontal_blocks, std::vector<T>());

                    // Loop over all indices in triplet structure which are part of this block row
                    while (input.row_coord[triplet_index] < (block_row+1)*BETA && triplet_index < this->nnz) {
                        int_type block_index = input.col_coord[triplet_index] / BETA;
                        block_row_ind[block_index].push_back(input.row_coord[triplet_index]-block_row*BETA);
                        block_col_ind[block_index].push_back(input.col_coord[triplet_index]-block_index*BETA);
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
                    for (int_type block_col = 0; block_col < horizontal_blocks; ++ block_col) {
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
            }

            /**
             * @brief Sparse matrix vector product calculation
             * 
             * Uses work-stealing scheduling of TBB
             * Tasks are block rows which can be split up as described in the CSB paper
             * 
             * @param x Vector to be modified with the matrix
             * @return T* Result vector
             */
            void mv(const T* x, T* y) {
                std::fill(y, y+this->nor, 0.);

                return;
            }

            /**
             * @brief Power method
             * 
             * @param x Input vector to start power method
             * @param it Amount of iterations
             * @return T* Resulting vector
             */
            void powerMethod(T* x, T* y, const int_type it) {
                return;
            }
    };
} // namespace pwm


#endif // PWM_CSB_HPP