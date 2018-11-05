#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <he/err.h>
#include <he/macro.h>

#include <alg/eig.h>

int main(void) {
    enum {X, Y, Z};
    int i;
    real m[6] = {1, 1/2.0, 1/3.0,
                 1/3.0, 1/4.0,
                 1/5.0};
    real v[3*3];
    alg_eig_vectors(m, v);

    i = 0;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;
    printf("%g %g %g\n", v[i+X], v[i+Y], v[i+Z]); i += 3;    
}
