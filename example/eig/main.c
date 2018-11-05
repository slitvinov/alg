#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <he/err.h>
#include <he/macro.h>

#include <alg/eig.h>

int main(void) {
    real m[9];
    real e0[3], e1[3], e2[3];
    alg_eig_vectors(m, e0, e1, e2);
}
