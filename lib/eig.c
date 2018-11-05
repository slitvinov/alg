#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

#include <real.h>
#include <he/err.h>

#include "alg/eig.h"

#define NDIM (3)

int alg_eig_vectors(const real *data, /**/ real e0[3], real e1[3], real e2[3]) {
    double data_[NDIM*NDIM];
    for (int i = 0; i < NDIM*NDIM; i++)
        data_[i] = data[i];
  
    gsl_matrix_view m
        = gsl_matrix_view_array (data_, NDIM, NDIM);
    gsl_vector *eval = gsl_vector_alloc (NDIM);
    gsl_matrix *evec = gsl_matrix_alloc (NDIM, NDIM);
    gsl_eigen_symmv_workspace * w =
        gsl_eigen_symmv_alloc (NDIM);
    gsl_eigen_symmv (&m.matrix, eval, evec, w);
    gsl_eigen_symmv_free (w);
    gsl_eigen_symmv_sort (eval, evec,
                          GSL_EIGEN_SORT_ABS_ASC);

    e0[0] = gsl_matrix_get(evec, 0, 0); e0[1] = gsl_matrix_get(evec, 1, 0); e0[2] = gsl_matrix_get(evec, 2, 0);
    e1[0] = gsl_matrix_get(evec, 0, 1); e1[1] = gsl_matrix_get(evec, 1, 1); e1[2] = gsl_matrix_get(evec, 2, 1);
    e2[0] = gsl_matrix_get(evec, 0, 2); e2[1] = gsl_matrix_get(evec, 1, 2); e2[2] = gsl_matrix_get(evec, 2, 2);
    gsl_vector_free (eval);
    gsl_matrix_free (evec);
    
    return HE_OK;
}
