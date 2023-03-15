/**
 * @file Math.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Mathematical utility functions
 */

#ifndef PWM_MATH_HPP
#define PWM_MATH_HPP

namespace pwm {
    /**
     * @brief Returns the ceiling of the division of 2 integers
     * 
     * @param x First integer
     * @param y Second integer
     * @return int_type Ceiling of x/y
     */
    template<typename int_type>
    int_type integerCeil(const int_type x, const int_type y) {
        return x / y + (x % y != 0);
    }

    /**
     * @brief Performs binary search in an array and returns the index of the leftmost element
     * 
     * https://en.wikipedia.org/wiki/Binary_search_algorithm
     * 
     * @param search_arr Array which needs to be searched
     * @param search_val Value which needs to be searched
     * @param size Size of the array
     * @return int_type Index of the leftmost element in the array with the specified value
     */
    template<typename int_type, typename T>
    int_type binarySearchLeftMost(const T* search_arr, const T search_val, int_type size) {
        int_type left = 0;
        int_type right = size;

        int_type middle;
        while (left < right) {
            middle = (left+right)/2;

            if (search_arr[middle] < search_val) left = middle + 1;
            else right = middle;
        }

        return left;
    }
    
} // namespace pwm

#endif // PWM_MATH_HPP