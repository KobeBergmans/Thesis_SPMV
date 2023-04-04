/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * generateRandMat.c
 *
 * Code generation for function 'generateRandMat'
 *
 */

/* Include files */
#include "generateRandMat.h"
#include "eml_i64dmul.h"
#include "eml_i64dplus.h"
#include "eml_int_forloop_overflow_check.h"
#include "eml_rand.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "find.h"
#include "generateRandMat_data.h"
#include "generateRandMat_emxutil.h"
#include "generateRandMat_mexutil.h"
#include "generateRandMat_types.h"
#include "indexShapeCheck.h"
#include "ixfun.h"
#include "log2.h"
#include "power.h"
#include "rand.h"
#include "randn.h"
#include "round.h"
#include "rt_nonfinite.h"
#include "spalloc.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "mwmathutil.h"
#include "omp.h"
#include <stdio.h>

/* Variable Definitions */
static int32_T threadID;
#pragma omp threadprivate(threadID)

static emlrtRSInfo emlrtRSI = {
    9,                 /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo b_emlrtRSI = {
    11,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo c_emlrtRSI = {
    12,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo d_emlrtRSI = {
    19,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo e_emlrtRSI = {
    20,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo f_emlrtRSI = {
    23,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo g_emlrtRSI = {
    26,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo h_emlrtRSI = {
    29,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo i_emlrtRSI = {
    32,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo j_emlrtRSI = {
    33,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo k_emlrtRSI = {
    36,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo l_emlrtRSI = {
    41,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo m_emlrtRSI = {
    42,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo n_emlrtRSI = {
    46,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo o_emlrtRSI = {
    47,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo p_emlrtRSI = {
    48,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo q_emlrtRSI = {
    66,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo r_emlrtRSI = {
    68,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo s_emlrtRSI = {
    71,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo t_emlrtRSI = {
    73,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo u_emlrtRSI = {
    78,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo v_emlrtRSI = {
    79,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo w_emlrtRSI = {
    83,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo x_emlrtRSI = {
    85,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo y_emlrtRSI = {
    88,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo ab_emlrtRSI = {
    90,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo bb_emlrtRSI = {
    92,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo cb_emlrtRSI = {
    95,                /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo db_emlrtRSI = {
    107,               /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo eb_emlrtRSI = {
    108,               /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo fb_emlrtRSI = {
    109,               /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo gb_emlrtRSI = {
    115,               /* lineNo */
    "generateRandMat", /* fcnName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pathName */
};

static emlrtRSInfo hb_emlrtRSI = {
    71,                                                           /* lineNo */
    "power",                                                      /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/ops/power.m" /* pathName */
};

static emlrtRSInfo ib_emlrtRSI =
    {
        34,               /* lineNo */
        "rdivide_helper", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "rdivide_helper.m" /* pathName */
};

static emlrtRSInfo jb_emlrtRSI = {
    27,    /* lineNo */
    "div", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/div.m" /* pathName
                                                                       */
};

static emlrtRSInfo kb_emlrtRSI = {
    151,               /* lineNo */
    "integerDivision", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/div.m" /* pathName
                                                                       */
};

static emlrtRSInfo lb_emlrtRSI = {
    47,      /* lineNo */
    "ixfun", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/ixfun.m" /* pathName
                                                                         */
};

static emlrtRSInfo mb_emlrtRSI = {
    192,                     /* lineNo */
    "scalarIntegerDivision", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/div.m" /* pathName
                                                                       */
};

static emlrtRSInfo bc_emlrtRSI = {
    29,         /* lineNo */
    "minOrMax", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo cc_emlrtRSI = {
    58,         /* lineNo */
    "maximum2", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo dc_emlrtRSI =
    {
        63,               /* lineNo */
        "binaryMinOrMax", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "binaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo ec_emlrtRSI = {
    57,      /* lineNo */
    "ixfun", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/ixfun.m" /* pathName
                                                                         */
};

static emlrtRSInfo fc_emlrtRSI = {
    102,                          /* lineNo */
    "binaryImplicitExpansionFun", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/ixfun.m" /* pathName
                                                                         */
};

static emlrtRSInfo vc_emlrtRSI = {
    38,        /* lineNo */
    "fprintf", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pathName
                                                                       */
};

static emlrtRSInfo wc_emlrtRSI = {
    72,        /* lineNo */
    "fprintf", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pathName
                                                                       */
};

static emlrtRSInfo id_emlrtRSI = {
    17,    /* lineNo */
    "max", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/datafun/max.m" /* pathName
                                                                     */
};

static emlrtRSInfo jd_emlrtRSI = {
    38,         /* lineNo */
    "minOrMax", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo kd_emlrtRSI = {
    77,        /* lineNo */
    "maximum", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/minOrMax.m" /* pathName
                                                                            */
};

static emlrtRSInfo ld_emlrtRSI =
    {
        173,             /* lineNo */
        "unaryMinOrMax", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pathName */
};

static emlrtRSInfo md_emlrtRSI = {
    72,                      /* lineNo */
    "vectorMinOrMaxInPlace", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "vectorMinOrMaxInPlace.m" /* pathName */
};

static emlrtRSInfo nd_emlrtRSI = {
    64,                      /* lineNo */
    "vectorMinOrMaxInPlace", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "vectorMinOrMaxInPlace.m" /* pathName */
};

static emlrtRSInfo od_emlrtRSI = {
    113,         /* lineNo */
    "findFirst", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "vectorMinOrMaxInPlace.m" /* pathName */
};

static emlrtRSInfo pd_emlrtRSI = {
    130,                        /* lineNo */
    "minOrMaxRealVectorKernel", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
    "vectorMinOrMaxInPlace.m" /* pathName */
};

static emlrtRSInfo qd_emlrtRSI =
    {
        76,                  /* lineNo */
        "eml_mtimes_helper", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/ops/"
        "eml_mtimes_helper.m" /* pathName */
};

static emlrtRSInfo de_emlrtRSI = {
    81,      /* lineNo */
    "randi", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/randfun/randi.m" /* pathName
                                                                       */
};

static emlrtRSInfo gf_emlrtRSI = {
    31,                                                            /* lineNo */
    "find",                                                        /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pathName
                                                                    */
};

static emlrtRTEInfo emlrtRTEI = {
    66,        /* lineNo */
    24,        /* colNo */
    "fprintf", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pName
                                                                       */
};

static emlrtMCInfo emlrtMCI = {
    66,        /* lineNo */
    18,        /* colNo */
    "fprintf", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pName
                                                                       */
};

static emlrtRTEInfo c_emlrtRTEI =
    {
        134,             /* lineNo */
        27,              /* colNo */
        "unaryMinOrMax", /* fName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/"
        "unaryMinOrMax.m" /* pName */
};

static emlrtBCInfo emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    101,               /* lineNo */
    129,               /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    101,               /* lineNo */
    53,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    98,                /* lineNo */
    109,               /* colNo */
    "block_row_cts",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    98,                /* lineNo */
    47,                /* colNo */
    "block_row_cts",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo e_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    109,               /* lineNo */
    57,                /* colNo */
    "A_parts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo f_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    107,               /* lineNo */
    41,                /* colNo */
    "A_parts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo g_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    22,                /* lineNo */
    33,                /* colNo */
    "A_parts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo h_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    38,                /* lineNo */
    15,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo i_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    38,                /* lineNo */
    45,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo j_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    37,                /* lineNo */
    15,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo k_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    37,                /* lineNo */
    51,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo emlrtDCI = {
    109,               /* lineNo */
    57,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo b_emlrtDCI = {
    101,               /* lineNo */
    129,               /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo c_emlrtDCI = {
    101,               /* lineNo */
    53,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo d_emlrtDCI = {
    98,                /* lineNo */
    109,               /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo e_emlrtDCI = {
    98,                /* lineNo */
    47,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo f_emlrtDCI = {
    46,                /* lineNo */
    22,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo g_emlrtDCI = {
    42,                /* lineNo */
    29,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo h_emlrtDCI = {
    42,                /* lineNo */
    29,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo i_emlrtDCI = {
    38,                /* lineNo */
    15,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo j_emlrtDCI = {
    38,                /* lineNo */
    45,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo k_emlrtDCI = {
    37,                /* lineNo */
    15,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo l_emlrtDCI = {
    37,                /* lineNo */
    51,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo l_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    26,                /* lineNo */
    50,                /* colNo */
    "row_cts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo m_emlrtDCI = {
    26,                /* lineNo */
    50,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo m_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    26,                /* lineNo */
    40,                /* colNo */
    "row_cts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo n_emlrtDCI = {
    26,                /* lineNo */
    40,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo o_emlrtDCI = {
    22,                /* lineNo */
    22,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo p_emlrtDCI = {
    22,                /* lineNo */
    22,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo q_emlrtDCI = {
    19,                /* lineNo */
    20,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo r_emlrtDCI = {
    19,                /* lineNo */
    20,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo s_emlrtDCI = {
    62,                /* lineNo */
    31,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo t_emlrtDCI = {
    62,                /* lineNo */
    31,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo u_emlrtDCI = {
    63,                /* lineNo */
    29,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo v_emlrtDCI = {
    63,                /* lineNo */
    29,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtBCInfo n_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    22,                /* lineNo */
    33,                /* colNo */
    "block_row_cts",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo o_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    22,                /* lineNo */
    33,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo p_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    26,                /* lineNo */
    5,                 /* colNo */
    "block_row_cts",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo w_emlrtDCI = {
    26,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo q_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    33,                /* lineNo */
    5,                 /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo x_emlrtDCI = {
    33,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo r_emlrtBCI = {
    -1,                     /* iFirst */
    -1,                     /* iLast */
    37,                     /* lineNo */
    62,                     /* colNo */
    "block_cts{nb_blocks}", /* aName */
    "generateRandMat",      /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo y_emlrtDCI = {
    37,                /* lineNo */
    62,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo s_emlrtBCI = {
    -1,                     /* iFirst */
    -1,                     /* iLast */
    37,                     /* lineNo */
    26,                     /* colNo */
    "block_cts{nb_blocks}", /* aName */
    "generateRandMat",      /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo ab_emlrtDCI = {
    37,                /* lineNo */
    26,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo t_emlrtBCI = {
    -1,                       /* iFirst */
    -1,                       /* iLast */
    38,                       /* lineNo */
    58,                       /* colNo */
    "block_cts{block_index}", /* aName */
    "generateRandMat",        /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo u_emlrtBCI = {
    -1,                       /* iFirst */
    -1,                       /* iLast */
    38,                       /* lineNo */
    28,                       /* colNo */
    "block_cts{block_index}", /* aName */
    "generateRandMat",        /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo v_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    42,                /* lineNo */
    50,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo bb_emlrtDCI = {
    42,                /* lineNo */
    50,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo w_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    42,                /* lineNo */
    5,                 /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo cb_emlrtDCI = {
    42,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo x_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    42,                /* lineNo */
    15,                /* colNo */
    "block_cts",       /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo db_emlrtDCI = {
    42,                /* lineNo */
    15,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo y_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    48,                /* lineNo */
    45,                /* colNo */
    "block_row_cts",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo eb_emlrtDCI = {
    48,                /* lineNo */
    45,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo fb_emlrtDCI = {
    51,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo gb_emlrtDCI = {
    51,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo hb_emlrtDCI = {
    52,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo ib_emlrtDCI = {
    52,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo jb_emlrtDCI = {
    58,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo kb_emlrtDCI = {
    58,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo lb_emlrtDCI = {
    59,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo mb_emlrtDCI = {
    59,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo nb_emlrtDCI = {
    62,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo ob_emlrtDCI = {
    62,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtDCInfo pb_emlrtDCI = {
    63,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtDCInfo qb_emlrtDCI = {
    63,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    4                    /* checkKind */
};

static emlrtBCInfo ab_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    104,               /* lineNo */
    13,                /* colNo */
    "A_parts",         /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtDCInfo rb_emlrtDCI = {
    104,               /* lineNo */
    13,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    1                    /* checkKind */
};

static emlrtBCInfo bb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    97,                /* lineNo */
    46,                /* colNo */
    "curr_row_cts",    /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo cb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    97,                /* lineNo */
    22,                /* colNo */
    "curr_row_cts",    /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo db_emlrtBCI = {
    -1,                         /* iFirst */
    -1,                         /* iLast */
    98,                         /* lineNo */
    58,                         /* colNo */
    "block_row_cts{block_row}", /* aName */
    "generateRandMat",          /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo eb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    98,                /* lineNo */
    82,                /* colNo */
    "curr_row_cts",    /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo fb_emlrtBCI = {
    -1,                         /* iFirst */
    -1,                         /* iLast */
    98,                         /* lineNo */
    120,                        /* colNo */
    "block_row_cts{block_row}", /* aName */
    "generateRandMat",          /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo gb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    98,                /* lineNo */
    21,                /* colNo */
    "rel_row_err",     /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo hb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    100,               /* lineNo */
    58,                /* colNo */
    "curr_block_cts",  /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo ib_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    100,               /* lineNo */
    24,                /* colNo */
    "curr_block_cts",  /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo jb_emlrtBCI = {
    -1,                     /* iFirst */
    -1,                     /* iLast */
    101,                    /* lineNo */
    64,                     /* colNo */
    "block_cts{block_row}", /* aName */
    "generateRandMat",      /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo kb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    101,               /* lineNo */
    98,                /* colNo */
    "curr_block_cts",  /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo lb_emlrtBCI = {
    -1,                     /* iFirst */
    -1,                     /* iLast */
    101,                    /* lineNo */
    140,                    /* colNo */
    "block_cts{block_row}", /* aName */
    "generateRandMat",      /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtBCInfo mb_emlrtBCI = {
    -1,                /* iFirst */
    -1,                /* iLast */
    101,               /* lineNo */
    23,                /* colNo */
    "rel_block_err",   /* aName */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m", /* pName */
    0                    /* checkKind */
};

static emlrtRTEInfo ab_emlrtRTEI = {
    13,                                                            /* lineNo */
    9,                                                             /* colNo */
    "sqrt",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elfun/sqrt.m" /* pName */
};

static emlrtRTEInfo eb_emlrtRTEI = {
    19,                /* lineNo */
    15,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo fb_emlrtRTEI = {
    19,                /* lineNo */
    1,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo gb_emlrtRTEI = {
    22,                /* lineNo */
    33,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo hb_emlrtRTEI = {
    33,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo ib_emlrtRTEI = {
    26,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo jb_emlrtRTEI = {
    42,                /* lineNo */
    44,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo kb_emlrtRTEI = {
    32,                                                            /* lineNo */
    5,                                                             /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo lb_emlrtRTEI = {
    33,                                                            /* lineNo */
    5,                                                             /* colNo */
    "find",                                                        /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/elmat/find.m" /* pName */
};

static emlrtRTEInfo mb_emlrtRTEI = {
    42,                /* lineNo */
    24,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo nb_emlrtRTEI = {
    42,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo ob_emlrtRTEI = {
    51,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo pb_emlrtRTEI = {
    58,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo qb_emlrtRTEI = {
    52,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo rb_emlrtRTEI = {
    59,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo sb_emlrtRTEI = {
    62,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo tb_emlrtRTEI = {
    63,                /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo ub_emlrtRTEI = {
    104,               /* lineNo */
    5,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo vb_emlrtRTEI = {
    66,                /* lineNo */
    9,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo wb_emlrtRTEI = {
    88,                /* lineNo */
    15,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo xb_emlrtRTEI = {
    22,                /* lineNo */
    1,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo yb_emlrtRTEI = {
    31,                /* lineNo */
    1,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo ac_emlrtRTEI = {
    45,                /* lineNo */
    1,                 /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo bc_emlrtRTEI = {
    107,               /* lineNo */
    20,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo cc_emlrtRTEI = {
    83,                /* lineNo */
    13,                /* colNo */
    "generateRandMat", /* fName */
    "/home/kobe/Documents/School/Unif/5WIT/Thesis/powermethod/Util_Scripts/"
    "generateRandMat.m" /* pName */
};

static emlrtRTEInfo cd_emlrtRTEI = {
    248,                       /* lineNo */
    5,                         /* colNo */
    "eml_scalar_uint_rdivide", /* fName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/div.m" /* pName
                                                                       */
};

static emlrtRSInfo qg_emlrtRSI = {
    66,        /* lineNo */
    "fprintf", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pathName
                                                                       */
};

static emlrtRSInfo rg_emlrtRSI = {
    68,        /* lineNo */
    "fprintf", /* fcnName */
    "/usr/local/MATLAB/R2022b/toolbox/eml/lib/matlab/iofun/fprintf.m" /* pathName
                                                                       */
};

static emlrtRSInfo tg_emlrtRSI =
    {
        102,      /* lineNo */
        "intmod", /* fcnName */
        "/usr/local/MATLAB/R2022b/toolbox/eml/eml/+coder/+internal/+scalar/"
        "mod.m" /* pathName */
};

/* Function Declarations */
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp,
                                          const char_T u[26]);

static const mxArray *b_feval(const emlrtStack *sp, const mxArray *m1,
                              const mxArray *m2, const mxArray *m3,
                              const mxArray *m4, const mxArray *m5,
                              emlrtMCInfo *location);

static const mxArray *c_emlrt_marshallOut(const int64_T u);

static const mxArray *d_emlrt_marshallOut(const emlrtStack *sp,
                                          const char_T u[33]);

static int64_T div_nde_s64_floor(int64_T numerator);

static int64_T div_s64_floor(const emlrtStack *sp, int64_T numerator,
                             int64_T denominator);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp,
                                        const char_T u[7]);

static const mxArray *f_emlrt_marshallOut(void);

static const mxArray *feval(const emlrtStack *sp, const mxArray *m1,
                            const mxArray *m2, const mxArray *m3,
                            const mxArray *m4, emlrtMCInfo *location);

/* Function Definitions */
static const mxArray *b_emlrt_marshallOut(const emlrtStack *sp,
                                          const char_T u[26])
{
  static const int32_T iv[2] = {1, 26};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)sp, 26, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *b_feval(const emlrtStack *sp, const mxArray *m1,
                              const mxArray *m2, const mxArray *m3,
                              const mxArray *m4, const mxArray *m5,
                              emlrtMCInfo *location)
{
  const mxArray *pArrays[5];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  pArrays[4] = m5;
  return emlrtCallMATLABR2012b((emlrtConstCTX)sp, 1, &m, 5, &pArrays[0],
                               "feval", true, location);
}

static const mxArray *c_emlrt_marshallOut(const int64_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
  *(int64_T *)emlrtMxGetData(m) = u;
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *d_emlrt_marshallOut(const emlrtStack *sp,
                                          const char_T u[33])
{
  static const int32_T iv[2] = {1, 33};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)sp, 33, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static int64_T div_nde_s64_floor(int64_T numerator)
{
  int64_T i;
  if ((numerator < 0L) && (numerator % 10000L != 0L)) {
    i = -1L;
  } else {
    i = 0L;
  }
  return numerator / 10000L + i;
}

static int64_T div_s64_floor(const emlrtStack *sp, int64_T numerator,
                             int64_T denominator)
{
  int64_T quotient;
  if (denominator == 0L) {
    emlrtDivisionByZeroErrorR2012b(NULL, (emlrtConstCTX)sp);
  } else {
    uint64_T absDenominator;
    uint64_T absNumerator;
    uint64_T tempAbsQuotient;
    boolean_T quotientNeedsNegation;
    if (numerator < 0L) {
      absNumerator = ~(uint64_T)numerator + 1UL;
    } else {
      absNumerator = (uint64_T)numerator;
    }
    if (denominator < 0L) {
      absDenominator = ~(uint64_T)denominator + 1UL;
    } else {
      absDenominator = (uint64_T)denominator;
    }
    quotientNeedsNegation = ((numerator < 0L) != (denominator < 0L));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0UL) {
        tempAbsQuotient++;
      }
      quotient = -(int64_T)tempAbsQuotient;
    } else {
      quotient = (int64_T)tempAbsQuotient;
    }
  }
  return quotient;
}

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const char_T u[7])
{
  static const int32_T iv[2] = {1, 7};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)sp, 7, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *f_emlrt_marshallOut(void)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *feval(const emlrtStack *sp, const mxArray *m1,
                            const mxArray *m2, const mxArray *m3,
                            const mxArray *m4, emlrtMCInfo *location)
{
  const mxArray *pArrays[4];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  return emlrtCallMATLABR2012b((emlrtConstCTX)sp, 1, &m, 4, &pArrays[0],
                               "feval", true, location);
}

emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

void generateRandMat(const emlrtStack *sp, real_T size, real_T avg_line,
                     real_T var_line, real_T var_block, b_sparse *A)
{
  static const char_T cv2[33] = {'b', 'l', 'o', 'c', 'k', ' ', 'r', 'o', 'w',
                                 ' ', '%', 'i', ' ', 'h', 'a', 's', ' ', 'p',
                                 'r', 'o', 'c', 'e', 's', 's', 'e', 'd', ' ',
                                 '%', 'i', ' ', 'n', 'n', 'z'};
  static const char_T cv1[26] = {'b', 'l', 'o', 'c', 'k', ' ', 'r',  'o', 'w',
                                 ' ', '%', 'i', ' ', 's', 't', 'a',  'r', 't',
                                 'i', 'n', 'g', '.', '.', '.', '\\', 'n'};
  static const char_T cv[7] = {'f', 'p', 'r', 'i', 'n', 't', 'f'};
  emlrtConstCTX ctx;
  jmp_buf emlrtJBEnviron;
  jmp_buf *volatile emlrtJBStack;
  b_sparse A_temp;
  b_sparse *A_parts_data;
  cell_wrap_0 *block_cts_data;
  cell_wrap_0 *block_row_cts_data;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack j_st;
  emlrtStack k_st;
  emlrtStack l_st;
  emlrtStack m_st;
  emlrtStack n_st;
  emlrtStack o_st;
  emlrtStack p_st;
  emlrtStack q_st;
  emlrtStack st;
  emxArray_boolean_T *t3_d;
  emxArray_cell_wrap_0 *block_cts;
  emxArray_cell_wrap_0 *block_row_cts;
  emxArray_int32_T *expl_temp;
  emxArray_int32_T *ii;
  emxArray_int32_T *jj;
  emxArray_int32_T *t2_colidx;
  emxArray_int32_T *t3_colidx;
  emxArray_real_T *col_ind;
  emxArray_real_T *curr_block_cts;
  emxArray_real_T *curr_row_cts;
  emxArray_real_T *data;
  emxArray_real_T *rel_block_err;
  emxArray_real_T *rel_row_err;
  emxArray_real_T *row_cts;
  emxArray_real_T *t2_d;
  emxArray_real_T *v;
  emxArray_sparse *A_parts;
  int64_T b_block_row;
  int64_T b_col_ind;
  int64_T b_i;
  int64_T b_size;
  int64_T block_row;
  int64_T block_size;
  int64_T i5;
  int64_T lowhigh;
  int64_T nb_blocks;
  int64_T qY;
  int64_T row_end;
  int64_T ub_loop;
  real_T avg_block;
  real_T block_compensation;
  real_T d;
  real_T d1;
  real_T ex;
  real_T lg_sqrt_size;
  real_T r;
  real_T *curr_block_cts_data;
  real_T *curr_row_cts_data;
  real_T *data_data;
  real_T *rel_block_err_data;
  real_T *rel_row_err_data;
  real_T *row_cts_data;
  real_T *v_data;
  uint64_T q;
  uint64_T x;
  uint64_T y;
  int32_T iv[2];
  int32_T a;
  int32_T b_idx;
  int32_T exitg2;
  int32_T generateRandMat_numThreads;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T idx;
  int32_T k;
  int32_T last;
  int32_T loop_ub;
  int32_T unnamed_idx_0;
  int32_T *ii_data;
  int32_T *jj_data;
  boolean_T emlrtHadParallelError = false;
  boolean_T exitg1;
  boolean_T guard1 = false;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  /* GENERATERANDMAT Generates a random sparse matrix */
  /*    The matrix is created to have approximately the right properties */
  /*    The properties are obtained by getting the amount of nonzero's from a */
  /*    normal distribution with the right properties */
  d = muDoubleScalarRound(size);
  if (d < 9.2233720368547758E+18) {
    if (d >= -9.2233720368547758E+18) {
      b_size = (int64_T)d;
    } else {
      b_size = MIN_int64_T;
    }
  } else if (d >= 9.2233720368547758E+18) {
    b_size = MAX_int64_T;
  } else {
    b_size = 0L;
  }
  st.site = &emlrtRSI;
  if (b_size < 0.0) {
    emlrtErrorWithMessageIdR2018a(
        &st, &ab_emlrtRTEI, "Coder:toolbox:ElFunDomainError",
        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
  }
  st.site = &emlrtRSI;
  lg_sqrt_size = b_log2(&st, muDoubleScalarSqrt((real_T)b_size));
  lg_sqrt_size = muDoubleScalarCeil(lg_sqrt_size);
  st.site = &b_emlrtRSI;
  b_st.site = &hb_emlrtRSI;
  i = (int32_T)muDoubleScalarRound(
      muDoubleScalarPower(2.0, muDoubleScalarMin(16.0, lg_sqrt_size + 3.0)));
  block_size = i;
  st.site = &c_emlrtRSI;
  b_st.site = &ib_emlrtRSI;
  c_st.site = &jb_emlrtRSI;
  d_st.site = &kb_emlrtRSI;
  e_st.site = &lb_emlrtRSI;
  if (i == 0L) {
    if (b_size == 0L) {
      nb_blocks = 0L;
    } else if (b_size < 0L) {
      nb_blocks = MIN_int64_T;
    } else {
      nb_blocks = MAX_int64_T;
    }
  } else if (i == 1L) {
    nb_blocks = b_size;
  } else if (i == -1L) {
    if (b_size <= MIN_int64_T) {
      nb_blocks = MAX_int64_T;
    } else {
      nb_blocks = -b_size;
    }
  } else {
    if (b_size >= 0L) {
      x = (uint64_T)b_size;
    } else if (b_size == MIN_int64_T) {
      x = 9223372036854775808UL;
    } else {
      x = (uint64_T)-b_size;
    }
    if (i >= 0L) {
      y = (uint64_T)i;
    } else {
      y = (uint64_T) - (int64_T)i;
    }
    f_st.site = &mb_emlrtRSI;
    if (y == 0UL) {
      emlrtDivisionByZeroErrorR2012b(&cd_emlrtRTEI, &f_st);
    } else {
      q = x / y;
    }
    x -= q * y;
    if ((x > 0UL) && (x >= (y >> 1UL) + (y & 1UL))) {
      q++;
    }
    nb_blocks = (int64_T)q;
    if ((b_size < 0L) != (i < 0L)) {
      nb_blocks = -(int64_T)q;
    }
  }
  block_compensation = 1.0;
  if (i == 0L) {
    qY = b_size;
  } else {
    st.site = &tg_emlrtRSI;
    qY = b_size - div_s64_floor(&st, b_size, i) * i;
  }
  if (qY != 0L) {
    block_compensation = (real_T)qY / (real_T)i;
  }
  st.site = &d_emlrtRSI;
  if (var_line < 0.0) {
    emlrtErrorWithMessageIdR2018a(
        &st, &ab_emlrtRTEI, "Coder:toolbox:ElFunDomainError",
        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
  }
  lg_sqrt_size = muDoubleScalarSqrt(var_line);
  emxInit_real_T(sp, &data, 1, &bc_emlrtRTEI, true);
  st.site = &d_emlrtRSI;
  randn(&st, b_size, data);
  data_data = data->data;
  st.site = &d_emlrtRSI;
  if (!(b_size >= 0.0)) {
    emlrtNonNegativeCheckR2012b((real_T)b_size, &r_emlrtDCI, &st);
  }
  d = (real_T)(int64_T)muDoubleScalarFloor((real_T)b_size);
  if (d != (int32_T)muDoubleScalarFloor(d)) {
    emlrtIntegerCheckR2012b(d, &q_emlrtDCI, &st);
  }
  loop_ub = data->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    data_data[i1] = lg_sqrt_size * data_data[i1] + avg_line;
  }
  b_st.site = &d_emlrtRSI;
  b_round(&b_st, data);
  data_data = data->data;
  b_st.site = &ac_emlrtRSI;
  c_st.site = &bc_emlrtRSI;
  d_st.site = &cc_emlrtRSI;
  e_st.site = &dc_emlrtRSI;
  f_st.site = &ec_emlrtRSI;
  emxInit_real_T(&f_st, &row_cts, 1, &fb_emlrtRTEI, true);
  emxInit_real_T(&f_st, &col_ind, 1, &cc_emlrtRTEI, true);
  if ((int32_T)b_size == data->size[0]) {
    i1 = row_cts->size[0];
    row_cts->size[0] = (int32_T)b_size;
    emxEnsureCapacity_real_T(&f_st, row_cts, i1, &fb_emlrtRTEI);
    row_cts_data = row_cts->data;
    loop_ub = (int32_T)b_size;
    for (i1 = 0; i1 < loop_ub; i1++) {
      lg_sqrt_size = data_data[i1];
      row_cts_data[i1] = muDoubleScalarMax(1.0, lg_sqrt_size);
    }
  } else {
    i1 = col_ind->size[0];
    col_ind->size[0] = (int32_T)b_size;
    emxEnsureCapacity_real_T(&f_st, col_ind, i1, &eb_emlrtRTEI);
    data_data = col_ind->data;
    loop_ub = (int32_T)b_size;
    for (i1 = 0; i1 < loop_ub; i1++) {
      data_data[i1] = 1.0;
    }
    g_st.site = &fc_emlrtRSI;
    expand_max(&g_st, col_ind, data, row_cts);
    row_cts_data = row_cts->data;
  }
  st.site = &e_emlrtRSI;
  lg_sqrt_size = sum(&st, row_cts);
  if (!(nb_blocks >= 0.0)) {
    emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &p_emlrtDCI,
                                (emlrtConstCTX)sp);
  }
  ub_loop = (int64_T)muDoubleScalarFloor((real_T)nb_blocks);
  if ((real_T)ub_loop != (int32_T)muDoubleScalarFloor((real_T)ub_loop)) {
    emlrtIntegerCheckR2012b((real_T)ub_loop, &o_emlrtDCI, (emlrtConstCTX)sp);
  }
  unnamed_idx_0 = (int32_T)nb_blocks;
  emxInit_cell_wrap_0(sp, &block_row_cts, &xb_emlrtRTEI);
  i1 = block_row_cts->size[0];
  block_row_cts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_cell_wrap_0(sp, block_row_cts, i1, &b_emlrtRTEI);
  block_row_cts_data = block_row_cts->data;
  for (i1 = 0; i1 < unnamed_idx_0; i1++) {
    if (i1 > block_row_cts->size[0] - 1) {
      emlrtDynamicBoundsCheckR2012b(i1, 0, block_row_cts->size[0] - 1,
                                    &n_emlrtBCI, (emlrtConstCTX)sp);
    }
    block_row_cts_data[i1].f1->size[0] = 0;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  st.site = &f_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  i1 = block_row_cts->size[0];
  block_row_cts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_cell_wrap_0(sp, block_row_cts, i1, &gb_emlrtRTEI);
  block_row_cts_data = block_row_cts->data;
  if (nb_blocks >= 1L) {
    iv[0] = 1;
  }
  block_row = 1L;
  while (block_row <= nb_blocks) {
    if (block_row < -9223372036854775807L) {
      qY = MIN_int64_T;
    } else {
      qY = block_row - 1L;
    }
    row_end = mul_s64_sat(qY, i);
    if (row_end > 9223372036854775806L) {
      qY = MAX_int64_T;
    } else {
      qY = row_end + 1L;
    }
    row_end = mul_s64_sat(block_row, i);
    if (b_size <= row_end) {
      row_end = b_size;
    }
    if (qY > row_end) {
      i1 = 0;
      i2 = 0;
    } else {
      if ((real_T)qY != (int32_T)muDoubleScalarFloor((real_T)qY)) {
        emlrtIntegerCheckR2012b((real_T)qY, &n_emlrtDCI, (emlrtConstCTX)sp);
      }
      qY = (int64_T)muDoubleScalarFloor((real_T)qY);
      if ((qY < 1L) || (qY > row_cts->size[0])) {
        emlrtDynamicBoundsCheckInt64(qY, 1, row_cts->size[0], &m_emlrtBCI,
                                     (emlrtCTX)sp);
      }
      i1 = (int32_T)qY - 1;
      if ((real_T)row_end != (int32_T)muDoubleScalarFloor((real_T)row_end)) {
        emlrtIntegerCheckR2012b((real_T)row_end, &m_emlrtDCI,
                                (emlrtConstCTX)sp);
      }
      qY = (int64_T)muDoubleScalarFloor((real_T)row_end);
      if ((qY < 1L) || (qY > row_cts->size[0])) {
        emlrtDynamicBoundsCheckInt64(qY, 1, row_cts->size[0], &l_emlrtBCI,
                                     (emlrtCTX)sp);
      }
      i2 = (int32_T)qY;
    }
    loop_ub = i2 - i1;
    iv[1] = loop_ub;
    st.site = &g_emlrtRSI;
    indexShapeCheck(&st, row_cts->size[0], iv);
    d = (int32_T)muDoubleScalarFloor((real_T)block_row);
    if (block_row != d) {
      emlrtIntegerCheckR2012b((real_T)block_row, &w_emlrtDCI,
                              (emlrtConstCTX)sp);
    }
    i2 = (int32_T)(int64_T)muDoubleScalarFloor((real_T)block_row) - 1;
    if ((i2 < 0) || (i2 > block_row_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i2, 0, block_row_cts->size[0] - 1,
                                    &p_emlrtBCI, (emlrtConstCTX)sp);
    }
    i3 = block_row_cts_data[i2].f1->size[0];
    block_row_cts_data[i2].f1->size[0] = loop_ub;
    emxEnsureCapacity_real_T(sp, block_row_cts_data[i2].f1, i3, &ib_emlrtRTEI);
    for (i3 = 0; i3 < loop_ub; i3++) {
      if (block_row != d) {
        emlrtIntegerCheckR2012b((real_T)block_row, &w_emlrtDCI,
                                (emlrtConstCTX)sp);
      }
      if ((i2 < 0) || (i2 > block_row_cts->size[0] - 1)) {
        emlrtDynamicBoundsCheckR2012b(i2, 0, block_row_cts->size[0] - 1,
                                      &p_emlrtBCI, (emlrtConstCTX)sp);
      }
      block_row_cts_data[i2].f1->data[i3] = row_cts_data[i1 + i3];
    }
    block_row++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  st.site = &h_emlrtRSI;
  avg_block = lg_sqrt_size / (real_T)power(b_size) * (real_T)power(i);
  emxInit_cell_wrap_0(sp, &block_cts, &yb_emlrtRTEI);
  i = block_cts->size[0];
  block_cts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_cell_wrap_0(sp, block_cts, i, &b_emlrtRTEI);
  block_cts_data = block_cts->data;
  for (i = 0; i < unnamed_idx_0; i++) {
    if (i > block_cts->size[0] - 1) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &o_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    block_cts_data[i].f1->size[0] = 0;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  st.site = &i_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  i = block_cts->size[0];
  block_cts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_cell_wrap_0(sp, block_cts, i, &gb_emlrtRTEI);
  block_cts_data = block_cts->data;
  row_end = 1L;
  while (row_end <= nb_blocks) {
    st.site = &j_emlrtRSI;
    if (var_block < 0.0) {
      emlrtErrorWithMessageIdR2018a(
          &st, &ab_emlrtRTEI, "Coder:toolbox:ElFunDomainError",
          "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
    }
    lg_sqrt_size = muDoubleScalarSqrt(var_block);
    st.site = &j_emlrtRSI;
    randn(&st, nb_blocks, data);
    data_data = data->data;
    d = (int32_T)muDoubleScalarFloor((real_T)row_end);
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &x_emlrtDCI, (emlrtConstCTX)sp);
    }
    i = (int32_T)(int64_T)muDoubleScalarFloor((real_T)row_end) - 1;
    if ((i < 0) || (i > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &q_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i1 = block_cts_data[i].f1->size[0];
    block_cts_data[i].f1->size[0] = data->size[0];
    emxEnsureCapacity_real_T(sp, block_cts_data[i].f1, i1, &hb_emlrtRTEI);
    loop_ub = data->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      if (row_end != d) {
        emlrtIntegerCheckR2012b((real_T)row_end, &x_emlrtDCI,
                                (emlrtConstCTX)sp);
      }
      if ((i < 0) || (i > block_cts->size[0] - 1)) {
        emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &q_emlrtBCI,
                                      (emlrtConstCTX)sp);
      }
      block_cts_data[i].f1->data[i1] = lg_sqrt_size * data_data[i1] + avg_block;
    }
    row_end++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  st.site = &k_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  row_end = 1L;
  while (row_end <= nb_blocks) {
    if ((real_T)nb_blocks != (int32_T)muDoubleScalarFloor((real_T)nb_blocks)) {
      emlrtIntegerCheckR2012b((real_T)nb_blocks, &l_emlrtDCI,
                              (emlrtConstCTX)sp);
    }
    i = (int32_T)(int64_T)muDoubleScalarFloor((real_T)nb_blocks) - 1;
    if ((i < 0) || (i > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &k_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if ((real_T)nb_blocks != (int32_T)muDoubleScalarFloor((real_T)nb_blocks)) {
      emlrtIntegerCheckR2012b((real_T)nb_blocks, &k_emlrtDCI,
                              (emlrtConstCTX)sp);
    }
    if (((int32_T)nb_blocks - 1 < 0) ||
        ((int32_T)nb_blocks - 1 > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b((int32_T)nb_blocks - 1, 0,
                                    block_cts->size[0] - 1, &j_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i = block_cts_data[(int32_T)nb_blocks - 1].f1->size[0];
    d = (int32_T)muDoubleScalarFloor((real_T)row_end);
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &y_emlrtDCI, (emlrtConstCTX)sp);
    }
    qY = (int64_T)muDoubleScalarFloor((real_T)row_end);
    if ((qY < 1L) || (qY > i)) {
      emlrtDynamicBoundsCheckInt64(qY, 1, i, &r_emlrtBCI, (emlrtCTX)sp);
    }
    i = block_cts_data[(int32_T)nb_blocks - 1].f1->size[0];
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &ab_emlrtDCI, (emlrtConstCTX)sp);
    }
    if ((qY < 1L) || (qY > i)) {
      emlrtDynamicBoundsCheckInt64(qY, 1, i, &s_emlrtBCI, (emlrtCTX)sp);
    }
    block_cts_data[(int32_T)nb_blocks - 1].f1->data[(int32_T)qY - 1] *=
        block_compensation;
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &j_emlrtDCI, (emlrtConstCTX)sp);
    }
    i = (int32_T)(int64_T)muDoubleScalarFloor((real_T)row_end) - 1;
    if ((i < 0) || (i > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &i_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &i_emlrtDCI, (emlrtConstCTX)sp);
    }
    if (((int32_T)row_end - 1 < 0) ||
        ((int32_T)row_end - 1 > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b((int32_T)row_end - 1, 0,
                                    block_cts->size[0] - 1, &h_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    i = block_cts_data[(int32_T)row_end - 1].f1->size[0];
    i1 = block_cts_data[(int32_T)row_end - 1].f1->size[0];
    if ((i1 < 1) || (i1 > i)) {
      emlrtDynamicBoundsCheckR2012b(i1, 1, i, &t_emlrtBCI, (emlrtConstCTX)sp);
    }
    i = block_cts_data[(int32_T)row_end - 1].f1->size[0];
    i2 = block_cts_data[(int32_T)row_end - 1].f1->size[0];
    if ((i2 < 1) || (i2 > i)) {
      emlrtDynamicBoundsCheckR2012b(i2, 1, i, &u_emlrtBCI, (emlrtConstCTX)sp);
    }
    block_cts_data[(int32_T)row_end - 1].f1->data[i2 - 1] =
        block_cts_data[(int32_T)row_end - 1].f1->data[i1 - 1] *
        block_compensation;
    row_end++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  st.site = &l_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  row_end = 1L;
  while (row_end <= nb_blocks) {
    st.site = &m_emlrtRSI;
    if (!(nb_blocks >= 0.0)) {
      emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &h_emlrtDCI, &st);
    }
    if ((real_T)ub_loop != (int32_T)muDoubleScalarFloor((real_T)ub_loop)) {
      emlrtIntegerCheckR2012b((real_T)ub_loop, &g_emlrtDCI, &st);
    }
    d = (int32_T)muDoubleScalarFloor((real_T)row_end);
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &bb_emlrtDCI, &st);
    }
    i = (int32_T)(int64_T)muDoubleScalarFloor((real_T)row_end) - 1;
    if ((i < 0) || (i > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &v_emlrtBCI,
                                    &st);
    }
    i1 = data->size[0];
    data->size[0] = block_cts_data[i].f1->size[0];
    emxEnsureCapacity_real_T(&st, data, i1, &jb_emlrtRTEI);
    data_data = data->data;
    if (row_end != d) {
      emlrtIntegerCheckR2012b((real_T)row_end, &bb_emlrtDCI, &st);
    }
    if ((i < 0) || (i > block_cts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &v_emlrtBCI,
                                    &st);
    }
    loop_ub = block_cts_data[i].f1->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      if (row_end != d) {
        emlrtIntegerCheckR2012b((real_T)row_end, &bb_emlrtDCI, &st);
      }
      if ((i < 0) || (i > block_cts->size[0] - 1)) {
        emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &v_emlrtBCI,
                                      &st);
      }
      data_data[i1] = block_cts_data[i].f1->data[i1];
    }
    b_st.site = &m_emlrtRSI;
    b_round(&b_st, data);
    data_data = data->data;
    b_st.site = &ac_emlrtRSI;
    c_st.site = &bc_emlrtRSI;
    d_st.site = &cc_emlrtRSI;
    e_st.site = &dc_emlrtRSI;
    f_st.site = &ec_emlrtRSI;
    if ((int32_T)nb_blocks == data->size[0]) {
      if (row_end != d) {
        emlrtIntegerCheckR2012b((real_T)row_end, &cb_emlrtDCI, &f_st);
      }
      if ((i < 0) || (i > block_cts->size[0] - 1)) {
        emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &w_emlrtBCI,
                                      &f_st);
      }
      i1 = block_cts_data[i].f1->size[0];
      block_cts_data[i].f1->size[0] = (int32_T)nb_blocks;
      emxEnsureCapacity_real_T(&f_st, block_cts_data[i].f1, i1, &nb_emlrtRTEI);
      loop_ub = (int32_T)nb_blocks;
      for (i1 = 0; i1 < loop_ub; i1++) {
        if (row_end != d) {
          emlrtIntegerCheckR2012b((real_T)row_end, &cb_emlrtDCI, &f_st);
        }
        if ((i < 0) || (i > block_cts->size[0] - 1)) {
          emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1,
                                        &w_emlrtBCI, &f_st);
        }
        lg_sqrt_size = data_data[i1];
        block_cts_data[i].f1->data[i1] = muDoubleScalarMax(1.0, lg_sqrt_size);
      }
    } else {
      i1 = col_ind->size[0];
      col_ind->size[0] = (int32_T)nb_blocks;
      emxEnsureCapacity_real_T(&f_st, col_ind, i1, &mb_emlrtRTEI);
      data_data = col_ind->data;
      loop_ub = (int32_T)nb_blocks;
      for (i1 = 0; i1 < loop_ub; i1++) {
        data_data[i1] = 1.0;
      }
      if (row_end != d) {
        emlrtIntegerCheckR2012b((real_T)row_end, &db_emlrtDCI, &f_st);
      }
      if ((i < 0) || (i > block_cts->size[0] - 1)) {
        emlrtDynamicBoundsCheckR2012b(i, 0, block_cts->size[0] - 1, &x_emlrtBCI,
                                      &f_st);
      }
      g_st.site = &fc_emlrtRSI;
      expand_max(&g_st, col_ind, data, block_cts_data[i].f1);
    }
    row_end++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  emxInit_sparse(sp, &A_parts, &ac_emlrtRTEI);
  i = A_parts->size[0];
  A_parts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_sparse(sp, A_parts, i, &b_emlrtRTEI);
  A_parts_data = A_parts->data;
  for (i = 0; i < unnamed_idx_0; i++) {
    if (i > A_parts->size[0] - 1) {
      emlrtDynamicBoundsCheckR2012b(i, 0, A_parts->size[0] - 1, &g_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    A_parts_data[i].d->size[0] = 0;
    A_parts_data[i].colidx->size[0] = 0;
    A_parts_data[i].rowidx->size[0] = 0;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  if ((real_T)nb_blocks != (int32_T)muDoubleScalarFloor((real_T)nb_blocks)) {
    emlrtIntegerCheckR2012b((real_T)nb_blocks, &f_emlrtDCI, (emlrtConstCTX)sp);
  }
  st.site = &n_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  i = A_parts->size[0];
  A_parts->size[0] = (int32_T)nb_blocks;
  emxEnsureCapacity_sparse(sp, A_parts, i, &gb_emlrtRTEI);
  A_parts_data = A_parts->data;
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  if (!omp_in_parallel()) {
    i_st.site = &n_emlrtRSI;
    c_eml_rand_mt19937ar_stateful_s(true);
    i_st.site = &n_emlrtRSI;
    eml_rand_swap();
  }
  generateRandMat_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel num_threads(generateRandMat_numThreads) private(          \
    curr_row_cts_data, rel_row_err_data, curr_block_cts_data,                  \
    rel_block_err_data, t3_colidx, t3_d, expl_temp, t2_colidx, t2_d,           \
    curr_row_cts, rel_row_err, curr_block_cts, rel_block_err, A_temp,          \
    b_col_ind, emlrtJBEnviron, l_st, q_st, d1, i4, r, i5, a, last, b_i, ctx,   \
    idx, b_idx, exitg2, lowhigh, ex, k, exitg1)                                \
    firstprivate(h_st, i_st, j_st, k_st, m_st, n_st, o_st, p_st, guard1,       \
                 emlrtHadParallelError)
  {
    if (setjmp(emlrtJBEnviron) == 0) {
      h_st.prev = sp;
      h_st.tls = emlrtAllocTLS((emlrtCTX)sp, omp_get_thread_num());
      h_st.site = NULL;
      emlrtSetJmpBuf(&h_st, &emlrtJBEnviron);
      i_st.prev = &h_st;
      i_st.tls = h_st.tls;
      j_st.prev = &i_st;
      j_st.tls = i_st.tls;
      k_st.prev = &j_st;
      k_st.tls = j_st.tls;
      l_st.prev = &j_st;
      l_st.tls = j_st.tls;
      m_st.prev = &k_st;
      m_st.tls = k_st.tls;
      n_st.prev = &m_st;
      n_st.tls = m_st.tls;
      o_st.prev = &n_st;
      o_st.tls = n_st.tls;
      p_st.prev = &o_st;
      p_st.tls = o_st.tls;
      q_st.prev = &p_st;
      q_st.tls = p_st.tls;
      emxInit_int32_T(&h_st, &t3_colidx, &wb_emlrtRTEI, true);
      emxInit_boolean_T(&h_st, &t3_d, &wb_emlrtRTEI);
      emxInit_int32_T(&h_st, &expl_temp, &wb_emlrtRTEI, true);
      emxInit_int32_T(&h_st, &t2_colidx, &wb_emlrtRTEI, true);
      emxInit_real_T(&h_st, &t2_d, 1, &wb_emlrtRTEI, true);
      emxInit_real_T(&h_st, &curr_row_cts, 1, &ob_emlrtRTEI, true);
      emxInit_real_T(&h_st, &rel_row_err, 1, &qb_emlrtRTEI, true);
      emxInit_real_T(&h_st, &curr_block_cts, 2, &sb_emlrtRTEI, true);
      emxInit_real_T(&h_st, &rel_block_err, 2, &tb_emlrtRTEI, true);
      emxInitStruct_sparse(&h_st, &A_temp, &vb_emlrtRTEI, true);
    } else {
      emlrtHadParallelError = true;
    }
#pragma omp for nowait
    for (b_block_row = 1L; b_block_row <= ub_loop; b_block_row++) {
      if (emlrtHadParallelError) {
        continue;
      }
      if (setjmp(emlrtJBEnviron) == 0) {
        i_st.site = &o_emlrtRSI;
        j_st.site = &vc_emlrtRSI;
        if (!emlrtIsInParallelRegion(&j_st)) {
          emlrtAssertMATLABThread(&j_st, &emlrtRTEI);
          k_st.site = &qg_emlrtRSI;
          l_st.site = &rg_emlrtRSI;
          emlrt_marshallIn(&k_st,
                           feval(&k_st, emlrt_marshallOut(&k_st, cv),
                                 f_emlrt_marshallOut(),
                                 b_emlrt_marshallOut(&l_st, cv1),
                                 c_emlrt_marshallOut(b_block_row), &emlrtMCI),
                           "<output of feval>");
        } else {
          k_st.site = &wc_emlrtRSI;
          if (emlrtIsInParallelRegion(&k_st)) {
            ctx = emlrtGetRootTLSGlobal();
            emlrtMexPrintf(ctx, "block row %li starting...\n", b_block_row);
          } else {
            mexPrintf("block row %li starting...\n", b_block_row);
          }
        }
        d1 = (int32_T)muDoubleScalarFloor((real_T)b_block_row);
        if (b_block_row != d1) {
          emlrtIntegerCheckR2012b((real_T)b_block_row, &eb_emlrtDCI, &h_st);
        }
        i4 = (int32_T)(int64_T)muDoubleScalarFloor((real_T)b_block_row) - 1;
        if ((i4 < 0) || (i4 > block_row_cts->size[0] - 1)) {
          emlrtDynamicBoundsCheckR2012b(i4, 0, block_row_cts->size[0] - 1,
                                        &y_emlrtBCI, &h_st);
        }
        i_st.site = &p_emlrtRSI;
        r = muDoubleScalarRound(sum(&i_st, block_row_cts_data[i4].f1));
        if (r < 9.2233720368547758E+18) {
          if (r >= -9.2233720368547758E+18) {
            i5 = (int64_T)r;
          } else {
            i5 = MIN_int64_T;
          }
        } else if (r >= 9.2233720368547758E+18) {
          i5 = MAX_int64_T;
        } else {
          i5 = 0L;
        }
        if (b_block_row != nb_blocks) {
          if (!(block_size >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)block_size, &gb_emlrtDCI,
                                        &h_st);
          }
          r = (real_T)(int64_T)muDoubleScalarFloor((real_T)block_size);
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &fb_emlrtDCI, &h_st);
          }
          a = curr_row_cts->size[0];
          curr_row_cts->size[0] = (int32_T)(int64_T)muDoubleScalarFloor(r);
          emxEnsureCapacity_real_T(&h_st, curr_row_cts, a, &ob_emlrtRTEI);
          curr_row_cts_data = curr_row_cts->data;
          if (!(block_size >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)block_size, &gb_emlrtDCI,
                                        &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &fb_emlrtDCI, &h_st);
          }
          last = (int32_T)(int64_T)muDoubleScalarFloor(r);
          for (a = 0; a < last; a++) {
            curr_row_cts_data[a] = 0.0;
          }
          if (!(block_size >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)block_size, &ib_emlrtDCI,
                                        &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &hb_emlrtDCI, &h_st);
          }
          a = rel_row_err->size[0];
          rel_row_err->size[0] = (int32_T)(int64_T)muDoubleScalarFloor(r);
          emxEnsureCapacity_real_T(&h_st, rel_row_err, a, &qb_emlrtRTEI);
          rel_row_err_data = rel_row_err->data;
          if (!(block_size >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)block_size, &ib_emlrtDCI,
                                        &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &hb_emlrtDCI, &h_st);
          }
          last = (int32_T)(int64_T)muDoubleScalarFloor(r);
          for (a = 0; a < last; a++) {
            rel_row_err_data[a] = 1.0;
          }
        } else {
          if (block_size == 0L) {
            b_col_ind = b_size;
          } else {
            i_st.site = &tg_emlrtRSI;
            b_col_ind =
                b_size - div_s64_floor(&i_st, b_size, block_size) * block_size;
          }
          if (b_col_ind == 0L) {
            b_col_ind = block_size;
          }
          if (!(b_col_ind >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)b_col_ind, &kb_emlrtDCI, &h_st);
          }
          r = (real_T)(int64_T)muDoubleScalarFloor((real_T)b_col_ind);
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &jb_emlrtDCI, &h_st);
          }
          a = curr_row_cts->size[0];
          curr_row_cts->size[0] = (int32_T)(int64_T)muDoubleScalarFloor(r);
          emxEnsureCapacity_real_T(&h_st, curr_row_cts, a, &pb_emlrtRTEI);
          curr_row_cts_data = curr_row_cts->data;
          if (!(b_col_ind >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)b_col_ind, &kb_emlrtDCI, &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &jb_emlrtDCI, &h_st);
          }
          last = (int32_T)(int64_T)muDoubleScalarFloor(r);
          for (a = 0; a < last; a++) {
            curr_row_cts_data[a] = 0.0;
          }
          if (!(b_col_ind >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)b_col_ind, &mb_emlrtDCI, &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &lb_emlrtDCI, &h_st);
          }
          a = rel_row_err->size[0];
          rel_row_err->size[0] = (int32_T)(int64_T)muDoubleScalarFloor(r);
          emxEnsureCapacity_real_T(&h_st, rel_row_err, a, &rb_emlrtRTEI);
          rel_row_err_data = rel_row_err->data;
          if (!(b_col_ind >= 0.0)) {
            emlrtNonNegativeCheckR2012b((real_T)b_col_ind, &mb_emlrtDCI, &h_st);
          }
          if (r != (int32_T)muDoubleScalarFloor(r)) {
            emlrtIntegerCheckR2012b(r, &lb_emlrtDCI, &h_st);
          }
          last = (int32_T)(int64_T)muDoubleScalarFloor(r);
          for (a = 0; a < last; a++) {
            rel_row_err_data[a] = 1.0;
          }
        }
        a = curr_block_cts->size[0] * curr_block_cts->size[1];
        curr_block_cts->size[0] = 1;
        emxEnsureCapacity_real_T(&h_st, curr_block_cts, a, &sb_emlrtRTEI);
        if (!(nb_blocks >= 0.0)) {
          emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &t_emlrtDCI, &h_st);
        }
        r = (real_T)(int64_T)muDoubleScalarFloor((real_T)nb_blocks);
        if (r != (int32_T)muDoubleScalarFloor(r)) {
          emlrtIntegerCheckR2012b(r, &s_emlrtDCI, &h_st);
        }
        a = curr_block_cts->size[0] * curr_block_cts->size[1];
        curr_block_cts->size[1] = (int32_T)(int64_T)muDoubleScalarFloor(r);
        emxEnsureCapacity_real_T(&h_st, curr_block_cts, a, &sb_emlrtRTEI);
        curr_block_cts_data = curr_block_cts->data;
        if (!(nb_blocks >= 0.0)) {
          emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &ob_emlrtDCI, &h_st);
        }
        r = (real_T)(int64_T)muDoubleScalarFloor((real_T)nb_blocks);
        if (r != (int32_T)muDoubleScalarFloor(r)) {
          emlrtIntegerCheckR2012b(r, &nb_emlrtDCI, &h_st);
        }
        last = (int32_T)(int64_T)muDoubleScalarFloor(r);
        for (a = 0; a < last; a++) {
          curr_block_cts_data[a] = 0.0;
        }
        a = rel_block_err->size[0] * rel_block_err->size[1];
        rel_block_err->size[0] = 1;
        emxEnsureCapacity_real_T(&h_st, rel_block_err, a, &tb_emlrtRTEI);
        if (!(nb_blocks >= 0.0)) {
          emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &v_emlrtDCI, &h_st);
        }
        r = (real_T)(int64_T)muDoubleScalarFloor((real_T)nb_blocks);
        if (r != (int32_T)muDoubleScalarFloor(r)) {
          emlrtIntegerCheckR2012b(r, &u_emlrtDCI, &h_st);
        }
        a = rel_block_err->size[0] * rel_block_err->size[1];
        rel_block_err->size[1] = (int32_T)(int64_T)muDoubleScalarFloor(r);
        emxEnsureCapacity_real_T(&h_st, rel_block_err, a, &tb_emlrtRTEI);
        rel_block_err_data = rel_block_err->data;
        if (!(nb_blocks >= 0.0)) {
          emlrtNonNegativeCheckR2012b((real_T)nb_blocks, &qb_emlrtDCI, &h_st);
        }
        r = (real_T)(int64_T)muDoubleScalarFloor((real_T)nb_blocks);
        if (r != (int32_T)muDoubleScalarFloor(r)) {
          emlrtIntegerCheckR2012b(r, &pb_emlrtDCI, &h_st);
        }
        last = (int32_T)(int64_T)muDoubleScalarFloor(r);
        for (a = 0; a < last; a++) {
          rel_block_err_data[a] = 1.0;
        }
        if (b_block_row != nb_blocks) {
          i_st.site = &q_emlrtRSI;
          spalloc(&i_st, block_size, b_size, i5, &A_temp);
        } else {
          if (block_size == 0L) {
            b_col_ind = b_size;
          } else {
            i_st.site = &tg_emlrtRSI;
            b_col_ind =
                b_size - div_s64_floor(&i_st, b_size, block_size) * block_size;
          }
          if (b_col_ind == 0L) {
            i_st.site = &q_emlrtRSI;
            spalloc(&i_st, block_size, b_size, i5, &A_temp);
          } else {
            if (block_size == 0L) {
              b_col_ind = b_size;
            } else {
              i_st.site = &tg_emlrtRSI;
              b_col_ind = b_size -
                          div_s64_floor(&i_st, b_size, block_size) * block_size;
            }
            i_st.site = &r_emlrtRSI;
            spalloc(&i_st, b_col_ind, b_size, i5, &A_temp);
          }
        }
        i_st.site = &s_emlrtRSI;
        if (i5 > 9223372036854775806L) {
          j_st.site = &yb_emlrtRSI;
          check_forloop_overflow_error(&j_st);
        }
        b_i = 1L;
        while (b_i <= i5) {
          if (b_i - div_nde_s64_floor(b_i) * 10000L == 0L) {
            i_st.site = &t_emlrtRSI;
            j_st.site = &vc_emlrtRSI;
            if (!emlrtIsInParallelRegion(&j_st)) {
              emlrtAssertMATLABThread(&j_st, &emlrtRTEI);
              k_st.site = &qg_emlrtRSI;
              l_st.site = &rg_emlrtRSI;
              emlrt_marshallIn(&k_st,
                               b_feval(&k_st, emlrt_marshallOut(&k_st, cv),
                                       f_emlrt_marshallOut(),
                                       d_emlrt_marshallOut(&l_st, cv2),
                                       c_emlrt_marshallOut(b_block_row),
                                       c_emlrt_marshallOut(b_i), &emlrtMCI),
                               "<output of feval>");
            } else {
              k_st.site = &wc_emlrtRSI;
              if (emlrtIsInParallelRegion(&k_st)) {
                ctx = emlrtGetRootTLSGlobal();
                emlrtMexPrintf(ctx, "block row %li has processed %li nnz",
                               b_block_row, b_i);
              } else {
                mexPrintf("block row %li has processed %li nnz", b_block_row,
                          b_i);
              }
            }
          }
          /*  Find row and block col which needs the most nnz by checking the */
          /*  relative error */
          i_st.site = &u_emlrtRSI;
          j_st.site = &id_emlrtRSI;
          k_st.site = &jd_emlrtRSI;
          m_st.site = &kd_emlrtRSI;
          if (rel_row_err->size[0] < 1) {
            emlrtErrorWithMessageIdR2018a(
                &m_st, &c_emlrtRTEI, "Coder:toolbox:eml_min_or_max_varDimZero",
                "Coder:toolbox:eml_min_or_max_varDimZero", 0);
          }
          n_st.site = &ld_emlrtRSI;
          last = rel_row_err->size[0];
          if (rel_row_err->size[0] <= 2) {
            if (rel_row_err->size[0] == 1) {
              idx = 1;
            } else if ((rel_row_err_data[0] < rel_row_err_data[1]) ||
                       (muDoubleScalarIsNaN(rel_row_err_data[0]) &&
                        (!muDoubleScalarIsNaN(rel_row_err_data[1])))) {
              idx = 2;
            } else {
              idx = 1;
            }
          } else {
            o_st.site = &nd_emlrtRSI;
            if (!muDoubleScalarIsNaN(rel_row_err_data[0])) {
              idx = 1;
            } else {
              idx = 0;
              p_st.site = &od_emlrtRSI;
              if (rel_row_err->size[0] > 2147483646) {
                q_st.site = &yb_emlrtRSI;
                b_check_forloop_overflow_error(&q_st);
              }
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= last)) {
                if (!muDoubleScalarIsNaN(rel_row_err_data[k - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }
            if (idx == 0) {
              idx = 1;
            } else {
              o_st.site = &md_emlrtRSI;
              ex = rel_row_err_data[idx - 1];
              a = idx + 1;
              p_st.site = &pd_emlrtRSI;
              if ((idx + 1 <= rel_row_err->size[0]) &&
                  (rel_row_err->size[0] > 2147483646)) {
                q_st.site = &yb_emlrtRSI;
                b_check_forloop_overflow_error(&q_st);
              }
              for (k = a; k <= last; k++) {
                r = rel_row_err_data[k - 1];
                if (ex < r) {
                  ex = r;
                  idx = k;
                }
              }
            }
          }
          i_st.site = &v_emlrtRSI;
          j_st.site = &id_emlrtRSI;
          k_st.site = &jd_emlrtRSI;
          m_st.site = &kd_emlrtRSI;
          if (rel_block_err->size[1] < 1) {
            emlrtErrorWithMessageIdR2018a(
                &m_st, &c_emlrtRTEI, "Coder:toolbox:eml_min_or_max_varDimZero",
                "Coder:toolbox:eml_min_or_max_varDimZero", 0);
          }
          n_st.site = &ld_emlrtRSI;
          last = rel_block_err->size[1];
          if (rel_block_err->size[1] <= 2) {
            if (rel_block_err->size[1] == 1) {
              b_idx = 1;
            } else if ((rel_block_err_data[0] < rel_block_err_data[1]) ||
                       (muDoubleScalarIsNaN(rel_block_err_data[0]) &&
                        (!muDoubleScalarIsNaN(rel_block_err_data[1])))) {
              b_idx = 2;
            } else {
              b_idx = 1;
            }
          } else {
            o_st.site = &nd_emlrtRSI;
            if (!muDoubleScalarIsNaN(rel_block_err_data[0])) {
              b_idx = 1;
            } else {
              b_idx = 0;
              p_st.site = &od_emlrtRSI;
              if (rel_block_err->size[1] > 2147483646) {
                q_st.site = &yb_emlrtRSI;
                b_check_forloop_overflow_error(&q_st);
              }
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= last)) {
                if (!muDoubleScalarIsNaN(rel_block_err_data[k - 1])) {
                  b_idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }
            if (b_idx == 0) {
              b_idx = 1;
            } else {
              o_st.site = &md_emlrtRSI;
              ex = rel_block_err_data[b_idx - 1];
              a = b_idx + 1;
              p_st.site = &pd_emlrtRSI;
              if ((b_idx + 1 <= rel_block_err->size[1]) &&
                  (rel_block_err->size[1] > 2147483646)) {
                q_st.site = &yb_emlrtRSI;
                b_check_forloop_overflow_error(&q_st);
              }
              for (k = a; k <= last; k++) {
                r = rel_block_err_data[k - 1];
                if (ex < r) {
                  ex = r;
                  b_idx = k;
                }
              }
            }
          }
          /*  Generate a random column index in this block col */
          guard1 = false;
          if (nb_blocks != b_idx) {
            guard1 = true;
          } else {
            if (block_size == 0L) {
              b_col_ind = b_size;
            } else {
              i_st.site = &tg_emlrtRSI;
              b_col_ind = b_size -
                          div_s64_floor(&i_st, b_size, block_size) * block_size;
            }
            if (b_col_ind == 0L) {
              guard1 = true;
            } else {
              i_st.site = &x_emlrtRSI;
              j_st.site = &qd_emlrtRSI;
              b_col_ind = times(&j_st, block_size, (real_T)b_idx - 1.0);
              if (block_size == 0L) {
                lowhigh = b_size;
              } else {
                i_st.site = &tg_emlrtRSI;
                lowhigh = b_size -
                          div_s64_floor(&i_st, b_size, block_size) * block_size;
              }
              i_st.site = &x_emlrtRSI;
              j_st.site = &de_emlrtRSI;
              r = b_rand(&j_st);
              b_col_ind = plus(b_col_ind,
                               muDoubleScalarFloor(r * (real_T)lowhigh) + 1.0);
            }
          }
          if (guard1) {
            i_st.site = &w_emlrtRSI;
            j_st.site = &qd_emlrtRSI;
            b_col_ind = times(&j_st, block_size, (real_T)b_idx - 1.0);
            i_st.site = &w_emlrtRSI;
            j_st.site = &de_emlrtRSI;
            r = b_rand(&j_st);
            b_col_ind = plus(b_col_ind,
                             muDoubleScalarFloor(r * (real_T)block_size) + 1.0);
          }
          do {
            exitg2 = 0;
            i_st.site = &y_emlrtRSI;
            sparse_parenReference(&i_st, A_temp.d, A_temp.colidx, A_temp.rowidx,
                                  A_temp.m, A_temp.n, idx, b_col_ind, t2_d,
                                  t2_colidx, expl_temp);
            i_st.site = &y_emlrtRSI;
            sparse_ne(&i_st, t2_d, t2_colidx, t3_d, t3_colidx, expl_temp);
            i_st.site = &y_emlrtRSI;
            if (sparse_full(&i_st, t3_d, t3_colidx)) {
              guard1 = false;
              if (nb_blocks != b_idx) {
                guard1 = true;
              } else {
                if (block_size == 0L) {
                  b_col_ind = b_size;
                } else {
                  i_st.site = &tg_emlrtRSI;
                  b_col_ind =
                      b_size -
                      div_s64_floor(&i_st, b_size, block_size) * block_size;
                }
                if (b_col_ind == 0L) {
                  guard1 = true;
                } else {
                  i_st.site = &bb_emlrtRSI;
                  j_st.site = &qd_emlrtRSI;
                  b_col_ind = times(&j_st, block_size, (real_T)b_idx - 1.0);
                  if (block_size == 0L) {
                    lowhigh = b_size;
                  } else {
                    i_st.site = &tg_emlrtRSI;
                    lowhigh =
                        b_size -
                        div_s64_floor(&i_st, b_size, block_size) * block_size;
                  }
                  i_st.site = &bb_emlrtRSI;
                  j_st.site = &de_emlrtRSI;
                  r = b_rand(&j_st);
                  b_col_ind =
                      plus(b_col_ind,
                           muDoubleScalarFloor(r * (real_T)lowhigh) + 1.0);
                }
              }
              if (guard1) {
                i_st.site = &ab_emlrtRSI;
                j_st.site = &qd_emlrtRSI;
                b_col_ind = times(&j_st, block_size, (real_T)b_idx - 1.0);
                i_st.site = &ab_emlrtRSI;
                j_st.site = &de_emlrtRSI;
                r = b_rand(&j_st);
                b_col_ind =
                    plus(b_col_ind,
                         muDoubleScalarFloor(r * (real_T)block_size) + 1.0);
              }
              if (*emlrtBreakCheckR2012bFlagVar != 0) {
                emlrtBreakCheckR2012b(&h_st);
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);
          i_st.site = &cb_emlrtRSI;
          sparse_parenAssign(&i_st, &A_temp, idx, b_col_ind);
          if ((idx < 1) || (idx > curr_row_cts->size[0])) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, curr_row_cts->size[0],
                                          &bb_emlrtBCI, &h_st);
          }
          if (idx > curr_row_cts->size[0]) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, curr_row_cts->size[0],
                                          &cb_emlrtBCI, &h_st);
          }
          curr_row_cts_data[idx - 1]++;
          if (b_block_row != d1) {
            emlrtIntegerCheckR2012b((real_T)b_block_row, &e_emlrtDCI, &h_st);
          }
          if ((i4 < 0) || (i4 > block_row_cts->size[0] - 1)) {
            emlrtDynamicBoundsCheckR2012b(i4, 0, block_row_cts->size[0] - 1,
                                          &d_emlrtBCI, &h_st);
          }
          if (b_block_row != d1) {
            emlrtIntegerCheckR2012b((real_T)b_block_row, &d_emlrtDCI, &h_st);
          }
          if ((i4 < 0) || (i4 > block_row_cts->size[0] - 1)) {
            emlrtDynamicBoundsCheckR2012b(i4, 0, block_row_cts->size[0] - 1,
                                          &c_emlrtBCI, &h_st);
          }
          a = block_row_cts_data[(int32_T)b_block_row - 1].f1->size[0];
          if (idx > a) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, a, &db_emlrtBCI, &h_st);
          }
          if (idx > curr_row_cts->size[0]) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, curr_row_cts->size[0],
                                          &eb_emlrtBCI, &h_st);
          }
          a = block_row_cts_data[(int32_T)b_block_row - 1].f1->size[0];
          if (idx > a) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, a, &fb_emlrtBCI, &h_st);
          }
          if (idx > rel_row_err->size[0]) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, rel_row_err->size[0],
                                          &gb_emlrtBCI, &h_st);
          }
          r = block_row_cts_data[(int32_T)b_block_row - 1].f1->data[idx - 1];
          rel_row_err_data[idx - 1] = (r - curr_row_cts_data[idx - 1]) / r;
          if ((b_idx < 1) || (b_idx > curr_block_cts->size[1])) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, curr_block_cts->size[1],
                                          &hb_emlrtBCI, &h_st);
          }
          if (b_idx > curr_block_cts->size[1]) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, curr_block_cts->size[1],
                                          &ib_emlrtBCI, &h_st);
          }
          curr_block_cts_data[b_idx - 1]++;
          if (b_block_row != d1) {
            emlrtIntegerCheckR2012b((real_T)b_block_row, &c_emlrtDCI, &h_st);
          }
          if ((i4 < 0) || (i4 > block_cts->size[0] - 1)) {
            emlrtDynamicBoundsCheckR2012b(i4, 0, block_cts->size[0] - 1,
                                          &b_emlrtBCI, &h_st);
          }
          if (b_block_row != d1) {
            emlrtIntegerCheckR2012b((real_T)b_block_row, &b_emlrtDCI, &h_st);
          }
          if ((i4 < 0) || (i4 > block_cts->size[0] - 1)) {
            emlrtDynamicBoundsCheckR2012b(i4, 0, block_cts->size[0] - 1,
                                          &emlrtBCI, &h_st);
          }
          a = block_cts_data[(int32_T)b_block_row - 1].f1->size[0];
          if (b_idx > a) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, a, &jb_emlrtBCI, &h_st);
          }
          if (b_idx > curr_block_cts->size[1]) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, curr_block_cts->size[1],
                                          &kb_emlrtBCI, &h_st);
          }
          a = block_cts_data[(int32_T)b_block_row - 1].f1->size[0];
          if (b_idx > a) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, a, &lb_emlrtBCI, &h_st);
          }
          if (b_idx > rel_block_err->size[1]) {
            emlrtDynamicBoundsCheckR2012b(b_idx, 1, rel_block_err->size[1],
                                          &mb_emlrtBCI, &h_st);
          }
          r = block_cts_data[(int32_T)b_block_row - 1].f1->data[b_idx - 1];
          rel_block_err_data[b_idx - 1] =
              (r - curr_block_cts_data[b_idx - 1]) / r;
          b_i++;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(&h_st);
          }
        }
        if (b_block_row != d1) {
          emlrtIntegerCheckR2012b((real_T)b_block_row, &rb_emlrtDCI, &h_st);
        }
        if ((i4 < 0) || (i4 > A_parts->size[0] - 1)) {
          emlrtDynamicBoundsCheckR2012b(i4, 0, A_parts->size[0] - 1,
                                        &ab_emlrtBCI, &h_st);
        }
        emxCopyStruct_sparse(&h_st, &A_parts_data[i4], &A_temp, &ub_emlrtRTEI);
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(&h_st);
        }
      } else {
        emlrtHadParallelError = true;
      }
    }
    if (!emlrtHadParallelError) {
      emlrtHeapReferenceStackLeaveScope(&h_st, 10);
      emxFreeStruct_sparse(&h_st, &A_temp);
      emxFree_real_T(&h_st, &rel_block_err);
      emxFree_real_T(&h_st, &curr_block_cts);
      emxFree_real_T(&h_st, &rel_row_err);
      emxFree_real_T(&h_st, &curr_row_cts);
      emxFree_real_T(&h_st, &t2_d);
      emxFree_int32_T(&h_st, &t2_colidx);
      emxFree_int32_T(&h_st, &expl_temp);
      emxFree_boolean_T(&h_st, &t3_d);
      emxFree_int32_T(&h_st, &t3_colidx);
    }
  }
  if (!omp_in_parallel()) {
    i_st.site = &n_emlrtRSI;
    c_eml_rand_mt19937ar_stateful_s(false);
    i_st.site = &n_emlrtRSI;
    eml_rand_swap();
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emxFree_cell_wrap_0(sp, &block_cts);
  emxFree_cell_wrap_0(sp, &block_row_cts);
  if (A_parts->size[0] - 1 < 0) {
    emlrtDynamicBoundsCheckR2012b(0, 0, A_parts->size[0] - 1, &f_emlrtBCI,
                                  (emlrtConstCTX)sp);
  }
  st.site = &db_emlrtRSI;
  emxInit_int32_T(&st, &ii, &b_emlrtRTEI, true);
  emxInit_int32_T(&st, &jj, &b_emlrtRTEI, true);
  b_st.site = &gf_emlrtRSI;
  eml_find(&b_st, A_parts_data[0].d, A_parts_data[0].colidx,
           A_parts_data[0].rowidx, A_parts_data[0].m, A_parts_data[0].n, ii, jj,
           data);
  jj_data = jj->data;
  ii_data = ii->data;
  i = row_cts->size[0];
  row_cts->size[0] = ii->size[0];
  emxEnsureCapacity_real_T(&st, row_cts, i, &kb_emlrtRTEI);
  row_cts_data = row_cts->data;
  loop_ub = ii->size[0];
  for (i = 0; i < loop_ub; i++) {
    row_cts_data[i] = ii_data[i];
  }
  i = col_ind->size[0];
  col_ind->size[0] = jj->size[0];
  emxEnsureCapacity_real_T(&st, col_ind, i, &lb_emlrtRTEI);
  data_data = col_ind->data;
  loop_ub = jj->size[0];
  for (i = 0; i < loop_ub; i++) {
    data_data[i] = jj_data[i];
  }
  st.site = &eb_emlrtRSI;
  if (nb_blocks > 9223372036854775806L) {
    b_st.site = &yb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  block_row = 2L;
  emxInit_real_T(sp, &v, 1, &b_emlrtRTEI, true);
  while (block_row <= nb_blocks) {
    st.site = &fb_emlrtRSI;
    if ((real_T)block_row != (int32_T)muDoubleScalarFloor((real_T)block_row)) {
      emlrtIntegerCheckR2012b((real_T)block_row, &emlrtDCI, &st);
    }
    i = (int32_T)(int64_T)muDoubleScalarFloor((real_T)block_row) - 1;
    if ((i < 0) || (i > A_parts->size[0] - 1)) {
      emlrtDynamicBoundsCheckR2012b(i, 0, A_parts->size[0] - 1, &e_emlrtBCI,
                                    &st);
    }
    b_st.site = &gf_emlrtRSI;
    eml_find(&b_st, A_parts_data[(int32_T)block_row - 1].d,
             A_parts_data[(int32_T)block_row - 1].colidx,
             A_parts_data[(int32_T)block_row - 1].rowidx,
             A_parts_data[(int32_T)block_row - 1].m,
             A_parts_data[(int32_T)block_row - 1].n, ii, jj, v);
    v_data = v->data;
    jj_data = jj->data;
    ii_data = ii->data;
    i = row_cts->size[0];
    i1 = row_cts->size[0];
    row_cts->size[0] += ii->size[0];
    emxEnsureCapacity_real_T(sp, row_cts, i1, &b_emlrtRTEI);
    row_cts_data = row_cts->data;
    if (block_row < -9223372036854775807L) {
      qY = MIN_int64_T;
    } else {
      qY = block_row - 1L;
    }
    lg_sqrt_size = (real_T)mul_s64_sat(qY, block_size);
    loop_ub = ii->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      row_cts_data[i + i1] = (real_T)ii_data[i1] + lg_sqrt_size;
    }
    i = col_ind->size[0];
    i1 = col_ind->size[0];
    col_ind->size[0] += jj->size[0];
    emxEnsureCapacity_real_T(sp, col_ind, i1, &b_emlrtRTEI);
    data_data = col_ind->data;
    loop_ub = jj->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      data_data[i + i1] = jj_data[i1];
    }
    i = data->size[0];
    i1 = data->size[0];
    data->size[0] += v->size[0];
    emxEnsureCapacity_real_T(sp, data, i1, &b_emlrtRTEI);
    data_data = data->data;
    loop_ub = v->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      data_data[i + i1] = v_data[i1];
    }
    block_row++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  emxFree_real_T(sp, &v);
  emxFree_int32_T(sp, &jj);
  emxFree_int32_T(sp, &ii);
  emxFree_sparse(sp, &A_parts);
  st.site = &gb_emlrtRSI;
  sparse(&st, row_cts, col_ind, data, b_size, b_size, A);
  emxFree_real_T(sp, &col_ind);
  emxFree_real_T(sp, &data);
  emxFree_real_T(sp, &row_cts);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
}

int32_T getThreadID(void)
{
  return threadID;
}

void getThreadID_init(const emlrtStack *sp)
{
  jmp_buf *volatile emlrtJBStack;
  int32_T getThreadID_init_numThreads;
  int32_T i;
  int32_T ub_loop;
  ub_loop = omp_get_max_threads();
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  getThreadID_init_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel for schedule(static)                                      \
    num_threads(getThreadID_init_numThreads)

  for (i = 1; i <= ub_loop; i++) {
    threadID = omp_get_thread_num();
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
}

/* End of code generation (generateRandMat.c) */
