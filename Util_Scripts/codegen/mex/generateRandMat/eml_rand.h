/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_rand.h
 *
 * Code generation for function 'eml_rand'
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
real_T b_eml_rand(const emlrtStack *sp);

void eml_rand(const emlrtStack *sp, int64_T varargin_1, emxArray_real_T *r);

void eml_rand_free(const emlrtStack *sp);

void eml_rand_init(const emlrtStack *sp);

void eml_rand_swap(void);

/* End of code generation (eml_rand.h) */
