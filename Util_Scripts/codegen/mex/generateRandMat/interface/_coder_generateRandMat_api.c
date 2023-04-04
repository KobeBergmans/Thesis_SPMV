/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generateRandMat_api.c
 *
 * Code generation for function '_coder_generateRandMat_api'
 *
 */

/* Include files */
#include "_coder_generateRandMat_api.h"
#include "generateRandMat.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_mexutil.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRTEInfo wc_emlrtRTEI = {
    1,                            /* lineNo */
    1,                            /* colNo */
    "_coder_generateRandMat_api", /* fName */
    ""                            /* pName */
};

/* Function Declarations */
static const mxArray *e_emlrt_marshallOut(const b_sparse u);

/* Function Definitions */
static const mxArray *e_emlrt_marshallOut(const b_sparse u)
{
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateSparse(&u.d->data[0], &u.colidx->data[0],
                                    &u.rowidx->data[0], u.m, u.n, u.maxnz,
                                    mxDOUBLE_CLASS, mxREAL));
  return y;
}

void generateRandMat_api(const mxArray *const prhs[4], const mxArray **plhs)
{
  b_sparse A;
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real_T avg_line;
  real_T size;
  real_T var_block;
  real_T var_line;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  /* Marshall function inputs */
  size = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "size");
  avg_line = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "avg_line");
  var_line = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "var_line");
  var_block = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "var_block");
  /* Invoke the target function */
  emxInitStruct_sparse(&st, &A, &wc_emlrtRTEI, true);
  generateRandMat(&st, size, avg_line, var_line, var_block, &A);
  /* Marshall function outputs */
  *plhs = e_emlrt_marshallOut(A);
  emxFreeStruct_sparse(&st, &A);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_generateRandMat_api.c) */
