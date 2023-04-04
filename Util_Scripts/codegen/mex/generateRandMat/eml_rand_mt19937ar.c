/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_rand_mt19937ar.c
 *
 * Code generation for function 'eml_rand_mt19937ar'
 *
 */

/* Include files */
#include "eml_rand_mt19937ar.h"
#include "generateRandMat.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRTEInfo bb_emlrtRTEI = {
    158,        /* lineNo */
    17,         /* colNo */
    "genrandu", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/"
    "eml_rand_mt19937ar.m" /* pName */
};

/* Function Definitions */
void eml_rand_mt19937ar(const emlrtStack *sp, uint32_T b_state[625])
{
  int32_T mti;
  if (emlrtIsInParallelRegion((emlrtCTX)sp)) {
    uint32_T r;
    mti = getThreadID();
    if (mti > 2147483646) {
      mti = MAX_int32_T;
    } else {
      mti++;
    }
    if (mti < 0) {
      mti = 0;
    }
    r = (uint32_T)mti;
    b_state[0] = (uint32_T)mti;
    for (mti = 0; mti < 623; mti++) {
      r = ((r ^ r >> 30U) * 1812433253U + (uint32_T)mti) + 1U;
      b_state[mti + 1] = r;
    }
    b_state[624] = 624U;
  } else {
    uint32_T r;
    r = 5489U;
    b_state[0] = 5489U;
    for (mti = 0; mti < 623; mti++) {
      r = ((r ^ r >> 30U) * 1812433253U + (uint32_T)mti) + 1U;
      b_state[mti + 1] = r;
    }
    b_state[624] = 624U;
  }
}

void genrand_uint32_vector(uint32_T mt[625], uint32_T u[2])
{
  int32_T j;
  int32_T kk;
  for (j = 0; j < 2; j++) {
    uint32_T mti;
    uint32_T y;
    mti = mt[624] + 1U;
    if (mti >= 625U) {
      for (kk = 0; kk < 227; kk++) {
        y = (mt[kk] & 2147483648U) | (mt[kk + 1] & 2147483647U);
        if ((y & 1U) == 0U) {
          y >>= 1U;
        } else {
          y = y >> 1U ^ 2567483615U;
        }
        mt[kk] = mt[kk + 397] ^ y;
      }
      for (kk = 0; kk < 396; kk++) {
        y = (mt[kk + 227] & 2147483648U) | (mt[kk + 228] & 2147483647U);
        if ((y & 1U) == 0U) {
          y >>= 1U;
        } else {
          y = y >> 1U ^ 2567483615U;
        }
        mt[kk + 227] = mt[kk] ^ y;
      }
      y = (mt[623] & 2147483648U) | (mt[0] & 2147483647U);
      if ((y & 1U) == 0U) {
        y >>= 1U;
      } else {
        y = y >> 1U ^ 2567483615U;
      }
      mt[623] = mt[396] ^ y;
      mti = 1U;
    }
    y = mt[(int32_T)mti - 1];
    mt[624] = mti;
    y ^= y >> 11U;
    y ^= y << 7U & 2636928640U;
    y ^= y << 15U & 4022730752U;
    u[j] = y ^ y >> 18U;
  }
}

real_T genrandu(const emlrtStack *sp, uint32_T mt[625])
{
  real_T r;
  /* ========================= COPYRIGHT NOTICE ============================ */
  /*  This is a uniform (0,1) pseudorandom number generator based on:        */
  /*                                                                         */
  /*  A C-program for MT19937, with initialization improved 2002/1/26.       */
  /*  Coded by Takuji Nishimura and Makoto Matsumoto.                        */
  /*                                                                         */
  /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      */
  /*  All rights reserved.                                                   */
  /*                                                                         */
  /*  Redistribution and use in source and binary forms, with or without     */
  /*  modification, are permitted provided that the following conditions     */
  /*  are met:                                                               */
  /*                                                                         */
  /*    1. Redistributions of source code must retain the above copyright    */
  /*       notice, this list of conditions and the following disclaimer.     */
  /*                                                                         */
  /*    2. Redistributions in binary form must reproduce the above copyright */
  /*       notice, this list of conditions and the following disclaimer      */
  /*       in the documentation and/or other materials provided with the     */
  /*       distribution.                                                     */
  /*                                                                         */
  /*    3. The names of its contributors may not be used to endorse or       */
  /*       promote products derived from this software without specific      */
  /*       prior written permission.                                         */
  /*                                                                         */
  /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
  /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
  /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
  /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  */
  /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
  /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
  /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
  /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
  /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
  /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
  /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
  /*                                                                         */
  /* =============================   END   ================================= */
  int32_T exitg1;
  uint32_T u[2];
  do {
    exitg1 = 0;
    genrand_uint32_vector(mt, u);
    u[0] >>= 5U;
    u[1] >>= 6U;
    r = 1.1102230246251565E-16 * ((real_T)u[0] * 6.7108864E+7 + (real_T)u[1]);
    if (r == 0.0) {
      boolean_T isvalid;
      if ((mt[624] >= 1U) && (mt[624] < 625U)) {
        isvalid = true;
      } else {
        isvalid = false;
      }
      if (isvalid) {
        int32_T k;
        boolean_T exitg2;
        isvalid = false;
        k = 1;
        exitg2 = false;
        while ((!exitg2) && (k < 625)) {
          if (mt[k - 1] == 0U) {
            k++;
          } else {
            isvalid = true;
            exitg2 = true;
          }
        }
      }
      if (!isvalid) {
        emlrtErrorWithMessageIdR2018a(
            sp, &bb_emlrtRTEI, "Coder:MATLAB:rand_invalidTwisterState",
            "Coder:MATLAB:rand_invalidTwisterState", 0);
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return r;
}

/* End of code generation (eml_rand_mt19937ar.c) */
