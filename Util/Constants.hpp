/**
 * @file Constants.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Defines the specific constants used throughout the program
 */

#ifndef PWM_CONSTANTS_HPP
#define PWM_CONSTANTS_HPP

#include <cstdint>

// OpenMP chunk size for dynamic scheduling
#define OMP_DYNAMIC_CHUNK_SIZE 500

// Definitions for compressed integers
typedef uint16_t index_t;
typedef uint32_t compress_t;
typedef int16_t bicrs_t;

// Definitions for Block CO-H
#define LOW_BITMASK  0b00000000000000001111111111111111
#define HIGH_BITMASK 0b11111111111111110000000000000000
#define COORD_BITS 16

// Definitions for CSB
#define O_DIM_CONST 4
#define O_BETA_CONST 3
#define L2_CACHE_SIZE_MB 1
#define L2_CACHE_MULT 0.85
#define MIN_NNZ_TO_PAR 256

#endif // PWM_CONSTANTS_HPP
