/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * randn.c
 *
 * Code generation for function 'randn'
 *
 */

/* Include files */
#include "randn.h"
#include "eml_rand.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo nb_emlrtRSI = {
    116,     /* lineNo */
    "randn", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/randn.m" /* pathName
                                                                       */
};

static emlrtRSInfo ob_emlrtRSI = {
    119,     /* lineNo */
    "randn", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/randn.m" /* pathName
                                                                       */
};

static emlrtRSInfo pb_emlrtRSI = {
    40,          /* lineNo */
    "eml_randn", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/private/"
    "eml_randn.m" /* pathName */
};

static emlrtDCInfo sb_emlrtDCI = {
    115,     /* lineNo */
    30,      /* colNo */
    "randn", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/randn.m", /* pName
                                                                        */
    4 /* checkKind */
};

static emlrtRTEInfo dc_emlrtRTEI = {
    115,     /* lineNo */
    24,      /* colNo */
    "randn", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/randn.m" /* pName
                                                                       */
};

/* Function Definitions */
void randn(const emlrtStack *sp, int64_T varargin_1, emxArray_real_T *r)
{
  emlrtStack b_st;
  emlrtStack st;
  real_T *r_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (!emlrtIsInParallelRegion((emlrtCTX)sp)) {
    int32_T i;
    if (!(varargin_1 >= 0.0)) {
      emlrtNonNegativeCheckR2012b((real_T)varargin_1, &sb_emlrtDCI,
                                  (emlrtConstCTX)sp);
    }
    i = r->size[0];
    r->size[0] = (int32_T)(int64_T)muDoubleScalarFloor((real_T)varargin_1);
    emxEnsureCapacity_real_T(sp, r, i, &dc_emlrtRTEI);
    r_data = r->data;
    st.site = &nb_emlrtRSI;
    if ((int32_T)varargin_1 != 0) {
      emlrtRandn(&r_data[0], (int32_T)varargin_1);
    }
  } else {
    st.site = &ob_emlrtRSI;
    b_st.site = &pb_emlrtRSI;
    eml_rand(&b_st, varargin_1, r);
  }
}

/* End of code generation (randn.c) */
