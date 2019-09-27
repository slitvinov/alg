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
#include <alg/ode.h>

static int
f (__UNUSED real t, const real y[], real f[], void *params)
{
	real mu = *(real*)params;
	f[0] = y[1];
	f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
	return CO_OK;
}

int
main (void)
{
	real m = 10;
	Ode *ode;
	int i;
	real t = 0.0, t1 = 100.0, ti;
	real x[2] = {1.0, 0.0};

	ode_ini(RK2, 2, 1e-6, f, &m, &ode);
	for (i = 1; i <= 100; i++) {
		ti = i * t1 / 100.0;
		ode_apply(ode, &t, ti, x);
		printf ("%.5e %.5e %.5e\n", t, x[0], x[1]);
	}
	ode_fin(ode);
}
