#define T AlgIntegration
typedef struct T T;

enum { QNG, QAGS, GAUSS15, GAUSS21, GAUSS31, GAUSS61 };
int alg_integration_ini(int, T **);
int alg_integration_fin(T *);
int alg_integration_apply(T *, real, real, real(*)(real, void *), void *,
                          /**/ real *);

#undef T
