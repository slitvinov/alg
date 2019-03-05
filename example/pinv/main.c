#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <co/err.h>
#include <co/macro.h>

#include <alg/pinv.h>

int main(__UNUSED int argc, const char **argv) {
    AlgPinv *pinv;
    real A[99], B[99];

    int dim = 1;

    alg_pinv_ini(dim, &pinv);
    alg_pinv_apply(pinv, A, /**/ B);
    alg_pinv_fin(pinv);
}
