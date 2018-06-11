#include <stdio.h>
#include <gsl/gsl_multimin.h>

#include <real.h>
#include <he/err.h>
#include <he/memory.h>

#include "alg/min.h"

#define T AlgMin

struct T {
    real *pos;
    real *xx, *yy, *zz;

    gsl_multimin_function_fdf func;
};

static double f(const gsl_vector *v, void *param) {
    return 0.0;
}

static double df(const gsl_vector *v, void *param, gsl_vector *df) {
    return 0.0;
}

void fdf (const gsl_vector *x, void *params, double *f0, gsl_vector *df0) {
    *f0 = f(x, params);
    df(x, params, df0);
}

int alg_min_ini(int type, AlgMinF* f, AlgMinDF* df, int n, void *param, /**/ T **pq) {
    T *q;
    MALLOC(1, &q);

    q->func.f = f;
    q->func.df = df;
    q->func.fdf = fdf;

    *pq = q;
    return HE_OK;
}

int alg_min_free(T *q) { FREE(q); return HE_OK; }
