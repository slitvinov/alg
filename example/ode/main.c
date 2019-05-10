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
int ode_apply(T*, real *time, real dt, real*);
#undef T

#define T Ode
struct T
{
	gsl_odeiv2_driver *d;
	void *param;
};

typedef struct Param Param;
struct Param
{
	void *param;
	double *y, *dy;
	int dim;
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

int
ode_ini(int type, int dim, real dt, int (*f)(real, const real*, real *dy, void*), void *param, T **pq)
{	
	T *q;
	int i, n;
	gsl_odeiv2_driver *d;
	gsl_odeiv2_system sys;
	const gsl_odeiv2_step_type *Stype[99];
	
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
	sys.function  = NULL;
	sys.jacobian = NULL;
	sys.dimension = dim;
	sys.params = NULL;	
	d = gsl_odeiv2_driver_alloc_y_new(&sys, Stype[i], dt, EPSABS, EPSREL);
	if (d == NULL)
		ERR(CO_MEMORY, "fail to allocate ode driver");	    	 
	q->d = d;
	*pq = q;
	return CO_OK;
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

