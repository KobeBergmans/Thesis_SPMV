/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ixfun.c
 *
 * Code generation for function 'ixfun'
 *
 */

/* Include files */
#include "ixfun.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRTEInfo f_emlrtRTEI = {
    225,          /* lineNo */
    23,           /* colNo */
    "expand_max", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/ixfun.m" /* pName
                                                                         */
};

static emlrtRTEInfo fc_emlrtRTEI = {
    234,     /* lineNo */
    20,      /* colNo */
    "ixfun", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/ixfun.m" /* pName
                                                                         */
};

/* Function Definitions */
void expand_max(const emlrtStack *sp, const emxArray_real_T *a,
                const emxArray_real_T *b, emxArray_real_T *c)
{
  const real_T *b_data;
  real_T *c_data;
  int32_T sak;
  int32_T sbk;
  b_data = b->data;
  sak = a->size[0];
  sbk = b->size[0];
  if (b->size[0] == 1) {
    sak = a->size[0];
  } else if (a->size[0] == 1) {
    sak = b->size[0];
  } else {
    sak = muIntScalarMin_sint32(sak, sbk);
    if (a->size[0] != b->size[0]) {
      emlrtErrorWithMessageIdR2018a(sp, &f_emlrtRTEI,
                                    "MATLAB:sizeDimensionsMustMatch",
                                    "MATLAB:sizeDimensionsMustMatch", 0);
    }
  }
  sbk = c->size[0];
  c->size[0] = sak;
  emxEnsureCapacity_real_T(sp, c, sbk, &fc_emlrtRTEI);
  c_data = c->data;
  if (sak != 0) {
    boolean_T b_b;
    b_b = (b->size[0] != 1);
    sbk = sak - 1;
    for (sak = 0; sak <= sbk; sak++) {
      c_data[sak] = muDoubleScalarMax(1.0, b_data[b_b * sak]);
    }
  }
}

/* End of code generation (ixfun.c) */
