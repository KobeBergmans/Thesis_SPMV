/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * round.c
 *
 * Code generation for function 'round'
 *
 */

/* Include files */
#include "round.h"
#include "eml_int_forloop_overflow_check.h"
#include "generateRandMat_data.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo wb_emlrtRSI = {
    10,      /* lineNo */
    "round", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elfun/round.m" /* pathName
                                                                     */
};

static emlrtRSInfo xb_emlrtRSI = {
    33,                           /* lineNo */
    "applyScalarFunctionInPlace", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "applyScalarFunctionInPlace.m" /* pathName */
};

/* Function Definitions */
void b_round(const emlrtStack *sp, emxArray_real_T *x)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  real_T *x_data;
  int32_T k;
  int32_T nx;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  x_data = x->data;
  st.site = &wb_emlrtRSI;
  nx = x->size[0];
  b_st.site = &xb_emlrtRSI;
  if (x->size[0] > 2147483646) {
    c_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&c_st);
  }
  for (k = 0; k < nx; k++) {
    x_data[k] = muDoubleScalarRound(x_data[k]);
  }
}

/* End of code generation (round.c) */
