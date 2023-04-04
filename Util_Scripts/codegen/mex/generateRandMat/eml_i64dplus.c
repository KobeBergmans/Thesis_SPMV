/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_i64dplus.c
 *
 * Code generation for function 'eml_i64dplus'
 *
 */

/* Include files */
#include "eml_i64dplus.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
int64_T plus(int64_T x, real_T y)
{
  int64_T z;
  real_T roundedy;
  roundedy = muDoubleScalarRound(y);
  if ((roundedy >= -9.2233720368547758E+18) &&
      (roundedy < 9.2233720368547758E+18)) {
    if (y - y == 0.5) {
      if ((y > 0.0) && (x < 0L) && (x <= (int64_T)-roundedy)) {
        roundedy--;
      } else if ((y < 0.0) && (x > 0L) && (-x <= (int64_T)roundedy)) {
        roundedy++;
      }
      if ((x < 0L) && ((int64_T)roundedy < MIN_int64_T - x)) {
        z = MIN_int64_T;
      } else if ((x > 0L) && ((int64_T)roundedy > MAX_int64_T - x)) {
        z = MAX_int64_T;
      } else {
        z = x + (int64_T)roundedy;
      }
    } else if ((x < 0L) && ((int64_T)roundedy < MIN_int64_T - x)) {
      z = MIN_int64_T;
    } else if ((x > 0L) && ((int64_T)roundedy > MAX_int64_T - x)) {
      z = MAX_int64_T;
    } else {
      z = x + (int64_T)roundedy;
    }
  } else if (y >= 0.0) {
    if ((y < 1.8446744073709552E+19) && (x < 0L)) {
      int64_T i;
      uint64_T tmp;
      i = -x;
      if (-x < 0L) {
        i = 0L;
      }
      if (x > MIN_int64_T) {
        tmp = (uint64_T)y - (uint64_T)i;
      } else {
        tmp = (uint64_T)y - 9223372036854775808UL;
      }
      if (tmp > 9223372036854775807UL) {
        z = MAX_int64_T;
      } else {
        z = (int64_T)tmp;
      }
    } else {
      z = MAX_int64_T;
    }
  } else if (y < 0.0) {
    if (-y < 1.8446744073709552E+19) {
      uint64_T qY;
      uint64_T tmp;
      tmp = (uint64_T)-y - (uint64_T)x;
      if (tmp > (uint64_T)-y) {
        tmp = 0UL;
      }
      qY = (uint64_T)-y + (uint64_T)-x;
      if (qY < (uint64_T)-y) {
        qY = MAX_uint64_T;
      }
      if (x < 0L) {
        tmp = qY;
      }
      if (tmp > 9223372036854775807UL) {
        z = MIN_int64_T;
      } else {
        z = -(int64_T)tmp;
      }
    } else {
      z = MIN_int64_T;
    }
  } else {
    z = 0L;
  }
  return z;
}

/* End of code generation (eml_i64dplus.c) */
