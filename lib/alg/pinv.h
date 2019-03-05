#define T AlgPinv

typedef struct T T;

int alg_pinv_ini(int dim, T**);
int alg_pinv_fin(T*);

#undef T
