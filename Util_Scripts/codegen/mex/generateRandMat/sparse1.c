/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sparse1.c
 *
 * Code generation for function 'sparse1'
 *
 */

/* Include files */
#include "sparse1.h"
#include "eml_int_forloop_overflow_check.h"
#include "fillIn.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo of_emlrtRSI = {
    119,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo pf_emlrtRSI = {
    120,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo qf_emlrtRSI = {
    126,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo rf_emlrtRSI = {
    138,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo sf_emlrtRSI = {
    147,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo tf_emlrtRSI = {
    209,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo vf_emlrtRSI = {
    1672,          /* lineNo */
    "locSortrows", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo wf_emlrtRSI = {
    1674,          /* lineNo */
    "locSortrows", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo xf_emlrtRSI = {
    1675,          /* lineNo */
    "locSortrows", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo kg_emlrtRSI = {
    44,         /* lineNo */
    "minOrMax", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo lg_emlrtRSI = {
    79,        /* lineNo */
    "maximum", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo mg_emlrtRSI =
    {
        225,             /* lineNo */
        "unaryMinOrMax", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo ng_emlrtRSI =
    {
        312,                     /* lineNo */
        "unaryMinOrMaxDispatch", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo og_emlrtRSI =
    {
        353,          /* lineNo */
        "minOrMax1D", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRTEInfo r_emlrtRTEI = {
    111,             /* lineNo */
    35,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo s_emlrtRTEI = {
    116,             /* lineNo */
    35,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo t_emlrtRTEI = {
    148,             /* lineNo */
    43,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo u_emlrtRTEI = {
    153,             /* lineNo */
    43,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo qc_emlrtRTEI = {
    125,      /* lineNo */
    44,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo rc_emlrtRTEI = {
    13,       /* lineNo */
    1,        /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/sparse.m" /* pName
                                                                        */
};

static emlrtRTEInfo sc_emlrtRTEI = {
    119,      /* lineNo */
    13,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo tc_emlrtRTEI = {
    120,      /* lineNo */
    13,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo uc_emlrtRTEI = {
    125,      /* lineNo */
    13,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

/* Function Definitions */
void sparse(const emlrtStack *sp, const emxArray_real_T *varargin_1,
            const emxArray_real_T *varargin_2,
            const emxArray_real_T *varargin_3, int64_T varargin_4,
            int64_T varargin_5, b_sparse *y)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack st;
  emxArray_int32_T *cidxInt;
  emxArray_int32_T *ridxInt;
  emxArray_int32_T *sortedIndices;
  const real_T *varargin_3_data;
  int32_T i;
  int32_T k;
  int32_T maxr;
  int32_T nc;
  int32_T numalloc;
  int32_T *cidxInt_data;
  int32_T *ridxInt_data;
  int32_T *sortedIndices_data;
  st.prev = sp;
  st.tls = sp->tls;
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
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  varargin_3_data = varargin_3->data;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  st.site = &pe_emlrtRSI;
  nc = varargin_2->size[0];
  if ((varargin_1->size[0] != varargin_2->size[0]) ||
      (varargin_3->size[0] != varargin_2->size[0])) {
    emlrtErrorWithMessageIdR2018a(&st, &r_emlrtRTEI, "MATLAB:samelen",
                                  "MATLAB:samelen", 0);
  }
  if ((varargin_3->size[0] != varargin_2->size[0]) &&
      (varargin_3->size[0] != varargin_1->size[0])) {
    emlrtErrorWithMessageIdR2018a(&st, &s_emlrtRTEI, "MATLAB:samelen",
                                  "MATLAB:samelen", 0);
  }
  emxInit_int32_T(&st, &ridxInt, &sc_emlrtRTEI, true);
  b_st.site = &of_emlrtRSI;
  assertValidIndexArg(&b_st, varargin_1, ridxInt);
  emxInit_int32_T(&st, &cidxInt, &tc_emlrtRTEI, true);
  b_st.site = &pf_emlrtRSI;
  assertValidIndexArg(&b_st, varargin_2, cidxInt);
  emxInit_int32_T(&st, &sortedIndices, &uc_emlrtRTEI, true);
  i = sortedIndices->size[0];
  sortedIndices->size[0] = varargin_2->size[0];
  emxEnsureCapacity_int32_T(&st, sortedIndices, i, &qc_emlrtRTEI);
  sortedIndices_data = sortedIndices->data;
  b_st.site = &qf_emlrtRSI;
  if (varargin_2->size[0] > 2147483646) {
    c_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&c_st);
  }
  for (k = 0; k < nc; k++) {
    sortedIndices_data[k] = k + 1;
  }
  b_st.site = &rf_emlrtRSI;
  c_st.site = &vf_emlrtRSI;
  introsort(&c_st, sortedIndices, cidxInt->size[0], cidxInt, ridxInt);
  sortedIndices_data = sortedIndices->data;
  c_st.site = &wf_emlrtRSI;
  permuteVector(&c_st, sortedIndices, cidxInt);
  cidxInt_data = cidxInt->data;
  c_st.site = &xf_emlrtRSI;
  permuteVector(&c_st, sortedIndices, ridxInt);
  ridxInt_data = ridxInt->data;
  b_st.site = &fd_emlrtRSI;
  assertValidSize(&b_st, varargin_4);
  b_st.site = &ed_emlrtRSI;
  assertValidSize(&b_st, varargin_5);
  y->m = (int32_T)varargin_4;
  y->n = (int32_T)varargin_5;
  if (ridxInt->size[0] != 0) {
    b_st.site = &sf_emlrtRSI;
    c_st.site = &ac_emlrtRSI;
    d_st.site = &kg_emlrtRSI;
    e_st.site = &lg_emlrtRSI;
    f_st.site = &mg_emlrtRSI;
    numalloc = ridxInt->size[0];
    g_st.site = &ng_emlrtRSI;
    maxr = ridxInt_data[0];
    h_st.site = &og_emlrtRSI;
    if (ridxInt->size[0] > 2147483646) {
      i_st.site = &yb_emlrtRSI;
      b_check_forloop_overflow_error(&i_st);
    }
    for (k = 2; k <= numalloc; k++) {
      i = ridxInt_data[k - 1];
      if (maxr < i) {
        maxr = i;
      }
    }
    if (maxr > (int32_T)varargin_4) {
      emlrtErrorWithMessageIdR2018a(&st, &t_emlrtRTEI,
                                    "Coder:builtins:IndexOutOfBounds",
                                    "Coder:builtins:IndexOutOfBounds", 6, 12,
                                    maxr, 12, 1, 12, (int32_T)varargin_4);
    }
  }
  if ((cidxInt->size[0] != 0) &&
      (cidxInt_data[cidxInt->size[0] - 1] > (int32_T)varargin_5)) {
    emlrtErrorWithMessageIdR2018a(
        &st, &u_emlrtRTEI, "Coder:builtins:IndexOutOfBounds",
        "Coder:builtins:IndexOutOfBounds", 6, 12,
        cidxInt_data[cidxInt->size[0] - 1], 12, 1, 12, (int32_T)varargin_5);
  }
  numalloc = muIntScalarMax_sint32(varargin_2->size[0], 1);
  i = y->d->size[0];
  y->d->size[0] = numalloc;
  emxEnsureCapacity_real_T(&st, y->d, i, &rc_emlrtRTEI);
  for (i = 0; i < numalloc; i++) {
    y->d->data[i] = 0.0;
  }
  y->maxnz = numalloc;
  if ((int32_T)varargin_5 + 1 < 0) {
    emlrtNonNegativeCheckR2012b((int32_T)varargin_5 + 1, &ub_emlrtDCI, &st);
  }
  i = y->colidx->size[0];
  y->colidx->size[0] = (int32_T)varargin_5 + 1;
  emxEnsureCapacity_int32_T(&st, y->colidx, i, &hc_emlrtRTEI);
  y->colidx->data[0] = 1;
  i = y->rowidx->size[0];
  y->rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(&st, y->rowidx, i, &rc_emlrtRTEI);
  for (i = 0; i < numalloc; i++) {
    y->rowidx->data[i] = 0;
  }
  numalloc = 0;
  maxr = (int32_T)varargin_5;
  b_st.site = &cd_emlrtRSI;
  if ((int32_T)varargin_5 > 2147483646) {
    c_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&c_st);
  }
  for (k = 0; k < maxr; k++) {
    while ((numalloc + 1 <= nc) && (cidxInt_data[numalloc] == k + 1)) {
      y->rowidx->data[numalloc] = ridxInt_data[numalloc];
      numalloc++;
    }
    y->colidx->data[k + 1] = numalloc + 1;
  }
  emxFree_int32_T(&st, &cidxInt);
  emxFree_int32_T(&st, &ridxInt);
  b_st.site = &tf_emlrtRSI;
  for (k = 0; k < nc; k++) {
    y->d->data[k] = varargin_3_data[sortedIndices_data[k] - 1];
  }
  emxFree_int32_T(&st, &sortedIndices);
  b_st.site = &bd_emlrtRSI;
  sparse_fillIn(y);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

/* End of code generation (sparse1.c) */
