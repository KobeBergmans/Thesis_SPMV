/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertionsort.c
 *
 * Code generation for function 'insertionsort'
 *
 */

/* Include files */
#include "insertionsort.h"
#include "eml_int_forloop_overflow_check.h"
#include "generateRandMat_data.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo yf_emlrtRSI = {
    18,              /* lineNo */
    "insertionsort", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/lib/+coder/+internal/"
    "insertionsort.m" /* pathName */
};

/* Function Definitions */
void insertionsort(const emlrtStack *sp, emxArray_int32_T *x, int32_T xstart,
                   int32_T xend, const emxArray_int32_T *cmp_workspace_a,
                   const emxArray_int32_T *cmp_workspace_b)
{
  emlrtStack b_st;
  emlrtStack st;
  const int32_T *cmp_workspace_a_data;
  const int32_T *cmp_workspace_b_data;
  int32_T a;
  int32_T k;
  int32_T *x_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  cmp_workspace_b_data = cmp_workspace_b->data;
  cmp_workspace_a_data = cmp_workspace_a->data;
  x_data = x->data;
  a = xstart + 1;
  st.site = &yf_emlrtRSI;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    b_st.site = &yb_emlrtRSI;
    b_check_forloop_overflow_error(&b_st);
  }
  for (k = a; k <= xend; k++) {
    int32_T idx;
    int32_T xc;
    boolean_T exitg1;
    xc = x_data[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= xstart)) {
      boolean_T varargout_1;
      if (cmp_workspace_a_data[xc] < cmp_workspace_a_data[x_data[idx] - 1]) {
        varargout_1 = true;
      } else if (cmp_workspace_a_data[xc] ==
                 cmp_workspace_a_data[x_data[idx] - 1]) {
        varargout_1 =
            (cmp_workspace_b_data[xc] < cmp_workspace_b_data[x_data[idx] - 1]);
      } else {
        varargout_1 = false;
      }
      if (varargout_1) {
        x_data[idx + 1] = x_data[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x_data[idx + 1] = xc + 1;
  }
}

/* End of code generation (insertionsort.c) */
