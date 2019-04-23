#include <stdio.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

#include <real.h>
#include <co/err.h>
#include <co/memory.h>
#include <co/macro.h>

#include "alg/root.h"

#define T AlgRoot

static int Type[] = {BISECTION, FALSEPOS, BRENT};
//static const gsl_root_fsolver_type (*const) SType[] = {gsl_root_fsolver_bisection} ; //, gsl_root_fsolver_falsepos, gsl_root_fsolver_brent};

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
	int n;
	gsl_root_fsolver *s;

	MALLOC(1, &q);

	s = gsl_root_fsolver_alloc(type);
	if (s == NULL)
		ERR(CO_MEMORY, "fail to allocate root");
	n = sizeof(Type)/sizeof(Type[0]);

	q->s = s;
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
