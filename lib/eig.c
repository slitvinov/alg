#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

#include <real.h>
#include <he/err.h>

#include "alg/eig.h"

static real get(const gsl_matrix *m, int i, int j) { return gsl_matrix_get(m, i, j); }

int alg_eig_vectors(const real A[6], /**/ real e0[3], real e1[3], real e2[3]) {
    enum {XX, XY, XZ, YY, YZ, ZZ};
    enum {YX = XY, ZX = XZ, ZY = YZ};
    enum {X, Y, Z};

    double B[3*3];
    gsl_matrix_view m;
    gsl_vector *eval;
    gsl_matrix *evec;
    gsl_eigen_symmv_workspace *w;
    int i;

    eval = gsl_vector_alloc(3);
    evec = gsl_matrix_alloc(3, 3);
    w = gsl_eigen_symmv_alloc(3);

    i = 0;
    B[i++] = A[XX]; B[i++] = A[XY]; B[i++] = A[XZ];
    B[i++] = A[YX]; B[i++] = A[YY]; B[i++] = A[YZ];
    B[i++] = A[ZX]; B[i++] = A[ZY]; B[i++] = A[ZZ];
    m = gsl_matrix_view_array(B, 3, 3);
    gsl_eigen_symmv (&m.matrix, eval, evec, w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);
    e0[X] = get(evec, X, X); e0[Y] = get(evec, Y, X); e0[Z] = get(evec, Z, X);
    e1[X] = get(evec, X, Y); e1[Y] = get(evec, Y, Y); e1[Z] = get(evec, Z, Y);
    e2[X] = get(evec, X, Z); e2[Y] = get(evec, Y, Z); e2[Z] = get(evec, Z, Z);

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    gsl_eigen_symmv_free(w);
    return HE_OK;
}
