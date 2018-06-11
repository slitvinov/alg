#include <real.h>
#include <he/err.h>

#include "alg/min.h"

#define T AlgMin

struct T {
    real *pos;
    real *xx, *yy, *zz;
};

int alg_min_ini(int type, AlgMinF* f, AlgMinDF* df, int n, /**/ T **pq) {
    return HE_OK;
}
