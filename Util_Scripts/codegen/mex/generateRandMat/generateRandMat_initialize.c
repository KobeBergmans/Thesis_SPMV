/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat_initialize.c
 *
 * Code generation for function 'generateRandMat_initialize'
 *
 */

/* Include files */
#include "generateRandMat_initialize.h"
#include "_coder_generateRandMat_mex.h"
#include "eml_rand.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "generateRandMat.h"
#include "generateRandMat_data.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void generateRandMat_once(const emlrtStack *sp);

/* Function Definitions */
static void generateRandMat_once(const emlrtStack *sp)
{
  emlrtStack st;
  mex_InitInfAndNan();
  st.prev = sp;
  st.tls = sp->tls;
  st.site = NULL;
  getThreadID_init(&st);
  st.site = NULL;
  eml_rand_init(&st);
  st.site = NULL;
  c_eml_rand_mt19937ar_stateful_i(&st);
}

void generateRandMat_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2022b(&st);
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    generateRandMat_once(&st);
  }
}

/* End of code generation (generateRandMat_initialize.c) */
