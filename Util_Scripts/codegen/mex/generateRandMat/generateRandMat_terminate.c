/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat_terminate.c
 *
 * Code generation for function 'generateRandMat_terminate'
 *
 */

/* Include files */
#include "generateRandMat_terminate.h"
#include "_coder_generateRandMat_mex.h"
#include "eml_rand.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "generateRandMat_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void generateRandMat_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  c_eml_rand_mt19937ar_stateful_f(&st);
  eml_rand_free(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void generateRandMat_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (generateRandMat_terminate.c) */
