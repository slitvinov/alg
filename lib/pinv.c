#include <stdio.h>

#include <real.h>
#include <co/err.h>
#include <co/memory.h>

#include "alg/pinv.h"

#define T AlgPinv

typedef struct T T;
struct T {
};

int alg_pinv_ini(int dim, T **pq) {
    T *q;
    MALLOC(1, &q);
    *pq = q;
    return CO_OK;
}

int alg_pinv_fin(T *q) {
    FREE(q);
    return CO_OK;
}

int alg_pinv_apply(T *q, real *A, /**/ real *B) {
    return CO_OK;
}
