#include <stdio.h>
#include <real.h>

#include <alg/integration.h>

#define FMT CO_REAL_OUT

static real
f(real x, void *p)
{
	real alpha;
	alpha = *(real*)p;
	return alpha*x*x;
}

int
main(void)
{
	AlgIntegration *integ;
	real a, b, result, alpha;
	alg_integration_ini(GAUSS31, &integ);
	a = 0; 
	b = 1; 
	alpha = 0;
	alg_integration_apply(integ, a, b, f, &alpha, &result);
	printf(FMT "\n", result);
	alg_integration_fin(integ);
}
