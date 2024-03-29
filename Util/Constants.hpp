/**
 * @file Constants.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Defines the specific constants used throughout the program
 */

#ifndef PWM_CONSTANTS_HPP
#define PWM_CONSTANTS_HPP

#include <cstdint>

// OpenMP chunk size for dynamic scheduling
#define OMP_DYNAMIC_CHUNK_SIZE 512

// Definitions for compressed integers
typedef uint16_t compress_index_t;
typedef uint32_t compress_t;
typedef int16_t bicrs_t;

// Definitions for CSB
#define LOW_BITMASK  0b00000000000000001111111111111111
#define HIGH_BITMASK 0b11111111111111110000000000000000
#define COORD_BITS 16

#define O_DIM_CONST 4
#define O_BETA_CONST 3
#define L2_CACHE_SIZE_MB 1
#define L2_CACHE_MULT 0.85
#define MIN_NNZ_TO_PAR 256

// Definitions for drivers
typedef double data_t;

// Specific case for MKL needed because it does not support unsigned integers
#ifdef MKL
typedef int64_t index_t;
#else
typedef uint32_t index_t;
#endif

// Maximum and minimal value for input vector
#define MIN_IN -100.0
#define MAX_IN 100.0

#endif // PWM_CONSTANTS_HPP
