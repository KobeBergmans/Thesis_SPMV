/**
 * @file CRS_Merge.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using Merge-based multiplication
 * 
 * Based on:
 *   D. Merrill and M. Garland. Merge-based parallel sparse matrix-vector multiplication. 
 *   In SC ’16: Proceedings of the International Conference for High
 *   Performance Computing, Networking, Storage and Analysis, pages 678–689, 2016.
 */

#ifndef PWM_CRS_MERGE_HPP
#define PWM_CRS_MERGE_HPP

#include <tuple>
#include <algorithm>

#include "../Env_Implementations/CRSOMP.hpp"

#include <omp.h>

namespace pwm {
    template<typename T, typename int_type>
    class CRS_Merge: public pwm::CRSOMP<T, int_type> {
        protected:
            // List that keeps track of the starting coordinates in list A
            int_type* list_a_coord;

            // List that keeps track of the starting coordinates in list A
            int_type* list_b_coord;

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
            std::tuple<int_type, int_type> searchPathOnDiag(const int_type diagonal, const int_type* list_A) {
                // Search range for A list
                int_type a_coord_min = 0;
                if (diagonal > this->nnz) {
                    a_coord_min = diagonal - this->nnz;
                }
                int_type a_coord_max = std::min(diagonal, this->nor);

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

            /**
             * @brief Generates the starting coordinates in both list for all threads
             */
            void generateThreadStartingCoord() {
                list_a_coord = new int_type[this->threads+1];
                list_b_coord = new int_type[this->threads+1];
                
                list_a_coord[0] = 0;
                list_b_coord[0] = 0;

                const int_type* row_end_offsets = this->row_start + 1; // Merge list A
                const int_type num_merge_items = this->nor + this->nnz;
                const int_type items_per_thread = (num_merge_items + this->threads - 1) / this->threads;
                
                int_type diagonal = 0;
                std::tuple<int_type, int_type> thread_coord_end;
                for (int pid = 0; pid < this->threads; ++pid) {
                    diagonal = std::min(diagonal + items_per_thread, num_merge_items);
                    thread_coord_end = searchPathOnDiag(diagonal, row_end_offsets);

                    list_a_coord[pid+1] = std::get<0>(thread_coord_end);
                    list_b_coord[pid+1] = std::get<1>(thread_coord_end);
                }
            }

        public:
            // Base constructor
            CRS_Merge() {}

            // Base constructor
            CRS_Merge(int threads): pwm::CRSOMP<T, int_type>(threads) {
                if (this->threads == -1) {
                    this->threads = omp_get_max_threads();
                }
            }

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * Calls the normal OMP initializer and then generates datastructures which say where a specific thread starts and ends
             *
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                pwm::CRSOMP<T, int_type>::generatePoissonMatrix(m, n, partitions);

                generateThreadStartingCoord();
            }

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * Calls the CRSOMP constructor and then generates datastructures which say where a specific thread starts and ends
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partition_am) {
                pwm::CRSOMP<T, int_type>::loadFromTriplets(input, partition_am);

                generateThreadStartingCoord();
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
                const int_type* row_end_offsets = this->row_start + 1; // Merge list A

                int_type row_carry_out[this->threads];
                T value_carry_out[this->threads];

                // Parallel section: each thread processes 1 loop iteration
                #pragma omp parallel for schedule(static) num_threads(this->threads)
                for (int tid = 0; tid < this->threads; ++tid) {
                    int_type thread_a_coord = list_a_coord[tid];
                    int_type thread_b_coord = list_b_coord[tid];
                    const int_type thread_a_coord_end = list_a_coord[tid+1];
                    const int_type thread_b_coord_end = list_b_coord[tid+1];

                    // Consume merge items for every whole row
                    T running_total = 0.;
                    for (; thread_a_coord < thread_a_coord_end; ++thread_a_coord) {
                        for (; thread_b_coord < row_end_offsets[thread_a_coord]; ++thread_b_coord) {
                            running_total += this->data_arr[thread_b_coord]*x[this->col_ind[thread_b_coord]];
                        }

                        y[thread_a_coord] = running_total;
                        running_total = 0.;
                    }

                    // Consume last row (if its a partial row)
                    for (; thread_b_coord < thread_b_coord_end; ++thread_b_coord) {
                        running_total += this->data_arr[thread_b_coord] * x[this->col_ind[thread_b_coord]];
                    }

                    // Save carry results
                    row_carry_out[tid] = thread_a_coord_end;
                    value_carry_out[tid] = running_total;
                }

                // Fix the carry results
                for (int tid = 0; tid < this->threads; ++tid) {
                    if (row_carry_out[tid] < this->nor) {
                        y[row_carry_out[tid]] += value_carry_out[tid];
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRS_MERGE_HPP