/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * spalloc.h
 *
 * Code generation for function 'spalloc'
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
void spalloc(const emlrtStack *sp, int64_T m, int64_T n, int64_T nzmax,
             b_sparse *s);

/* End of code generation (spalloc.h) */
