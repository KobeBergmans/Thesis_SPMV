/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_i64dmul.c
 *
 * Code generation for function 'eml_i64dmul'
 *
 */

/* Include files */
#include "eml_i64dmul.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <math.h>

/* Variable Definitions */
static emlrtRSInfo rd_emlrtRSI = {
    28,      /* lineNo */
    "times", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m" /* pathName
                                                                         */
};

static emlrtRSInfo sd_emlrtRSI = {
    68,                    /* lineNo */
    "eml_mixed_int64_mul", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m" /* pathName
                                                                         */
};

static emlrtRSInfo td_emlrtRSI = {
    195,                    /* lineNo */
    "eml_mixed_uint64_mul", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m" /* pathName
                                                                         */
};

static emlrtRSInfo ud_emlrtRSI = {
    194,                    /* lineNo */
    "eml_mixed_uint64_mul", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m" /* pathName
                                                                         */
};

static emlrtRSInfo vd_emlrtRSI = {
    191,                    /* lineNo */
    "eml_mixed_uint64_mul", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m" /* pathName
                                                                         */
};

static emlrtBCInfo nb_emlrtBCI = {
    0,         /* iFirst */
    63,        /* iLast */
    230,       /* lineNo */
    20,        /* colNo */
    "",        /* aName */
    "ishiftr", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/eml_i64dmul.m", /* pName
                                                                          */
    1 /* checkKind */
};

/* Function Definitions */
int64_T times(const emlrtStack *sp, int64_T x, real_T y)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int64_T z;
  uint64_T prod_unsgn;
  uint64_T temp;
  int32_T ex_t;
  boolean_T isProdNegative;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &rd_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  if ((x < 0L) && (y > 0.0)) {
    isProdNegative = true;
  } else {
    isProdNegative = false;
  }
  if (x < 0L) {
    if (x > MIN_int64_T) {
      temp = (uint64_T)-x;
    } else {
      temp = 9223372036854775808UL;
    }
  } else {
    temp = (uint64_T)x;
  }
  b_st.site = &sd_emlrtRSI;
  if (muDoubleScalarIsNaN(y) || (y <= 0.0)) {
    prod_unsgn = 0UL;
  } else {
    real_T yd;
    uint64_T b_y0;
    uint64_T b_y1;
    yd = frexp(y, &ex_t);
    prod_unsgn = (uint64_T)muDoubleScalarRound(yd * 9.007199254740992E+15);
    b_y1 = prod_unsgn >> 32;
    b_y0 = prod_unsgn & 4294967295UL;
    if (temp == 0UL) {
      prod_unsgn = 0UL;
    } else {
      uint64_T ldword;
      uint64_T n1;
      uint64_T temp0;
      int16_T i;
      n1 = temp >> 32;
      prod_unsgn = temp & 4294967295UL;
      ldword = prod_unsgn * b_y0;
      temp0 = prod_unsgn * b_y1;
      prod_unsgn = n1 * b_y0;
      temp = ((temp0 & 4294967295UL) + (ldword >> 32)) +
             (prod_unsgn & 4294967295UL);
      ldword = (ldword & 4294967295UL) + (temp << 32);
      prod_unsgn =
          ((n1 * b_y1 + (temp0 >> 32)) + (prod_unsgn >> 32)) + (temp >> 32);
      c_st.site = &vd_emlrtRSI;
      i = (int16_T)(53 - ex_t);
      if (53 - ex_t < 0) {
        i = 0;
      } else if (53 - ex_t > 255) {
        i = 255;
      }
      if (i > 63) {
        emlrtDynamicBoundsCheckR2012b(i, 0, 63, &nb_emlrtBCI, &c_st);
      }
      if ((prod_unsgn >> (uint8_T)i) > 0UL) {
        prod_unsgn = MAX_uint64_T;
      } else {
        int16_T i1;
        int16_T i2;
        c_st.site = &ud_emlrtRSI;
        i = (int16_T)(52 - ex_t);
        if (52 - ex_t < 0) {
          i = 0;
        } else if (52 - ex_t > 255) {
          i = 255;
        }
        if (i > 63) {
          emlrtDynamicBoundsCheckR2012b(i, 0, 63, &nb_emlrtBCI, &c_st);
        }
        c_st.site = &td_emlrtRSI;
        i1 = (int16_T)(53 - ex_t);
        if (53 - ex_t < 0) {
          i1 = 0;
        } else if (53 - ex_t > 255) {
          i1 = 255;
        }
        if (i1 > 63) {
          emlrtDynamicBoundsCheckR2012b(i1, 0, 63, &nb_emlrtBCI, &c_st);
        }
        i2 = (int16_T)(ex_t + 11);
        if (ex_t + 11 < 0) {
          i2 = 0;
        } else if (ex_t + 11 > 255) {
          i2 = 255;
        }
        prod_unsgn = ((ldword >> (uint8_T)i1) + (prod_unsgn << (uint8_T)i2)) +
                     (ldword >> (uint8_T)i & 1UL);
      }
    }
  }
  if (isProdNegative) {
    if (prod_unsgn <= 9223372036854775807UL) {
      z = -(int64_T)prod_unsgn;
    } else {
      z = MIN_int64_T;
    }
  } else if (prod_unsgn <= 9223372036854775807UL) {
    z = (int64_T)prod_unsgn;
  } else {
    z = MAX_int64_T;
  }
  return z;
}

/* End of code generation (eml_i64dmul.c) */
