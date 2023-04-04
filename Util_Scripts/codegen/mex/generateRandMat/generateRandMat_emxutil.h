/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat_emxutil.h
 *
 * Code generation for function 'generateRandMat_emxutil'
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
void emxCopyStruct_sparse(const emlrtStack *sp, b_sparse *dst,
                          const b_sparse *src, const emlrtRTEInfo *srcLocation);

void emxCopy_int32_T(const emlrtStack *sp, emxArray_int32_T **dst,
                     emxArray_int32_T *const *src,
                     const emlrtRTEInfo *srcLocation);

void emxCopy_real_T(const emlrtStack *sp, emxArray_real_T **dst,
                    emxArray_real_T *const *src,
                    const emlrtRTEInfo *srcLocation);

void emxEnsureCapacity_boolean_T(const emlrtStack *sp,
                                 emxArray_boolean_T *emxArray, int32_T oldNumel,
                                 const emlrtRTEInfo *srcLocation);

void emxEnsureCapacity_cell_wrap_0(const emlrtStack *sp,
                                   emxArray_cell_wrap_0 *emxArray,
                                   int32_T oldNumel,
                                   const emlrtRTEInfo *srcLocation);

void emxEnsureCapacity_int32_T(const emlrtStack *sp, emxArray_int32_T *emxArray,
                               int32_T oldNumel,
                               const emlrtRTEInfo *srcLocation);

void emxEnsureCapacity_real_T(const emlrtStack *sp, emxArray_real_T *emxArray,
                              int32_T oldNumel,
                              const emlrtRTEInfo *srcLocation);

void emxEnsureCapacity_sparse(const emlrtStack *sp, emxArray_sparse *emxArray,
                              int32_T oldNumel,
                              const emlrtRTEInfo *srcLocation);

void emxExpand_cell_wrap_0(const emlrtStack *sp, emxArray_cell_wrap_0 *emxArray,
                           int32_T fromIndex, int32_T toIndex,
                           const emlrtRTEInfo *srcLocation);

void emxExpand_sparse(const emlrtStack *sp, emxArray_sparse *emxArray,
                      int32_T fromIndex, int32_T toIndex,
                      const emlrtRTEInfo *srcLocation);

void emxFreeStruct_cell_wrap_0(const emlrtStack *sp, cell_wrap_0 *pStruct);

void emxFreeStruct_sparse(const emlrtStack *sp, b_sparse *pStruct);

void emxFree_boolean_T(const emlrtStack *sp, emxArray_boolean_T **pEmxArray);

void emxFree_cell_wrap_0(const emlrtStack *sp,
                         emxArray_cell_wrap_0 **pEmxArray);

void emxFree_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray);

void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

void emxFree_sparse(const emlrtStack *sp, emxArray_sparse **pEmxArray);

void emxInitStruct_cell_wrap_0(const emlrtStack *sp, cell_wrap_0 *pStruct,
                               const emlrtRTEInfo *srcLocation);

void emxInitStruct_sparse(const emlrtStack *sp, b_sparse *pStruct,
                          const emlrtRTEInfo *srcLocation, boolean_T doPush);

void emxInit_boolean_T(const emlrtStack *sp, emxArray_boolean_T **pEmxArray,
                       const emlrtRTEInfo *srcLocation);

void emxInit_cell_wrap_0(const emlrtStack *sp, emxArray_cell_wrap_0 **pEmxArray,
                         const emlrtRTEInfo *srcLocation);

void emxInit_int32_T(const emlrtStack *sp, emxArray_int32_T **pEmxArray,
                     const emlrtRTEInfo *srcLocation, boolean_T doPush);

void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
                    int32_T numDimensions, const emlrtRTEInfo *srcLocation,
                    boolean_T doPush);

void emxInit_sparse(const emlrtStack *sp, emxArray_sparse **pEmxArray,
                    const emlrtRTEInfo *srcLocation);

void emxTrim_cell_wrap_0(const emlrtStack *sp, emxArray_cell_wrap_0 *emxArray,
                         int32_T fromIndex, int32_T toIndex);

void emxTrim_sparse(const emlrtStack *sp, emxArray_sparse *emxArray,
                    int32_T fromIndex, int32_T toIndex);

/* End of code generation (generateRandMat_emxutil.h) */
