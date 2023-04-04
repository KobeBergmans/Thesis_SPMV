/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat_mexutil.c
 *
 * Code generation for function 'generateRandMat_mexutil'
 *
 */

/* Include files */
#include "generateRandMat_mexutil.h"
#include "generateRandMat_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                          const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                          const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

real_T emlrt_marshallIn(const emlrtStack *sp,
                        const mxArray *a__output_of_feval_,
                        const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  emlrtAssertMATLABThread((emlrtCTX)sp, &b_emlrtRTEI);
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(a__output_of_feval_), &thisId);
  emlrtDestroyArray(&a__output_of_feval_);
  return y;
}

int64_T mul_s64_sat(int64_T a, int64_T b)
{
  int64_T result;
  uint64_T u64_chi;
  uint64_T u64_clo;
  mul_wide_s64(a, b, &u64_chi, &u64_clo);
  if (((int64_T)u64_chi > 0L) ||
      ((u64_chi == 0UL) && (u64_clo >= 9223372036854775808UL))) {
    result = MAX_int64_T;
  } else if (((int64_T)u64_chi < -1L) ||
             (((int64_T)u64_chi == -1L) && (u64_clo < 9223372036854775808UL))) {
    result = MIN_int64_T;
  } else {
    result = (int64_T)u64_clo;
  }
  return result;
}

void mul_wide_s64(int64_T in0, int64_T in1, uint64_T *ptrOutBitsHi,
                  uint64_T *ptrOutBitsLo)
{
  uint64_T absIn0;
  uint64_T absIn1;
  uint64_T in0Hi;
  uint64_T in0Lo;
  uint64_T in1Hi;
  uint64_T productHiLo;
  uint64_T productLoHi;
  if (in0 < 0L) {
    absIn0 = ~(uint64_T)in0 + 1UL;
  } else {
    absIn0 = (uint64_T)in0;
  }
  if (in1 < 0L) {
    absIn1 = ~(uint64_T)in1 + 1UL;
  } else {
    absIn1 = (uint64_T)in1;
  }
  in0Hi = absIn0 >> 32UL;
  in0Lo = absIn0 & 4294967295UL;
  in1Hi = absIn1 >> 32UL;
  absIn0 = absIn1 & 4294967295UL;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0UL;
  in0Lo = absIn0 + (productLoHi << 32UL);
  if (in0Lo < absIn0) {
    absIn1 = 1UL;
  }
  absIn0 = in0Lo;
  in0Lo += productHiLo << 32UL;
  if (in0Lo < absIn0) {
    absIn1++;
  }
  absIn0 = ((absIn1 + in0Hi * in1Hi) + (productLoHi >> 32UL)) +
           (productHiLo >> 32UL);
  if ((in0 != 0L) && ((in1 != 0L) && ((in0 > 0L) != (in1 > 0L)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0UL) {
      absIn0++;
    }
  }
  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

/* End of code generation (generateRandMat_mexutil.c) */
