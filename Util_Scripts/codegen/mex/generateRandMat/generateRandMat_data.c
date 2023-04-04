/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat_data.c
 *
 * Code generation for function 'generateRandMat_data'
 *
 */

/* Include files */
#include "generateRandMat_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131627U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "generateRandMat",                                    /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

emlrtRSInfo yb_emlrtRSI = {
    20,                               /* lineNo */
    "eml_int_forloop_overflow_check", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/eml/"
    "eml_int_forloop_overflow_check.m" /* pathName */
};

emlrtRSInfo ac_emlrtRSI = {
    15,    /* lineNo */
    "max", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/max.m" /* pathName
                                                                     */
};

emlrtRSInfo bd_emlrtRSI = {
    219,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

emlrtRSInfo cd_emlrtRSI = {
    197,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

emlrtRSInfo ed_emlrtRSI = {
    143,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

emlrtRSInfo fd_emlrtRSI = {
    142,             /* lineNo */
    "sparse/sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pathName */
};

emlrtRSInfo pe_emlrtRSI = {
    13,       /* lineNo */
    "sparse", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/sparfun/sparse.m" /* pathName
                                                                        */
};

emlrtRTEInfo b_emlrtRTEI = {
    1,                 /* lineNo */
    14,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

omp_lock_t emlrtLockGlobal;

omp_nest_lock_t generateRandMat_nestLockGlobal;

emlrtDCInfo ub_emlrtDCI = {
    193,             /* lineNo */
    48,              /* colNo */
    "sparse/sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m", /* pName */
    4                   /* checkKind */
};

emlrtRTEInfo hc_emlrtRTEI = {
    193,      /* lineNo */
    42,       /* colNo */
    "sparse", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/shared/coder/coder/+coder/+internal/"
    "@sparse/sparse.m" /* pName */
};

/* End of code generation (generateRandMat_data.c) */
