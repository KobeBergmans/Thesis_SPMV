/**
 * @file VectorUtil.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility functions to perform vector operations 
 * @version 0.1
 * @date 2022-10-01
 */

#ifndef PWM_VECTORUTILL_HPP
#define PWM_VECTORUTILL_HPP

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>

namespace pwm
{
    /**
     * @brief Calculate 2 norm of vector
     *
     * @param x Vector 
     * @param size Vector size
     */
    template<typename T, typename int_type>
    T norm2(const T* x, int_type size) {
        return std::sqrt(std::inner_product(x, x+size, x, 0.));
    }

    /**
     * @brief Normalize vector
     * 
     * @param x Vector 
     * @param size Vector size
     */
    template<typename T, typename int_type>
    void normalize(T* x, int_type size) {
        T norm = norm2(x, size);

        for (int_type i = 0; i < size; ++i) {
            x[i] /= norm;
        }
    }

    /**
     * @brief Print vector
     *
     * @param x Vector 
     * @param size Vector size
     */
    template<typename T, typename int_type>
    void printVector(T* x, int_type size) {
        for (int_type i = 0; i < size; ++i) {
            std::cout << x[i] << ", ";
        }
        std::cout << std::endl;
    }

    template<typename T, typename int_type>
    void fillPoisson(T* data_arr, int_type* row_start, int_type* col_ind, int_type m, int_type n) {
        // Fill data rows
        // TODO: Can this be more efficient?
        int_type nnz_index = 0;
        for (int_type row = 0; row < m*n; ++row) {

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

#endif // PWM_VECTORUTILL_HPP