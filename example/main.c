#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <real.h>
#include <he/err.h>
#include <he/macro.h>
#include <alg/min.h>

#define N (5)
static real xx[N], yy[N], zz[N];
static AlgMin *min;

real sq(real x) { return x*x; }
real f(int n, const real *xx, const real *yy, const real *zz,
       void __UNUSED *param) {
    int i;
    real s;
    s = 0;
    for (i = 0; i < n; i++)
        s += sq(xx[i]) + sq(yy[i]) + sq(zz[i]);
    return s;
}

void df(int n,
        const real *xx, const real *yy, const real *zz,
        void __UNUSED *param,
        real *fx, real *fy, real *fz) {
    int i;
    for (i = 0; i < n; i++) {
        fx[i] = 2*xx[i];
        fy[i] = 2*yy[i];
        fz[i] = 2*zz[i];
    }
}

int main(void) {
    int i;
    for (i = 0; i < N; i++)
        xx[i] = yy[i] = zz[i] = 1.0;

    alg_min_ini(STEEPEST_DESCENT, f, df,
                NULL, N, xx, yy, zz, &min);
    alg_min_fin(min);
    return 0;
}
