#include <stdio.h>
#include <gsl/gsl_multimin.h>

#include <real.h>
#include <he/err.h>
#include <he/memory.h>
#include <he/real.h>
#include <he/macro.h>

#include "alg/min.h"

#define T AlgMin

struct T {
    int n;
    gsl_multimin_fdfminimizer *min;
    gsl_vector *position;
    HeReal *real;

    AlgMinF *f;
    AlgMinDF *df;
    void *param;
};

static double f(const gsl_vector *v, void *vq) {
    int n;
    T *q;
    const real *position, *x, *y, *z;
    real E;
    q = (T*)vq;
    n = q->n;
    position = he_real_from(q->real, v->data);
    x = position; y = position + n; z = position + 2*n;
    (*q->f)(n, x, y, z, q->param, /**/ &E);
    return E;
}

static void df(const gsl_vector *v, void *vq, gsl_vector *df) {
    int n;
    T *q;
    const real *position, *x, *y, *z;
    real *force, *fx, *fy, *fz;
    q = (T*)vq;
    n = q->n;
    position = he_real_from(q->real, v->data);
    x = position; y = position + n; z = position + 2*n;

    force = he_real_from(q->real, df->data);
    fx = force; fy = force + n; fz = force + 2*n;
    
    (*q->df)(n, x, y, z, q->param, /**/ fx, fy, fz);
}

void fdf(const gsl_vector *x, void *params, double *f0, gsl_vector *df0) {
    *f0 = f(x, params);
    df(x, params, df0);
}

int alg_min_ini(int __UNUSED type, AlgMinF* f0, AlgMinDF* df0, void *param,
                int n, real *xx, real *yy, real *zz, /**/ T **pq) {
    T *q;
    gsl_multimin_function_fdf func;
    const gsl_multimin_fdfminimizer_type *T;
    double tol, step_size;
    int i, j;

    T = gsl_multimin_fdfminimizer_steepest_descent;

    MALLOC(1, &q);
    q->position = gsl_vector_alloc(3*n);
    he_real_ini(3*n, &q->real);

    q->n = n;
    q->f = f0;
    q->df = df0;
    q->param = param;

    q->min = gsl_multimin_fdfminimizer_alloc(T, 3*n);
    func.f = f;
    func.df = df;
    func.fdf = fdf;
    func.params = q;

    for (i = j = 0; i < n; i++) {
        gsl_vector_set(q->position, j++, xx[i]);
        gsl_vector_set(q->position, j++, yy[i]);
        gsl_vector_set(q->position, j++, zz[i]);
    }
    gsl_multimin_fdfminimizer_set(q->min, &func, q->position, step_size = 0.01, tol = 0.1);

    *pq = q;
    return HE_OK;
}

int alg_min_free(T *q) {
    gsl_multimin_fdfminimizer_free(q->min);
    gsl_vector_free(q->position);
    he_real_fin(q->real);
    FREE(q);
    return HE_OK;
}
