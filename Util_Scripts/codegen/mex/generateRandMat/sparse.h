/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sparse.h
 *
 * Code generation for function 'sparse'
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
void assertValidIndexArg(const emlrtStack *sp, const emxArray_real_T *s,
                         emxArray_int32_T *sint);

void assertValidSize(const emlrtStack *sp, int64_T s);

void permuteVector(const emlrtStack *sp, const emxArray_int32_T *idx,
                   emxArray_int32_T *y);

boolean_T sparse_full(const emlrtStack *sp, const emxArray_boolean_T *this_d,
                      const emxArray_int32_T *this_colidx);

void sparse_ne(const emlrtStack *sp, const emxArray_real_T *a_d,
               const emxArray_int32_T *a_colidx, emxArray_boolean_T *s_d,
               emxArray_int32_T *s_colidx, emxArray_int32_T *s_rowidx);

void sparse_parenAssign(const emlrtStack *sp, b_sparse *this, real_T varargin_1,
                        int64_T varargin_2);

void sparse_parenReference(const emlrtStack *sp, const emxArray_real_T *this_d,
                           const emxArray_int32_T *this_colidx,
                           const emxArray_int32_T *this_rowidx, int32_T this_m,
                           int32_T this_n, real_T varargin_1,
                           int64_T varargin_2, emxArray_real_T *s_d,
                           emxArray_int32_T *s_colidx,
                           emxArray_int32_T *s_rowidx);

/* End of code generation (sparse.h) */
