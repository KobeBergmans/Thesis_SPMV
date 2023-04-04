/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sparse.c
 *
 * Code generation for function 'sparse'
 *
 */

/* Include files */
#include "sparse.h"
#include "bigProduct.h"
#include "eml_int_forloop_overflow_check.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo gd_emlrtRSI = {
    1627,              /* lineNo */
    "assertValidSize", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo ie_emlrtRSI = {
    250,                     /* lineNo */
    "sparse/parenReference", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo je_emlrtRSI = {
    25,                        /* lineNo */
    "sparse/parenReference2D", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenReference2D.m" /* pathName */
};

static emlrtRSInfo ke_emlrtRSI = {
    32,                        /* lineNo */
    "parenReference2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenReference2D.m" /* pathName */
};

static emlrtRSInfo le_emlrtRSI = {
    33,                        /* lineNo */
    "parenReference2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenReference2D.m" /* pathName */
};

static emlrtRSInfo me_emlrtRSI = {
    36,                        /* lineNo */
    "parenReference2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenReference2D.m" /* pathName */
};

static emlrtRSInfo ne_emlrtRSI = {
    327,         /* lineNo */
    "sparse/ne", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo oe_emlrtRSI = {
    189,            /* lineNo */
    "sparse/binOp", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/binOp.m" /* pathName */
};

static emlrtRSInfo qe_emlrtRSI = {
    275,           /* lineNo */
    "sparse/full", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo re_emlrtRSI = {
    264,                  /* lineNo */
    "sparse/parenAssign", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo se_emlrtRSI = {
    66,                     /* lineNo */
    "sparse/parenAssign2D", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo te_emlrtRSI = {
    77,                     /* lineNo */
    "parenAssign2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo ue_emlrtRSI = {
    78,                     /* lineNo */
    "parenAssign2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo ve_emlrtRSI = {
    81,                     /* lineNo */
    "parenAssign2DNumeric", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo we_emlrtRSI = {
    119,                        /* lineNo */
    "parenAssign2DNumericImpl", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo xe_emlrtRSI = {
    115,                        /* lineNo */
    "parenAssign2DNumericImpl", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo ye_emlrtRSI = {
    110,                        /* lineNo */
    "parenAssign2DNumericImpl", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo af_emlrtRSI = {
    329,       /* lineNo */
    "realloc", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo bf_emlrtRSI = {
    337,       /* lineNo */
    "realloc", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo cf_emlrtRSI = {
    342,       /* lineNo */
    "realloc", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo df_emlrtRSI = {
    245,                  /* lineNo */
    "shiftRowidxAndData", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo ef_emlrtRSI = {
    246,                  /* lineNo */
    "shiftRowidxAndData", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo ff_emlrtRSI = {
    264,          /* lineNo */
    "incrColIdx", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pathName */
};

static emlrtRSInfo uf_emlrtRSI = {
    1656,                  /* lineNo */
    "assertValidIndexArg", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRSInfo jg_emlrtRSI = {
    1683,            /* lineNo */
    "permuteVector", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

static emlrtRTEInfo k_emlrtRTEI = {
    1629,              /* lineNo */
    9,                 /* colNo */
    "assertValidSize", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo l_emlrtRTEI = {
    1632,              /* lineNo */
    31,                /* colNo */
    "assertValidSize", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo m_emlrtRTEI = {
    58,                   /* lineNo */
    23,                   /* colNo */
    "assertValidSizeArg", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" /* pName */
};

static emlrtRTEInfo n_emlrtRTEI = {
    64,                   /* lineNo */
    15,                   /* colNo */
    "assertValidSizeArg", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" /* pName */
};

static emlrtRTEInfo o_emlrtRTEI = {
    12,                                   /* lineNo */
    27,                                   /* colNo */
    "sparse/sparse_validateNumericIndex", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/private/validateNumericIndex.m" /* pName */
};

static emlrtRTEInfo p_emlrtRTEI = {
    11,                                   /* lineNo */
    27,                                   /* colNo */
    "sparse/sparse_validateNumericIndex", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/private/validateNumericIndex.m" /* pName */
};

static emlrtRTEInfo v_emlrtRTEI = {
    1658,                  /* lineNo */
    31,                    /* colNo */
    "assertValidIndexArg", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo w_emlrtRTEI = {
    1660,                  /* lineNo */
    31,                    /* colNo */
    "assertValidIndexArg", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo x_emlrtRTEI = {
    1662,                  /* lineNo */
    31,                    /* colNo */
    "assertValidIndexArg", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo cb_emlrtRTEI = {
    237,            /* lineNo */
    13,             /* colNo */
    "sparse/numel", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo ic_emlrtRTEI = {
    250,      /* lineNo */
    17,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo jc_emlrtRTEI = {
    327,      /* lineNo */
    13,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo vc_emlrtRTEI = {
    1653,     /* lineNo */
    27,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo xc_emlrtRTEI = {
    325,             /* lineNo */
    1,               /* colNo */
    "parenAssign2D", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pName */
};

static emlrtRTEInfo yc_emlrtRTEI = {
    326,             /* lineNo */
    1,               /* colNo */
    "parenAssign2D", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/parenAssign2D.m" /* pName */
};

static emlrtRTEInfo ad_emlrtRTEI = {
    264,      /* lineNo */
    17,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

static emlrtRTEInfo bd_emlrtRTEI = {
    1682,     /* lineNo */
    5,        /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

/* Function Definitions */
void assertValidIndexArg(const emlrtStack *sp, const emxArray_real_T *s,
                         emxArray_int32_T *sint)
{
  emlrtStack b_st;
  emlrtStack st;
  const real_T *s_data;
  int32_T k;
  int32_T ns;
  int32_T *sint_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  s_data = s->data;
  ns = s->size[0];
  k = sint->size[0];
  sint->size[0] = s->size[0];
  emxEnsureCapacity_int32_T(sp, sint, k, &vc_emlrtRTEI);
  sint_data = sint->data;
  st.site = &uf_emlrtRSI;
  if (s->size[0] > 2147483646) {
    b_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&b_st);
  }
  for (k = 0; k < ns; k++) {
    if (!(muDoubleScalarFloor(s_data[k]) == s_data[k])) {
      emlrtErrorWithMessageIdR2018a(sp, &v_emlrtRTEI,
                                    "MATLAB:sparsfcn:nonIntegerIndex",
                                    "MATLAB:sparsfcn:nonIntegerIndex", 0);
    }
    if (!(s_data[k] < 2.147483647E+9)) {
      emlrtErrorWithMessageIdR2018a(sp, &w_emlrtRTEI,
                                    "MATLAB:sparsfcn:largeIndex",
                                    "MATLAB:sparsfcn:largeIndex", 0);
    }
    if (!(s_data[k] > 0.0)) {
      emlrtErrorWithMessageIdR2018a(sp, &x_emlrtRTEI,
                                    "MATLAB:sparsfcn:nonPosIndex",
                                    "MATLAB:sparsfcn:nonPosIndex", 0);
    }
    sint_data[k] = (int32_T)s_data[k];
  }
}

void assertValidSize(const emlrtStack *sp, int64_T s)
{
  emlrtStack st;
  real_T d;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &gd_emlrtRSI;
  if ((s < -2147483648L) || (s > 2147483647L)) {
    emlrtErrorWithMessageIdR2018a(
        &st, &m_emlrtRTEI, "Coder:MATLAB:NonIntegerInput",
        "Coder:MATLAB:NonIntegerInput", 4, 12, MIN_int32_T, 12, MAX_int32_T);
  }
  if (s <= 0L) {
    d = 0.0;
  } else {
    d = (real_T)s;
  }
  if (!(d <= 2.147483647E+9)) {
    emlrtErrorWithMessageIdR2018a(&st, &n_emlrtRTEI, "Coder:MATLAB:pmaxsize",
                                  "Coder:MATLAB:pmaxsize", 0);
  }
  if (s < 0L) {
    emlrtErrorWithMessageIdR2018a(sp, &k_emlrtRTEI,
                                  "Coder:toolbox:SparseNegativeSize",
                                  "Coder:toolbox:SparseNegativeSize", 0);
  }
  if (s >= 2147483647L) {
    emlrtErrorWithMessageIdR2018a(
        sp, &l_emlrtRTEI, "Coder:toolbox:SparseMaxSize",
        "Coder:toolbox:SparseMaxSize", 2, 12, MAX_int32_T);
  }
}

void permuteVector(const emlrtStack *sp, const emxArray_int32_T *idx,
                   emxArray_int32_T *y)
{
  emlrtStack b_st;
  emlrtStack st;
  emxArray_int32_T *t;
  const int32_T *idx_data;
  int32_T i;
  int32_T loop_ub;
  int32_T ny;
  int32_T *t_data;
  int32_T *y_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  y_data = y->data;
  idx_data = idx->data;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  ny = y->size[0];
  emxInit_int32_T(sp, &t, &bd_emlrtRTEI, true);
  i = t->size[0];
  t->size[0] = y->size[0];
  emxEnsureCapacity_int32_T(sp, t, i, &bd_emlrtRTEI);
  t_data = t->data;
  loop_ub = y->size[0];
  for (i = 0; i < loop_ub; i++) {
    t_data[i] = y_data[i];
  }
  st.site = &jg_emlrtRSI;
  if (y->size[0] > 2147483646) {
    b_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&b_st);
  }
  for (loop_ub = 0; loop_ub < ny; loop_ub++) {
    y_data[loop_ub] = t_data[idx_data[loop_ub] - 1];
  }
  emxFree_int32_T(sp, &t);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

boolean_T sparse_full(const emlrtStack *sp, const emxArray_boolean_T *this_d,
                      const emxArray_int32_T *this_colidx)
{
  emlrtStack b_st;
  emlrtStack st;
  const int32_T *this_colidx_data;
  int32_T a;
  int32_T cend;
  int32_T idx;
  const boolean_T *this_d_data;
  boolean_T y;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  y = false;
  cend = this_colidx_data[1] - 1;
  a = this_colidx_data[0];
  st.site = &qe_emlrtRSI;
  if ((this_colidx_data[0] <= this_colidx_data[1] - 1) &&
      (this_colidx_data[1] - 1 > 2147483646)) {
    b_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&b_st);
  }
  for (idx = a; idx <= cend; idx++) {
    y = this_d_data[0];
  }
  return y;
}

void sparse_ne(const emlrtStack *sp, const emxArray_real_T *a_d,
               const emxArray_int32_T *a_colidx, emxArray_boolean_T *s_d,
               emxArray_int32_T *s_colidx, emxArray_int32_T *s_rowidx)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  const real_T *a_d_data;
  real_T uniOp_workspace_sa;
  const int32_T *a_colidx_data;
  int32_T i;
  int32_T *s_colidx_data;
  int32_T *s_rowidx_data;
  boolean_T *s_d_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  st.site = &ne_emlrtRSI;
  if (a_colidx_data[a_colidx->size[0] - 1] - 1 > 0) {
    uniOp_workspace_sa = a_d_data[0];
  } else {
    uniOp_workspace_sa = 0.0;
  }
  b_st.site = &oe_emlrtRSI;
  c_st.site = &pe_emlrtRSI;
  i = s_d->size[0];
  s_d->size[0] = 1;
  emxEnsureCapacity_boolean_T(&c_st, s_d, i, &jc_emlrtRTEI);
  s_d_data = s_d->data;
  s_d_data[0] = false;
  i = s_colidx->size[0];
  s_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(&c_st, s_colidx, i, &jc_emlrtRTEI);
  s_colidx_data = s_colidx->data;
  s_colidx_data[0] = 1;
  i = s_rowidx->size[0];
  s_rowidx->size[0] = 1;
  emxEnsureCapacity_int32_T(&c_st, s_rowidx, i, &jc_emlrtRTEI);
  s_rowidx_data = s_rowidx->data;
  s_rowidx_data[0] = 1;
  s_colidx_data[1] = 1;
  if (uniOp_workspace_sa != 0.0) {
    s_rowidx_data[0] = 1;
    s_d_data[0] = true;
    s_colidx_data[1] = 2;
  }
}

void sparse_parenAssign(const emlrtStack *sp, b_sparse *this, real_T varargin_1,
                        int64_T varargin_2)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  emxArray_int32_T *rowidxt;
  emxArray_real_T *dt;
  real_T thisv;
  real_T *dt_data;
  int32_T a__1;
  int32_T numAlloc;
  int32_T nz;
  int32_T overflow;
  int32_T vidx;
  int32_T *rowidxt_data;
  boolean_T found;
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
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  st.site = &re_emlrtRSI;
  b_st.site = &se_emlrtRSI;
  c_st.site = &te_emlrtRSI;
  numAlloc = this->m;
  if ((!(muDoubleScalarFloor(varargin_1) == varargin_1)) ||
      muDoubleScalarIsInf(varargin_1)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &p_emlrtRTEI,
                                  "Coder:MATLAB:badsubscript",
                                  "Coder:MATLAB:badsubscript", 0);
  }
  if (!(varargin_1 <= numAlloc)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &o_emlrtRTEI,
                                  "Coder:builtins:IndexOutOfBounds",
                                  "Coder:builtins:IndexOutOfBounds", 6, 6,
                                  varargin_1, 12, 1, 12, numAlloc);
  }
  c_st.site = &ue_emlrtRSI;
  if (varargin_2 <= 0L) {
    emlrtErrorWithMessageIdR2018a(&c_st, &p_emlrtRTEI,
                                  "Coder:MATLAB:badsubscript",
                                  "Coder:MATLAB:badsubscript", 0);
  }
  if (varargin_2 > this->n) {
    emlrtErrorWithMessageIdR2018a(&c_st, &o_emlrtRTEI,
                                  "Coder:builtins:IndexOutOfBounds",
                                  "Coder:builtins:IndexOutOfBounds", 6, 14,
                                  varargin_2, 12, 1, 12, this->n);
  }
  c_st.site = &ve_emlrtRSI;
  sparse_locBsearch(this->rowidx, (int32_T)varargin_1,
                    this->colidx->data[(int32_T)varargin_2 - 1],
                    this->colidx->data[(int32_T)varargin_2], &vidx, &found);
  if (found) {
    thisv = this->d->data[vidx - 1];
  } else {
    thisv = 0.0;
  }
  nz = this->colidx->data[this->colidx->size[0] - 1] - 1;
  if (thisv != 0.0) {
    this->d->data[vidx - 1] = 1.0;
  } else {
    int32_T idx;
    idx = vidx + 1;
    if (this->colidx->data[this->colidx->size[0] - 1] - 1 == this->maxnz) {
      d_st.site = &ye_emlrtRSI;
      emxInit_int32_T(&d_st, &rowidxt, &xc_emlrtRTEI, true);
      a__1 = rowidxt->size[0];
      rowidxt->size[0] = this->rowidx->size[0];
      emxEnsureCapacity_int32_T(&d_st, rowidxt, a__1, &xc_emlrtRTEI);
      rowidxt_data = rowidxt->data;
      numAlloc = this->rowidx->size[0];
      for (a__1 = 0; a__1 < numAlloc; a__1++) {
        rowidxt_data[a__1] = this->rowidx->data[a__1];
      }
      emxInit_real_T(&d_st, &dt, 1, &yc_emlrtRTEI, true);
      a__1 = dt->size[0];
      dt->size[0] = this->d->size[0];
      emxEnsureCapacity_real_T(&d_st, dt, a__1, &yc_emlrtRTEI);
      dt_data = dt->data;
      numAlloc = this->d->size[0];
      for (a__1 = 0; a__1 < numAlloc; a__1++) {
        dt_data[a__1] = this->d->data[a__1];
      }
      bigProduct(this->m, this->n, &numAlloc, &overflow);
      if (overflow == 0) {
        e_st.site = &af_emlrtRSI;
        bigProduct(this->m, this->n, &a__1, &overflow);
        if (overflow != 0) {
          emlrtErrorWithMessageIdR2018a(&e_st, &cb_emlrtRTEI,
                                        "Coder:toolbox:SparseNumelTooBig",
                                        "Coder:toolbox:SparseNumelTooBig", 0);
        }
        numAlloc = this->m * this->n;
        a__1 = this->colidx->data[this->colidx->size[0] - 1] + 9;
        numAlloc = muIntScalarMin_sint32(a__1, numAlloc);
        if (numAlloc <= 1) {
          numAlloc = 1;
        }
      } else if (this->colidx->data[this->colidx->size[0] - 1] + 9 <= 1) {
        numAlloc = 1;
      } else {
        numAlloc = this->colidx->data[this->colidx->size[0] - 1] + 9;
      }
      a__1 = this->rowidx->size[0];
      this->rowidx->size[0] = numAlloc;
      emxEnsureCapacity_int32_T(&d_st, this->rowidx, a__1, &ad_emlrtRTEI);
      for (a__1 = 0; a__1 < numAlloc; a__1++) {
        this->rowidx->data[a__1] = 0;
      }
      a__1 = this->d->size[0];
      this->d->size[0] = numAlloc;
      emxEnsureCapacity_real_T(&d_st, this->d, a__1, &ad_emlrtRTEI);
      for (a__1 = 0; a__1 < numAlloc; a__1++) {
        this->d->data[a__1] = 0.0;
      }
      this->maxnz = numAlloc;
      e_st.site = &bf_emlrtRSI;
      if (vidx > 2147483646) {
        f_st.site = &yb_emlrtRSI;
        b_check_forloop_overflow_error(&f_st);
      }
      for (overflow = 0; overflow < vidx; overflow++) {
        this->rowidx->data[overflow] = rowidxt_data[overflow];
        this->d->data[overflow] = dt_data[overflow];
      }
      e_st.site = &cf_emlrtRSI;
      if ((vidx + 1 <= this->colidx->data[this->colidx->size[0] - 1] - 1) &&
          (this->colidx->data[this->colidx->size[0] - 1] - 1 > 2147483646)) {
        f_st.site = &yb_emlrtRSI;
        b_check_forloop_overflow_error(&f_st);
      }
      for (overflow = idx; overflow <= nz; overflow++) {
        this->rowidx->data[overflow] = rowidxt_data[overflow - 1];
        this->d->data[overflow] = dt_data[overflow - 1];
      }
      emxFree_real_T(&d_st, &dt);
      emxFree_int32_T(&d_st, &rowidxt);
      this->rowidx->data[vidx] = (int32_T)varargin_1;
      this->d->data[vidx] = 1.0;
    } else {
      d_st.site = &xe_emlrtRSI;
      numAlloc = (this->colidx->data[this->colidx->size[0] - 1] - vidx) - 1;
      if (numAlloc > 0) {
        e_st.site = &df_emlrtRSI;
        memmove((void *)&this->rowidx->data[vidx + 1],
                (void *)&this->rowidx->data[vidx],
                (uint32_T)((size_t)numAlloc * sizeof(int32_T)));
        e_st.site = &ef_emlrtRSI;
        memmove((void *)&this->d->data[vidx + 1], (void *)&this->d->data[vidx],
                (uint32_T)((size_t)numAlloc * sizeof(real_T)));
      }
      this->d->data[vidx] = 1.0;
      this->rowidx->data[vidx] = (int32_T)varargin_1;
    }
    d_st.site = &we_emlrtRSI;
    numAlloc = (int32_T)varargin_2 + 1;
    a__1 = this->n + 1;
    e_st.site = &ff_emlrtRSI;
    if (((int32_T)varargin_2 + 1 <= a__1) && (a__1 > 2147483646)) {
      f_st.site = &yb_emlrtRSI;
      b_check_forloop_overflow_error(&f_st);
    }
    for (overflow = numAlloc; overflow <= a__1; overflow++) {
      this->colidx->data[overflow - 1]++;
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

void sparse_parenReference(const emlrtStack *sp, const emxArray_real_T *this_d,
                           const emxArray_int32_T *this_colidx,
                           const emxArray_int32_T *this_rowidx, int32_T this_m,
                           int32_T this_n, real_T varargin_1,
                           int64_T varargin_2, emxArray_real_T *s_d,
                           emxArray_int32_T *s_colidx,
                           emxArray_int32_T *s_rowidx)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  const real_T *this_d_data;
  real_T *s_d_data;
  const int32_T *this_colidx_data;
  int32_T i;
  int32_T idx;
  int32_T *s_colidx_data;
  int32_T *s_rowidx_data;
  boolean_T found;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  st.site = &ie_emlrtRSI;
  b_st.site = &je_emlrtRSI;
  c_st.site = &ke_emlrtRSI;
  if ((!(muDoubleScalarFloor(varargin_1) == varargin_1)) ||
      muDoubleScalarIsInf(varargin_1)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &p_emlrtRTEI,
                                  "Coder:MATLAB:badsubscript",
                                  "Coder:MATLAB:badsubscript", 0);
  }
  if (!(varargin_1 <= this_m)) {
    emlrtErrorWithMessageIdR2018a(
        &c_st, &o_emlrtRTEI, "Coder:builtins:IndexOutOfBounds",
        "Coder:builtins:IndexOutOfBounds", 6, 6, varargin_1, 12, 1, 12, this_m);
  }
  c_st.site = &le_emlrtRSI;
  if (varargin_2 <= 0L) {
    emlrtErrorWithMessageIdR2018a(&c_st, &p_emlrtRTEI,
                                  "Coder:MATLAB:badsubscript",
                                  "Coder:MATLAB:badsubscript", 0);
  }
  if (varargin_2 > this_n) {
    emlrtErrorWithMessageIdR2018a(&c_st, &o_emlrtRTEI,
                                  "Coder:builtins:IndexOutOfBounds",
                                  "Coder:builtins:IndexOutOfBounds", 6, 14,
                                  varargin_2, 12, 1, 12, this_n);
  }
  c_st.site = &me_emlrtRSI;
  s_d->size[0] = 0;
  s_rowidx->size[0] = 0;
  i = s_colidx->size[0];
  s_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(&c_st, s_colidx, i, &ic_emlrtRTEI);
  s_colidx_data = s_colidx->data;
  s_colidx_data[0] = 1;
  s_colidx_data[1] = 1;
  sparse_locBsearch(this_rowidx, (int32_T)varargin_1,
                    this_colidx_data[(int32_T)varargin_2 - 1],
                    this_colidx_data[(int32_T)varargin_2], &idx, &found);
  if (found) {
    i = s_d->size[0];
    s_d->size[0] = 1;
    emxEnsureCapacity_real_T(&c_st, s_d, i, &ic_emlrtRTEI);
    s_d_data = s_d->data;
    i = s_rowidx->size[0];
    s_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(&c_st, s_rowidx, i, &ic_emlrtRTEI);
    s_rowidx_data = s_rowidx->data;
    s_d_data[0] = this_d_data[idx - 1];
    s_rowidx_data[0] = 1;
    s_colidx_data[1] = 2;
  }
  if (s_colidx_data[1] - 1 == 0) {
    i = s_rowidx->size[0];
    s_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(&c_st, s_rowidx, i, &ic_emlrtRTEI);
    s_rowidx_data = s_rowidx->data;
    s_rowidx_data[0] = 1;
    i = s_d->size[0];
    s_d->size[0] = 1;
    emxEnsureCapacity_real_T(&c_st, s_d, i, &ic_emlrtRTEI);
    s_d_data = s_d->data;
    s_d_data[0] = 0.0;
  }
}

/* End of code generation (sparse.c) */
