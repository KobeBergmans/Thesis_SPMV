/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eml_rand.c
 *
 * Code generation for function 'eml_rand'
 *
 */

/* Include files */
#include "eml_rand.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "generateRandMat_types.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Variable Definitions */
static uint32_T method;
#pragma omp threadprivate(method)

static boolean_T method_not_empty = false;
#pragma omp threadprivate(method_not_empty)

static uint32_T method_main;

static boolean_T method_not_empty_main = false;

static emlrtRSInfo qb_emlrtRSI =
    {
        45,         /* lineNo */
        "eml_rand", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/private/"
        "eml_rand.m" /* pathName */
};

/* Function Definitions */
real_T b_eml_rand(const emlrtStack *sp)
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &qb_emlrtRSI;
  return b_eml_rand_mt19937ar_stateful(&st);
}

void eml_rand(const emlrtStack *sp, int64_T varargin_1, emxArray_real_T *r)
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &qb_emlrtRSI;
  eml_rand_mt19937ar_stateful(&st, varargin_1, r);
}

void eml_rand_free(const emlrtStack *sp)
{
  jmp_buf *volatile emlrtJBStack;
  int32_T eml_rand_free_numThreads;
  int32_T i;
  int32_T ub_loop;
  ub_loop = omp_get_max_threads();
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  eml_rand_free_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel for schedule(static) num_threads(eml_rand_free_numThreads)

  for (i = 1; i <= ub_loop; i++) {
    method_not_empty = false;
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
  method_not_empty_main = false;
}

void eml_rand_init(const emlrtStack *sp)
{
  jmp_buf *volatile emlrtJBStack;
  int32_T eml_rand_init_numThreads;
  int32_T i;
  int32_T ub_loop;
  ub_loop = omp_get_max_threads();
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  eml_rand_init_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel for schedule(static) num_threads(eml_rand_init_numThreads)

  for (i = 1; i <= ub_loop; i++) {
    method = 7U;
    method_not_empty = true;
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
  method_main = method;
  method = 7U;
  method_not_empty = true;
}

void eml_rand_swap(void)
{
  uint32_T method_tmp;
  boolean_T method_not_empty_tmp;
  method_tmp = method;
  method = method_main;
  method_main = method_tmp;
  method_not_empty_tmp = method_not_empty;
  method_not_empty = method_not_empty_main;
  method_not_empty_main = method_not_empty_tmp;
}

/* End of code generation (eml_rand.c) */
