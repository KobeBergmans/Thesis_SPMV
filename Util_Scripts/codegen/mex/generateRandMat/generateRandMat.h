/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat.h
 *
 * Code generation for function 'generateRandMat'
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
emlrtCTX emlrtGetRootTLSGlobal(void);

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData);

void generateRandMat(const emlrtStack *sp, real_T size, real_T avg_line,
                     real_T var_line, real_T var_block, b_sparse *A);

int32_T getThreadID(void);

void getThreadID_init(const emlrtStack *sp);

/* End of code generation (generateRandMat.h) */
