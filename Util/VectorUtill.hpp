/**
 * @file VectorUtill.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility functions to perform vector operations 
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
} // namespace pwm

#endif // PWM_VECTORUTILL_HPP