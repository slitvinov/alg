#include <stdio.h>
#include <gsl/gsl_multimin.h>

#include <real.h>
#include <he/err.h>
#include <he/memory.h>

#include "alg/min.h"

#define T AlgMin

struct T {
    int n;
    gsl_multimin_fdfminimizer *min;
    real *position, *force;

    AlgMinF *f;
    AlgMinDF *df;
};

static double f(const gsl_vector *v, void *vq) {
    T *q;
    q= (T*)vq;
    
    return 0.0;
}

static double df(const gsl_vector *v, void *param, gsl_vector *df) {
    return 0.0;
}

void fdf(const gsl_vector *x, void *params, double *f0, gsl_vector *df0) {
    *f0 = f(x, params);
    df(x, params, df0);
}

int alg_min_ini(int type, AlgMinF* f0, AlgMinDF* df0, void *param,
                int n, real *xx, real *yy, real *zz, /**/ T **pq) {
    T *q;
    gsl_multimin_function_fdf func;
    gsl_multimin_fdfminimizer_type *T;
    double tol, step_size;
    const gsl_vector *pos;
    
    T = gsl_multimin_fdfminimizer_steepest_descent;
    
    MALLOC(1, &q);
    MALLOC(3*n, &q->position);
    MALLOC(3*n, &q->force);    
    
    q->n = n;

    q->min = gsl_multimin_fdfminimizer_alloc(T, 3*n);
    
    func.f = f;
    func.df = df;
    func.fdf = fdf;
    func.params = q;

    gsl_multimin_fdfminimizer_set(q->min, &func, pos, step_size = 0.01, tol = 0.1);

    *pq = q;
    return HE_OK;
}

int alg_min_free(T *q) {
    gsl_multimin_fdfminimizer_free(q->min);
    FREE(q->position);
    FREE(q->force);
    FREE(q);
    return HE_OK;
}
