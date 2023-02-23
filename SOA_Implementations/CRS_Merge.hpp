/**
 * @file CRSOMP.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using Merge-based multiplication
 * 
 * Based on:
 * D. Merrill and M. Garland. Merge-based parallel sparse matrix-vector multiplication. 
 * In SC ’16: Proceedings of the International Conference for High
 * Performance Computing, Networking, Storage and Analysis, pages 678–689, 2016.
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRS_MERGE_HPP
#define PWM_CRS_MERGE_HPP

#include <tuple>
#include <algorithm>

#include "../Matrix/SparseMatrix.hpp"
#include "../Util/VectorUtill.hpp"
#include "../Util/Poisson.hpp"

#include <omp.h>

namespace pwm {
    template<typename T, typename int_type>
    class CRS_Merge: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Row start array for the CRS format
            int_type* row_start;
            
            // Column index array for the CRS format
            int_type* col_ind;

            // Data array which stores the actual nonzeros
            T* data_arr;

            // Amount of threads to be used
            int threads;

        private:
            /**
             * @brief Calculate which coordinate in both lists the merge path will have on the given diagonal
             * 
             * Merge list B is implicitly given by the natural numbers.
             * 
             * @param diagonal diagonal on which coordinate must lie
             * @param list_A First merge list
             * @return std::tuple<int_type, int_type> First element represents the coordinate in list A and second element coordinate in list B
             */
            std::tuple<int_type, int_type> searchPathOnDiag(int_type diagonal, int_type* list_A) {
                // Search range for A list
                int a_coord_min = std::max(diagonal - this->nnz, 0);
                int a_coord_max = std::min(diagonal, this->nor);

                // Binary-search along the diagonal
                while (a_coord_min < a_coord_max) {
                    int_type pivot = (a_coord_min + a_coord_max) >> 1; // Is equal to middle of interval (division is shift for speed)

                    if (list_A[pivot] <= diagonal-pivot-1) {
                        a_coord_min = pivot + 1; // Keep top-right of diag
                    } else {
                        a_coord_max = pivot; // Keep bottom-left of diag
                    }
                }

                return std::make_tuple(std::min(a_coord_min, this->nor), diagonal-a_coord_min);
            }

        public:
            // Base constructor
            CRS_Merge() {}

            // Base constructor
            CRS_Merge(int threads): threads(threads) {
                if (threads == -1) {
                    threads = omp_get_max_threads();
                }
            }

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             *
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                omp_set_num_threads(threads);

                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];

                pwm::fillPoissonOMP(data_arr, row_start, col_ind, m, n);

                assert(row_start[0] == 0);
                assert(row_start[this->nor] == this->nnz);
            }

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partition_am) {
                omp_set_num_threads(threads);

                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;

                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];

                pwm::TripletToCRSOMP(input.row_coord, input.col_coord, input.data, row_start, col_ind, data_arr, this->nnz, this->nor);
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * Static scheduling using the merge-based scheduling
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {             
                int_type* row_end_offsets = row_start + 1; // Merge list A
                int_type num_merge_items = this->nor + this->nnz;
                int_type items_per_thread = (num_merge_items + threads - 1) / threads;

                int_type row_carry_out[threads];
                T value_carry_out[threads];

                // Parallel section: each thread processes 1 loop iteration
                #pragma omp parallel for schedule(static) num_threads(threads)
                for (int tid = 0; tid < threads; ++tid) {
                    // Find start and stop coordinates of merge path
                    int_type diagonal = std::min(items_per_thread*tid, num_merge_items);
                    int_type diagonal_end = std::min(diagonal + items_per_thread, num_merge_items);
                    std::tuple<int_type, int_type> thread_coord = searchPathOnDiag(diagonal, row_end_offsets);
                    std::tuple<int_type, int_type> thread_coord_end = searchPathOnDiag(diagonal_end, row_end_offsets);

                    int_type thread_a_coord = std::get<0>(thread_coord);
                    int_type thread_b_coord = std::get<1>(thread_coord);
                    int_type thread_a_coord_end = std::get<0>(thread_coord_end);
                    int_type thread_b_coord_end = std::get<1>(thread_coord_end);

                    // Consume merge items for every whole row
                    T running_total = 0.;
                    for (; thread_a_coord < thread_a_coord_end; ++thread_a_coord) {
                        for (; thread_b_coord < row_end_offsets[thread_a_coord]; ++thread_b_coord) {
                            running_total += data_arr[thread_b_coord]*x[col_ind[thread_b_coord]];
                        }

                        y[thread_a_coord] = running_total;
                        running_total = 0.;
                    }

                    // Consume last row (if its a partial row)
                    for (; thread_b_coord < thread_b_coord_end; ++thread_b_coord) {
                        running_total += data_arr[thread_b_coord] * x[col_ind[thread_b_coord]];
                    }

                    // Save carry results
                    row_carry_out[tid] = thread_a_coord_end;
                    value_carry_out[tid] = running_total;
                }

                // Fix the carry results
                for (int tid = 0; tid < threads; ++tid) {
                    if (row_carry_out[tid] < this->nor) {
                        y[row_carry_out[tid]] += value_carry_out[tid];
                    }
                }
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * Loop is parallelized using OpenMP
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm is it is uneven
             * @param y Vector to store calculations, contains the output at the end of the algorithm if it is even
             * @param it Amount of iterations for the algorithm
             */
            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int it_nb = 0; it_nb < it; ++it_nb) {
                    if (it_nb % 2 == 0) {
                        this->mv(x, y);
                        T norm = pwm::norm2(y, this->nor);

                        #pragma omp parallel for shared (y, norm) schedule(static)
                        for (int i = 0; i < this->nor; ++i) {
                            y[i] /= norm;
                        }
                    } else {
                        this->mv(y, x);
                        T norm = pwm::norm2(x, this->nor);

                        #pragma omp parallel for shared(y, norm) schedule(static)
                        for (int i = 0; i < this->nor; ++i) {
                            x[i] /= norm;
                        }
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRS_MERGE_HPP