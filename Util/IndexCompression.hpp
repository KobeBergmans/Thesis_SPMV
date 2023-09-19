/**
 * @file IndexCompression.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Helper functions for index compression
 */

#ifndef PWM_INDEXCOMPRESSION_HPP
#define PWM_INDEXCOMPRESSION_HPP

#include "../Util/Constants.hpp"

namespace pwm {
    /**
     * @brief Transforms compressed index to the corresponding row index
     * 
     * @param input Compressed input parameter
     * @return compress_index_t Corresponding row index
     */
    inline compress_index_t fromCompressedToRow(const compress_t input) {
        return (compress_index_t)((input & HIGH_BITMASK) >> COORD_BITS);
    }

    /**
     * @brief Transforms compressed index to the corresponding column index
     * 
     * @param input Compressed input parameter
     * @return compress_index_t Corresponding column index
     */
    inline compress_index_t fromCompressedToCol(const compress_t input) {
        return (compress_index_t)(input & LOW_BITMASK);
        }
            
    /**
     * @brief Transforms row and column index to compressed index
     * 
     * @param row Row index to be compressed
     * @param col Column index to be compressed
     * @return compress_t Compressed integer
     */
    inline compress_t fromIndicesToCompressed(const compress_index_t row, const compress_index_t col) {
        return ((compress_t)row << COORD_BITS) | (compress_t)col;
    }    
} // namespace pwm

#endif // PWM_INDEXCOMPRESSION_HPP