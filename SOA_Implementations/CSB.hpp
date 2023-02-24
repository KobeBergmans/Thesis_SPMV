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
 * TODO: Morton-Z ordering
 * TODO: Poisson matrix input
 */


#ifndef PWM_CSB_HPP
#define PWM_CSB_HPP

#define BETA 8

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
                sortCoordsForCRS(coords, input.data, 2, 0, this->nnz-1);

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
                        block_row_ind[block_index].push_back(input.row_coord[triplet_index]);
                        block_col_ind[block_index].push_back(input.col_coord[triplet_index]);
                        block_data[block_index].push_back(input.data[triplet_index]);

                        triplet_index++;
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