#include <stdio.h>
#include <real.h>

#include <co/err.h>
#include <alg/integration.h>

#define FMT CO_REAL_OUT

static real
f(real x, void *p)
{
    real alpha;

    alpha = *(real *) p;
    return alpha * x * x;
}

int
main(int argc, char **argv)
{
    int type, status;
    AlgIntegration *integ;
    real a, b, result, alpha;

    argv++;
    if (argv[0] == NULL)
	ER("needs an argment");
    status = alg_integration_str2enum(argv[0], &type);
    if (status != CO_OK)
	ER("alg_integration_str2enum failed");
    alg_integration_ini(QAGS, &integ);
    a = 0;
    b = 1;
    alpha = 10;
    alg_integration_apply(integ, a, b, f, &alpha, &result);
    printf(FMT "\n", result);
    alg_integration_fin(integ);
}
