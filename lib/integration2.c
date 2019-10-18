#include <stdio.h>
#include <real.h>
#include <co/err.h>
#include <co/memory.h>
#include <co/macro.h>
#include "alg/integration.h"
#include "alg/integration2.h"

#define T AlgIntegration2
struct Param {
	void *param;
	real (*function)(real, void*);
};
typedef struct Param Param;
static double
G(double x, void *vp)
{
	Param *p;
}

struct T {
	int key;
};

int
alg_integration2_ini(int type, T **pq)
{
	T *q;
	MALLOC(1, &q);
	*pq = q;
	return CO_OK;
}

int
alg_integration2_fin(T *q)
{
	FREE(q);
	return CO_OK;
}

int
alg_integration2_apply(T *q, real u0, real u1,
		       real(*v0)(real u, void*), real(*v1)(real u, void*),
		       real(*f)(real u, real v, void*), void *p, /**/ real *res)
{
    return CO_OK;
}
