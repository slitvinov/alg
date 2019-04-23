#include <stdio.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

#include <real.h>
#include <co/err.h>
#include <co/memory.h>
#include <co/macro.h>

#include "alg/root.h"

#define T AlgRoot

struct Param {
	void *param;
	real (*function)(real, void*);
};
typedef struct Param Param;
static double
G(double x, void *vp)
{
	Param *p;
	p = vp;
	return p->function(x, p->param);
}

struct T {
	gsl_root_fsolver *s;
};

int alg_root_ini(int type, T **pq)
{
	T *q;
	MALLOC(1, &q);

	*pq = q;
	return CO_OK;
}

int alg_root_fin(T *q)
{
	gsl_root_fsolver_free(q->s);
	FREE(q);
	return CO_OK;
}

int alg_root_apply(T *q, real lo, real hi, real (*f)(real, void*), void *p, real *result)
{
	return CO_OK;
}
