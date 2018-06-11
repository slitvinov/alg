#include <stdio.h>

#include <real.h>
#include <he/err.h>
#include <he/memory.h>

#include "alg/min.h"

#define T AlgMin

struct T {
    real *pos;
    real *xx, *yy, *zz;
};

int alg_min_ini(int type, AlgMinF* f, AlgMinDF* df, int n, /**/ T **pq) {
    T *q;
    MALLOC(1, &q);

    *pq = q;
    return HE_OK;
}

int alg_min_free(T *q) { FREE(q); return HE_OK; }
