/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * spalloc.c
 *
 * Code generation for function 'spalloc'
 *
 */

/* Include files */
#include "spalloc.h"
#include "eml_int_forloop_overflow_check.h"
#include "fillIn.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo xc_emlrtRSI = {
    7,         /* lineNo */
    "spalloc", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/spalloc.m" /* pathName
                                                                         */
};

static emlrtRSInfo yc_emlrtRSI = {
    1486,             /* lineNo */
    "sparse/spalloc", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo ad_emlrtRSI = {
    1482,                 /* lineNo */
    "sparse/spallocLike", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo dd_emlrtRSI = {
    176,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRTEInfo i_emlrtRTEI = {
    180,             /* lineNo */
    39,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo j_emlrtRTEI = {
    178,             /* lineNo */
    39,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo gc_emlrtRTEI = {
    7,         /* lineNo */
    1,         /* colNo */
    "spalloc", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/spalloc.m" /* pName
                                                                         */
};

/* Function Definitions */
void spalloc(const emlrtStack *sp, int64_T m, int64_T n, int64_T nzmax,
             b_sparse *s)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  int32_T c;
  int32_T numalloc;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &xc_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  b_st.site = &yc_emlrtRSI;
  c_st.site = &ad_emlrtRSI;
  d_st.site = &fd_emlrtRSI;
  assertValidSize(&d_st, m);
  d_st.site = &ed_emlrtRSI;
  assertValidSize(&d_st, n);
  s->m = (int32_T)m;
  s->n = (int32_T)n;
  d_st.site = &dd_emlrtRSI;
  assertValidSize(&d_st, nzmax);
  if (nzmax < 0L) {
    emlrtErrorWithMessageIdR2018a(&c_st, &j_emlrtRTEI,
                                  "Coder:toolbox:SparseNzmaxTooSmall",
                                  "Coder:toolbox:SparseNzmaxTooSmall", 0);
  }
  if (nzmax < 0L) {
    emlrtErrorWithMessageIdR2018a(&c_st, &i_emlrtRTEI,
                                  "Coder:toolbox:SparseNzmaxTooSmall",
                                  "Coder:toolbox:SparseNzmaxTooSmall", 0);
  }
  numalloc = (int32_T)nzmax;
  numalloc = muIntScalarMax_sint32(numalloc, 1);
  c = s->d->size[0];
  s->d->size[0] = numalloc;
  emxEnsureCapacity_real_T(&c_st, s->d, c, &gc_emlrtRTEI);
  for (c = 0; c < numalloc; c++) {
    s->d->data[c] = 0.0;
  }
  s->maxnz = numalloc;
  if ((int32_T)n + 1 < 0) {
    emlrtNonNegativeCheckR2012b((int32_T)n + 1, &ub_emlrtDCI, &c_st);
  }
  c = s->colidx->size[0];
  s->colidx->size[0] = (int32_T)n + 1;
  emxEnsureCapacity_int32_T(&c_st, s->colidx, c, &hc_emlrtRTEI);
  s->colidx->data[0] = 1;
  c = s->rowidx->size[0];
  s->rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(&c_st, s->rowidx, c, &gc_emlrtRTEI);
  for (c = 0; c < numalloc; c++) {
    s->rowidx->data[c] = 0;
  }
  numalloc = (int32_T)n;
  d_st.site = &cd_emlrtRSI;
  if ((int32_T)n > 2147483646) {
    e_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&e_st);
  }
  for (c = 0; c < numalloc; c++) {
    s->colidx->data[c + 1] = 1;
  }
  d_st.site = &bd_emlrtRSI;
  sparse_fillIn(s);
}

/* End of code generation (spalloc.c) */
