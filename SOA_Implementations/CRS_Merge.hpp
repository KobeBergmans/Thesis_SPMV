/**
 * @file CRS_Merge.hpp
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

#include "../Env_Implementations/CRSOMP.hpp"

#include <omp.h>

namespace pwm {
    template<typename T, typename int_type>
    class CRS_Merge: public pwm::CRSOMP<T, int_type> {
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
            CRS_Merge(int threads): pwm::CRSOMP<T, int_type>(threads) {
                if (this->threads == -1) {
                    this->threads = omp_get_max_threads();
                }
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
                int_type* row_end_offsets = this->row_start + 1; // Merge list A
                int_type num_merge_items = this->nor + this->nnz;
                int_type items_per_thread = (num_merge_items + this->threads - 1) / this->threads;

                int_type row_carry_out[this->threads];
                T value_carry_out[this->threads];

                // Parallel section: each thread processes 1 loop iteration
                #pragma omp parallel for schedule(static) num_threads(this->threads)
                for (int tid = 0; tid < this->threads; ++tid) {
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