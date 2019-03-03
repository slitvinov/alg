#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <he/err.h>
#include <he/macro.h>

#include <alg/eig.h>

static const char **argv;
static int scl(/**/ real *p) {
    if (*argv == NULL) ER("not enough args");
    if (sscanf(*argv, XE_REAL_IN, p) != 1)
        ER("not a number '%s'", *argv);
    argv++;
    return CO_OK;
}

int main(__UNUSED int argc, const char **argv0) {
    enum {X, Y, Z};
    enum {XX, XY, XZ, YY, YZ, ZZ};
    int i;
    real m[6] = {1, 1/2.0, 1/3.0,
                 1/3.0, 1/4.0,
                 1/5.0};
    real v[3*3];

    argv = argv0;
    argv++;

    scl(&m[XX]); scl(&m[XY]); scl(&m[XZ]);
    scl(&m[YY]); scl(&m[YZ]);
    scl(&m[ZZ]);

    alg_eig_vectors(m, v);

    i = 0;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;
    return CO_OK;
}
