/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_rand_mt19937ar_stateful.h
 *
 * Code generation for function 'eml_rand_mt19937ar_stateful'
 *
 */

#pragma once

/* Include files */
#include "generateRandMat_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
real_T b_eml_rand_mt19937ar_stateful(const emlrtStack *sp);

void c_eml_rand_mt19937ar_stateful_f(const emlrtStack *sp);

void c_eml_rand_mt19937ar_stateful_i(const emlrtStack *sp);

void c_eml_rand_mt19937ar_stateful_s(boolean_T aToMain);

void eml_rand_mt19937ar_stateful(const emlrtStack *sp, int64_T varargin_1,
                                 emxArray_real_T *r);

/* End of code generation (eml_rand_mt19937ar_stateful.h) */
