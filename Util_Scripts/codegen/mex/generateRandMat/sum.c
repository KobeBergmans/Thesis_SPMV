/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "sum.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"

/* Variable Definitions */
static emlrtRSInfo gc_emlrtRSI = {
    20,    /* lineNo */
    "sum", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/sum.m" /* pathName
                                                                     */
};

static emlrtRSInfo hc_emlrtRSI =
    {
        99,        /* lineNo */
        "sumprod", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
        "sumprod.m" /* pathName */
};

static emlrtRSInfo ic_emlrtRSI = {
    74,                      /* lineNo */
    "combineVectorElements", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
    "combineVectorElements.m" /* pathName */
};

static emlrtRSInfo jc_emlrtRSI = {
    107,                /* lineNo */
    "blockedSummation", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
    "blockedSummation.m" /* pathName */
};

static emlrtRSInfo kc_emlrtRSI = {
    22,                    /* lineNo */
    "sumMatrixIncludeNaN", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
    "sumMatrixIncludeNaN.m" /* pathName */
};

static emlrtRSInfo lc_emlrtRSI = {
    42,                 /* lineNo */
    "sumMatrixColumns", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
    "sumMatrixIncludeNaN.m" /* pathName */
};

static emlrtRSInfo mc_emlrtRSI = {
    57,                 /* lineNo */
    "sumMatrixColumns", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/private/"
    "sumMatrixIncludeNaN.m" /* pathName */
};

/* Function Definitions */
real_T sum(const emlrtStack *sp, const emxArray_real_T *x)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  real_T y;
  int32_T ib;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &gc_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  b_st.site = &hc_emlrtRSI;
  c_st.site = &ic_emlrtRSI;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    d_st.site = &jc_emlrtRSI;
    e_st.site = &kc_emlrtRSI;
    if (x->size[0] < 4096) {
      f_st.site = &lc_emlrtRSI;
      y = sumColumnB(&f_st, x, x->size[0]);
    } else {
      int32_T inb;
      int32_T nfb;
      int32_T nleft;
      nfb = (int32_T)((uint32_T)x->size[0] >> 12);
      inb = nfb << 12;
      nleft = x->size[0] - inb;
      y = sumColumnB4(x, 1);
      for (ib = 2; ib <= nfb; ib++) {
        y += sumColumnB4(x, ((ib - 1) << 12) + 1);
      }
      if (nleft > 0) {
        f_st.site = &mc_emlrtRSI;
        y += b_sumColumnB(&f_st, x, nleft, inb + 1);
      }
    }
  }
  return y;
}

/* End of code generation (sum.c) */
