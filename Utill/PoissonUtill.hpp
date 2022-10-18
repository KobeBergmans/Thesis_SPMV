/**
 * @file PoissonUtil.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility functions to fill and generate 2D discretized poisson matrix
 * @version 0.2
 * @date 2022-10-18
 */

#ifndef PWM_POISSONUTILL_HPP
#define PWM_POISSONUTILL_HPP

#include "omp.h"

namespace pwm {
    /**
     * @brief Fill the 2D discretized Poisson matrix.
     * 
     * https://en.wikipedia.org/wiki/Discrete_Poisson_equation
     * 
     * With the first_row and last_row parameters it is possible to put part of the Poisson matrix into CRS format.
     * 
     * @param data_arr Data array of CRS format
     * @param row_start Row_start array of CRS format
     * @param col_ind Column indices array of CRS format
     * @param m The amount of discretization steps in the x direction
     * @param n The amount of discretization steps in the y direction
     * @param first_row First row of the matrix which is put into CRS format
     * @param last_row Last row of the matrix which is put into CRS format
     */
    template<typename T, typename int_type>
    void fillPoisson(T* data_arr, int_type* row_start, int_type* col_ind, int_type m, int_type n, int_type first_row = 0, int_type last_row = 0) {
        if (last_row == 0) {
            last_row = m*n;
        }

        row_start[0] = 0;

        // Fill data rows
        int_type nnz_index = 0;
        for (int_type row = first_row; row < last_row; ++row) {

            // Check for identity before D
            if (row >= m) {
                // Diagonal of I
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row - m;
                nnz_index++;
            }

            // Check if we are not on the first row of D
            if (row % m != 0) {
                // Subdiagonal of D
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row-1;
                nnz_index++;
            } 

            // Diagonal of D
            data_arr[nnz_index] = 4;
            col_ind[nnz_index] = row;
            nnz_index++;

            // Check if we are not on the last row of D
            if (row % m != m-1) {
                // Superdiagonal of D
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row+1;
                nnz_index++;
            }

            // Check for identity after D
            if (row < m*n - n) {
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = m+row;
                nnz_index++;
            }

            row_start[row-first_row+1] = nnz_index;
        }
    }

    /**
     * @brief Fill the 2D discretized Poisson matrix.
     * 
     * https://en.wikipedia.org/wiki/Discrete_Poisson_equation
     * 
     * With the first_row and last_row parameters it is possible to put part of the Poisson matrix into CRS format.
     * 
     * Loop is parallelized using OpenMP. This is done to avoid the first touch problem if the main thread initializes all datastructures.
     * 
     * @param data_arr Data array of CRS format
     * @param row_start Row_start array of CRS format
     * @param col_ind Column indices array of CRS format
     * @param m The amount of discretization steps in the x direction
     * @param n The amount of discretization steps in the y direction
     * @param first_row First row of the matrix which is put into CRS format
     * @param last_row Last row of the matrix which is put into CRS format
     */
    template<typename T, typename int_type>
    void fillPoissonOMP(T* data_arr, int_type* row_start, int_type* col_ind, int_type m, int_type n) {
        int_type last_row = m*n;
        row_start[0] = 0;

        // Fill data rows
        #pragma omp parallel for shared(data_arr, row_start, col_ind) schedule(dynamic, 8)
        for (int_type row = 0; row < last_row; ++row) {
            // Calculate nnz_index (this is needed because this variable can't be shared anymore).
            int_type nnz_index = 0;
            if (row > 0) {
                nnz_index += std::max(0, row - m);
                nnz_index += (row/m)*(m-1) + row%m;
                nnz_index += row;
                nnz_index += (row/m)*(m-1) + row%m;
                nnz_index += std::min(row, m*n - n);
            
                if (row % m >= 1) nnz_index -= 1;
            }            

            // Check for identity before D
            if (row >= m) {
                // Diagonal of I
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row - m;
                nnz_index++;
            }

            // Check if we are not on the first row of D
            if (row % m != 0) {
                // Subdiagonal of D
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row-1;
                nnz_index++;
            } 

            // Diagonal of D
            data_arr[nnz_index] = 4;
            col_ind[nnz_index] = row;
            nnz_index++;

            // Check if we are not on the last row of D
            if (row % m != m-1) {
                // Superdiagonal of D
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = row+1;
                nnz_index++;
            }

            // Check for identity after D
            if (row < m*n - n) {
                data_arr[nnz_index] = -1;
                col_ind[nnz_index] = m+row;
                nnz_index++;
            }

            row_start[row+1] = nnz_index;
        }
    }
} // namespace pwm

#endif //PWM_POISSONUTILL_HPP