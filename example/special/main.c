#include <stdio.h>
#include <real.h>

#include <alg/special.h>

#define FMT CO_REAL_OUT

int
main(void)
{
	real x;
	int n;

	n = 3;
	x = 0.1;
	printf(FMT "\n", alg_special_bessel_Jn(3, 0.1));
}