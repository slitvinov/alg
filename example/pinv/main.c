#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <co/err.h>
#include <co/macro.h>

#include <alg/pinv.h>

#define FMT CO_REAL_OUT

int main(__UNUSED int argc, const char **argv) {
    AlgPinv *pinv;
    real A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    real B[99];
    int dim, i, j, m;

    dim = 3;
    alg_pinv_ini(dim, &pinv);
    alg_pinv_apply(pinv, A, /**/ B);

    for (i = m = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            if (j > 0) printf(" ");
            printf(FMT, A[m++]);
        }
        printf("\n");
    }

    alg_pinv_fin(pinv);
}
