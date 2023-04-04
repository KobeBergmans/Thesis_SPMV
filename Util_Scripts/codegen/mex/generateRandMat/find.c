/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * find.c
 *
 * Code generation for function 'find'
 *
 */

/* Include files */
#include "find.h"
#include "eml_int_forloop_overflow_check.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "warning.h"

/* Variable Definitions */
static emlrtRSInfo hf_emlrtRSI = {
    138,                                                           /* lineNo */
    "eml_find",                                                    /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo if_emlrtRSI = {
    158,                                                           /* lineNo */
    "eml_find",                                                    /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo jf_emlrtRSI = {
    202,                                                           /* lineNo */
    "find_first_nonempty_triples",                                 /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo kf_emlrtRSI = {
    205,                                                           /* lineNo */
    "find_first_nonempty_triples",                                 /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo lf_emlrtRSI = {
    253,                                                           /* lineNo */
    "find_first_nonempty_triples",                                 /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo mf_emlrtRSI = {
    254,                                                           /* lineNo */
    "find_first_nonempty_triples",                                 /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRSInfo nf_emlrtRSI = {
    255,                                                           /* lineNo */
    "find_first_nonempty_triples",                                 /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRTEInfo q_emlrtRTEI = {
    239,                                                           /* lineNo */
    1,                                                             /* colNo */
    "find_first_nonempty_triples",                                 /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtDCInfo vb_emlrtDCI = {
    195,                                                            /* lineNo */
    30,                                                             /* colNo */
    "find_first_nonempty_triples",                                  /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m", /* pName */
    4 /* checkKind */
};

static emlrtRTEInfo kc_emlrtRTEI = {
    195,                                                           /* lineNo */
    24,                                                            /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo lc_emlrtRTEI = {
    197,                                                           /* lineNo */
    24,                                                            /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo mc_emlrtRTEI = {
    199,                                                           /* lineNo */
    24,                                                            /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo nc_emlrtRTEI = {
    253,                                                           /* lineNo */
    5,                                                             /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo oc_emlrtRTEI = {
    254,                                                           /* lineNo */
    5,                                                             /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo pc_emlrtRTEI = {
    255,                                                           /* lineNo */
    5,                                                             /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

/* Function Definitions */
void eml_find(const emlrtStack *sp, const emxArray_real_T *x_d,
              const emxArray_int32_T *x_colidx,
              const emxArray_int32_T *x_rowidx, int32_T x_m, int32_T x_n,
              emxArray_int32_T *i, emxArray_int32_T *j, emxArray_real_T *v)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  const real_T *x_d_data;
  real_T *v_data;
  const int32_T *x_colidx_data;
  const int32_T *x_rowidx_data;
  int32_T col;
  int32_T idx;
  int32_T nx;
  int32_T *i_data;
  int32_T *j_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  x_rowidx_data = x_rowidx->data;
  x_colidx_data = x_colidx->data;
  x_d_data = x_d->data;
  nx = x_colidx_data[x_colidx->size[0] - 1] - 2;
  if (x_colidx_data[x_colidx->size[0] - 1] - 1 == 0) {
    i->size[0] = 0;
    j->size[0] = 0;
    v->size[0] = 0;
  } else {
    int32_T b_i;
    st.site = &hf_emlrtRSI;
    col = x_colidx_data[x_colidx->size[0] - 1] - 1;
    if (col < 0) {
      emlrtNonNegativeCheckR2012b(col, &vb_emlrtDCI, &st);
    }
    b_i = i->size[0];
    i->size[0] = col;
    emxEnsureCapacity_int32_T(&st, i, b_i, &kc_emlrtRTEI);
    i_data = i->data;
    col = j->size[0];
    j->size[0] = x_colidx_data[x_colidx->size[0] - 1] - 1;
    emxEnsureCapacity_int32_T(&st, j, col, &lc_emlrtRTEI);
    j_data = j->data;
    col = v->size[0];
    v->size[0] = x_colidx_data[x_colidx->size[0] - 1] - 1;
    emxEnsureCapacity_real_T(&st, v, col, &mc_emlrtRTEI);
    v_data = v->data;
    b_st.site = &jf_emlrtRSI;
    if (x_colidx_data[x_colidx->size[0] - 1] - 1 > 2147483646) {
      c_st.site = &yb_emlrtRSI;
      b_check_forloop_overflow_error(&c_st);
    }
    for (idx = 0; idx <= nx; idx++) {
      i_data[idx] = x_rowidx_data[idx];
    }
    b_st.site = &kf_emlrtRSI;
    if (x_colidx_data[x_colidx->size[0] - 1] - 1 > 2147483646) {
      c_st.site = &yb_emlrtRSI;
      b_check_forloop_overflow_error(&c_st);
    }
    for (col = 0; col <= nx; col++) {
      v_data[col] = x_d_data[col];
    }
    idx = 0;
    col = 1;
    while (idx < nx + 1) {
      if (idx == x_colidx_data[col] - 1) {
        col++;
      } else {
        idx++;
        j_data[idx - 1] = col;
      }
    }
    if (idx > x_colidx_data[x_colidx->size[0] - 1] - 1) {
      emlrtErrorWithMessageIdR2018a(&st, &q_emlrtRTEI,
                                    "Coder:builtins:AssertionFailed",
                                    "Coder:builtins:AssertionFailed", 0);
    }
    if (x_colidx_data[x_colidx->size[0] - 1] - 1 == 1) {
      if (idx == 0) {
        i->size[0] = 0;
        j->size[0] = 0;
        v->size[0] = 0;
      }
    } else {
      int32_T iv[2];
      if (idx < 1) {
        col = 0;
      } else {
        col = idx;
      }
      iv[0] = 1;
      iv[1] = col;
      b_st.site = &lf_emlrtRSI;
      indexShapeCheck(&b_st, i->size[0], iv);
      b_i = i->size[0];
      i->size[0] = col;
      emxEnsureCapacity_int32_T(&st, i, b_i, &nc_emlrtRTEI);
      if (idx < 1) {
        col = 0;
      } else {
        col = idx;
      }
      iv[0] = 1;
      iv[1] = col;
      b_st.site = &mf_emlrtRSI;
      indexShapeCheck(&b_st, j->size[0], iv);
      b_i = j->size[0];
      j->size[0] = col;
      emxEnsureCapacity_int32_T(&st, j, b_i, &oc_emlrtRTEI);
      if (idx < 1) {
        col = 0;
      } else {
        col = idx;
      }
      iv[0] = 1;
      iv[1] = col;
      b_st.site = &nf_emlrtRSI;
      indexShapeCheck(&b_st, v->size[0], iv);
      b_i = v->size[0];
      v->size[0] = col;
      emxEnsureCapacity_real_T(&st, v, b_i, &pc_emlrtRTEI);
    }
  }
  if ((x_m == 1) && (i->size[0] != 1) && (x_n >= 2)) {
    st.site = &if_emlrtRSI;
    warning(&st);
  }
}

/* End of code generation (find.c) */
