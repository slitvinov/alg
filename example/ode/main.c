#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include <real.h>
#include <co/err.h>
#include <co/memory.h>
#include <co/macro.h>

static const real EPSABS =  1e-8;
static const real EPSREL = 1e-8;
#define T Ode
typedef struct Ode Ode;
enum
{
	RK2, RK4, RKF45, RKCK, RK8PD
};
int ode_ini(int type, int dim, real dt, int (*)(real, const real*, real *dy, void*), void*, T**);
int ode_fin(T*);
int ode_apply(T*, real *time, real t, real*);
#undef T

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
	gsl_odeiv2_system sys;
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
	p = &q->params;
	MALLOC(dim, &p->x);
	MALLOC(dim, &p->g);
	p->dim = dim;
	p->f = f;
	p->params = param;
	sys.function  = F;
	sys.jacobian = NULL;
	sys.dimension = dim;
	sys.params = p;
	d = gsl_odeiv2_driver_alloc_y_new(&sys, Stype[i], dt, EPSABS, EPSREL);
	if (d == NULL)
		ERR(CO_MEMORY, "fail to allocate ode driver");	    	 
	q->d = d;
	*pq = q;
	return CO_OK;
}

int
ode_fin(T *q)
{
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

int
func (__UNUSED double t, const double y[], double f[],
void *params)
{
	double mu = *(double *)params;
	f[0] = y[1];
	f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
	return GSL_SUCCESS;
}

int
main (void)
{
	double mu = 10;
	gsl_odeiv2_system sys = {
		func, NULL, 2, &mu
	};

	gsl_odeiv2_driver * d =
	    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
	    1e-6, 1e-6, 0.0);
	int i;
	double t = 0.0, t1 = 100.0;
	double y[2] = {
		1.0, 0.0 	};

	for (i = 1; i <= 100; i++)
	{
		double ti = i * t1 / 100.0;
		int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

		if (status != GSL_SUCCESS)
		{
			printf ("error, return value=%d\n", status);
			break;
		}

		printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
	}

	gsl_odeiv2_driver_free (d);
	return 0;
}

