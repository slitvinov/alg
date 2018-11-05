#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <he/err.h>
#include <he/macro.h>

#include <alg/eig.h>

int main(void) {
    enum {X, Y, Z};
    real m[6] = {1, 1/2.0, 1/3.0,
                 1/3.0, 1/4.0,
                 1/5.0};
    real a[3], b[3], c[3];
    alg_eig_vectors(m, a, b, c);
    printf("%g %g %g\n", a[X], a[Y], a[Z]);
    printf("%g %g %g\n", b[X], b[Y], b[Z]);
    printf("%g %g %g\n", c[X], c[Y], c[Z]);
}
