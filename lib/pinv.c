#include <stdio.h>
#include <gsl/gsl_linalg.h>

#include <real.h>

#include <co/err.h>
#include <co/memory.h>

#include "alg/pinv.h"

#define T AlgPinv

typedef struct T T;
struct T {
    gsl_matrix *A, *V;
    gsl_vector *S, *work;
};

int alg_pinv_ini(int dim, T **pq) {
    T *q;
    MALLOC(1, &q);

    if ((q->A = gsl_matrix_alloc(dim, dim)) == NULL) {
        MSG("allocation failed for q->A");
        return 1;
    }
    if ((q->V = gsl_matrix_alloc(dim, dim)) == NULL) {
        MSG("allocation failed for q->V");
        return 1;
    }
    if ((q->S = gsl_vector_alloc(dim)) == NULL) {
        MSG("allocation failed for q->S");
        return 1;
    }
    if ((q->work = gsl_vector_alloc(dim)) == NULL) {
        MSG("allocation failed for q->work");
        return 1;
    }

    *pq = q;
    return CO_OK;
}

int alg_pinv_fin(T *q) {
    gsl_matrix_free(q->A);
    gsl_matrix_free(q->V);
    gsl_vector_free(q->S);
    gsl_vector_free(q->work);
    FREE(q);
    return CO_OK;
}

int alg_pinv_apply(T *q, real *A, /**/ real *B) {

    return CO_OK;
}
