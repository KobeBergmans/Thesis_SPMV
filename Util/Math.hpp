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
    
} // namespace pwm

#endif // PWM_MATH_HPP