#define T Ode
typedef struct T T;
enum
{
	RK2, RK4, RKF45, RKCK, RK8PD
};
int ode_ini(int type, int dim, real dt, int (*)(real, const real*, real *dy, void*), void*, T**);
int ode_fin(T*);
int ode_apply(T*, real *time, real t, real*);
#undef T