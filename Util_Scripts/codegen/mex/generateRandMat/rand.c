/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rand.c
 *
 * Code generation for function 'rand'
 *
 */

/* Include files */
#include "rand.h"
#include "eml_rand.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo fe_emlrtRSI = {
    107,    /* lineNo */
    "rand", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/rand.m" /* pathName
                                                                      */
};

/* Function Definitions */
real_T b_rand(const emlrtStack *sp)
{
  emlrtStack st;
  real_T r;
  st.prev = sp;
  st.tls = sp->tls;
  if (!emlrtIsInParallelRegion((emlrtCTX)sp)) {
    emlrtRandu(&r, 1);
  } else {
    st.site = &fe_emlrtRSI;
    r = b_eml_rand(&st);
  }
  return r;
}

/* End of code generation (rand.c) */
