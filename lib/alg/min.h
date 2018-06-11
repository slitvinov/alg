#define T AlgMin

typedef struct T T;

/* enum {CONJUGATE_FR, CONJUGATE_PR, VECTOR_BFGS2, VECTOR_BFGS, STEEPEST_DESCENT}; */
enum {STEEPEST_DESCENT};

typedef int (*AlgMinF )(int n, real *xx, real *yy, real *zz, void *param, /**/ real *E);
typedef int (*AlgMinDF)(int n, real *xx, real *yy, real *zz, void *param, /**/ real *fx, real *fy, real *fz);

int alg_min_ini(int type, AlgMinF*, AlgMinDF*, int n, void *param, /**/ T**);
int alg_min_fin(T*);

int alg_min_iterate(T*);

int  alg_min_force   (T*, /**/ real**, real**, real**);
int  alg_min_position(T*, /**/ real**, real**, real**);
real alg_min_energy(T*);

int alg_min_test_force(T*, real eps);

#undef T
