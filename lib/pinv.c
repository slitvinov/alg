#include <stdio.h>
#include <gsl/gsl_linalg.h>

#include <real.h>

#include <co/err.h>
#include <co/memory.h>

#include "alg/pinv.h"

#define T AlgPinv

typedef struct T T;
struct T {
    int dim;
    gsl_matrix *A, *V;
    gsl_vector *S, *WORK;
};

int alg_pinv_ini(int dim, T **pq) {
    T *q;
    MALLOC(1, &q);
    q->dim = dim;
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
    if ((q->WORK = gsl_vector_alloc(dim)) == NULL) {
        MSG("allocation failed for q->WORK");
        return 1;
    }

    *pq = q;
    return CO_OK;
}

int alg_pinv_fin(T *q) {
    gsl_matrix_free(q->A);
    gsl_matrix_free(q->V);
    gsl_vector_free(q->S);
    gsl_vector_free(q->WORK);
    FREE(q);
    return CO_OK;
}

int alg_pinv_apply(T *q, real *A0, /**/ real *B) {
    int i, j, m;
    int dim;
    gsl_matrix *A, *V;
    gsl_vector *S, *WORK;
    dim = q->dim;
    A = q->A;
    V = q->V;
    S = q->S;
    WORK = q->WORK;

    for (m = i = 0; i <  dim; i++)
        for (j = 0; j < dim; j++)
            gsl_matrix_set(A, i, j, A0[m++]);
    if (gsl_linalg_SV_decomp(A, V, S, WORK) != GSL_SUCCESS) {
        MSG("gsl_linalg_SV_decomp failed");
        return 1;
    }

    return CO_OK;
}
