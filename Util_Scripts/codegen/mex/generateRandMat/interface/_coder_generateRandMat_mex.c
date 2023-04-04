/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_generateRandMat_mex.c
 *
 * Code generation for function '_coder_generateRandMat_mex'
 *
 */

/* Include files */
#include "_coder_generateRandMat_mex.h"
#include "_coder_generateRandMat_api.h"
#include "generateRandMat.h"
#include "generateRandMat_data.h"
#include "generateRandMat_initialize.h"
#include "generateRandMat_terminate.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void generateRandMat_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                 const mxArray *prhs[4])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 4, 4,
                        15, "generateRandMat");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "generateRandMat");
  }
  /* Call the function. */
  generateRandMat_api(prhs, &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  static jmp_buf emlrtJBEnviron;
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexAtExit(&generateRandMat_atexit);
  emlrtLoadMATLABLibrary("sys/os/glnxa64/libiomp5.so");
  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&generateRandMat_nestLockGlobal);
  /* Module initialization. */
  generateRandMat_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    generateRandMat_mexFunction(nlhs, plhs, nrhs, prhs);
    /* Module termination. */
    generateRandMat_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&generateRandMat_nestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&generateRandMat_nestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                           &emlrtLockerFunction, omp_get_num_procs(), NULL,
                           "UTF-8", true);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_generateRandMat_mex.c) */
