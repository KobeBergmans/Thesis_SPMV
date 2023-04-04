/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "power.h"
#include "generateRandMat_mexutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
int64_T power(int64_T a)
{
  int64_T b_a;
  int64_T y;
  uint64_T bu;
  b_a = a;
  y = 1L;
  bu = 2UL;
  int32_T exitg1;
  do {
    exitg1 = 0;
    if ((bu & 1UL) != 0UL) {
      y = mul_s64_sat(b_a, y);
    }
    bu >>= 1UL;
    if (bu == 0UL) {
      exitg1 = 1;
    } else {
      b_a = mul_s64_sat(b_a, b_a);
    }
  } while (exitg1 == 0);
  return y;
}

/* End of code generation (power.c) */
