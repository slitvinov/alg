#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include <real.h>
#include <co/err.h>
#include <co/memory.h>
#include <co/macro.h>
#include "alg/ode.h"

static const real EPSABS =  1e-8;
static const real EPSREL = 1e-8;

#define T Ode
typedef struct Param Param;
struct Param
{
	void *params;
	real *x, *g;
	int dim;
	int (*f)(real, const real*, real *dy, void*);
};
struct T
{
	gsl_odeiv2_driver *d;
	gsl_odeiv2_system sys;
	double *y;
	Param params;
};

static int Type[] =
{
	RK2, RK4, RKF45, RKCK, RK8PD
};
#define FILL \
	do { \
		i = 0; \
		Stype[i++] = gsl_odeiv2_step_rk2; \
		Stype[i++] = gsl_odeiv2_step_rk4; \
		Stype[i++] = gsl_odeiv2_step_rkf45; \
		Stype[i++] = gsl_odeiv2_step_rk8pd; \
	} while(0);

static int
F(double t, const double y[], double f[], void *p0)
{
	Param *p;
	real *x, *g;
	void *params;
	int i, status, dim;
	//return GSL_SUCCESS;

	p = p0;
	x = p->x;
	g = p->g;
	dim = p->dim;
	params = p->params;
	for (i = 0; i < dim; i++)
		x[i] = y[i];
	status = p->f(t, x, g, params);
	for (i = 0; i < dim; i++)
		f[i] = g[i];
	if (status == CO_OK)
		return GSL_SUCCESS;
	else
		return GSL_EINVAL;
}

int
ode_ini(int type, int dim, real dt, int (*f)(real, const real*, real *f, void*), void *param, T **pq)
{
	T *q;
	int i, n;
	gsl_odeiv2_driver *d;
	gsl_odeiv2_system *sys;
	const gsl_odeiv2_step_type *Stype[99];
	Param *p;

	FILL;
	MALLOC(1, &q);
	n = sizeof(Type)/sizeof(Type[0]);
	i = 0;
	while (1) {
		if (i == n)
			ERR(CO_INDEX, "unknown type %d", type);
		if (Type[i] == type)
			break;
		i++;
	}
	MALLOC(dim, &q->y);
	sys = &q->sys;
	p = &q->params;
	MALLOC(dim, &p->x);
	MALLOC(dim, &p->g);
	p->dim = dim;
	p->f = f;
	p->params = param;
	sys->function  = F;
	sys->jacobian = NULL;
	sys->dimension = dim;
	sys->params = p;
	d = gsl_odeiv2_driver_alloc_y_new(sys, Stype[i], dt, EPSABS, EPSREL);
	if (d == NULL)
		ERR(CO_MEMORY, "fail to allocate ode driver");
	q->d = d;
	*pq = q;
	return CO_OK;
}

int
ode_fin(T *q)
{
	gsl_odeiv2_driver_free(q->d);
	FREE(q->y);
	FREE(q->params.x);
	FREE(q->params.g);
	FREE(q);
	return CO_OK;
}

int
ode_apply(T *q, real *ptime, real t, real *x)
{
	int status;
	double time, *y;
	int dim, i;

	y = q->y;
	dim = q->params.dim;
	time = *ptime;
	for (i = 0; i < dim; i++)
		y[i] = x[i];
	status = gsl_odeiv2_driver_apply(q->d, &time, t, y);
	for (i = 0; i < dim; i++)
		x[i] = y[i];
	*ptime = time;
	return status == GSL_SUCCESS ? CO_OK : CO_NUM;
}