#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

#include <real.h>
#include <he/err.h>

#include "alg/eig.h"

#define D (3)

static real get(const gsl_matrix *m, int i, int j) { return gsl_matrix_get(m, i, j); }

int alg_eig_vectors(const real *data, /**/ real e0[3], real e1[3], real e2[3]) {
    enum {X, Y, Z};
    double data_[D*D];

    for (int i = 0; i < D*D; i++)
        data_[i] = data[i];

    gsl_matrix_view m
        = gsl_matrix_view_array (data_, D, D);
    gsl_vector *eval = gsl_vector_alloc (D);
    gsl_matrix *evec = gsl_matrix_alloc (D, D);
    gsl_eigen_symmv_workspace * w =
        gsl_eigen_symmv_alloc (D);
    gsl_eigen_symmv (&m.matrix, eval, evec, w);
    gsl_eigen_symmv_free (w);
    gsl_eigen_symmv_sort (eval, evec,
                          GSL_EIGEN_SORT_ABS_ASC);

    e0[X] = get(evec, X, X); e0[Y] = get(evec, Y, X); e0[Z] = get(evec, Z, X);
    e1[X] = get(evec, X, Y); e1[Y] = get(evec, Y, Y); e1[Z] = get(evec, Z, Y);
    e2[X] = get(evec, X, Z); e2[Y] = get(evec, Y, Z); e2[Z] = get(evec, Z, Z);
    gsl_vector_free (eval);
    gsl_matrix_free (evec);

    return HE_OK;
}
