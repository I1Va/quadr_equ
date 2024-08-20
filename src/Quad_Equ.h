#ifndef QUAD_EQU_H
#define QUAD_EQU_H

#ifdef DEBUG
#define debug(f_, ...) fprintf(stderr, (f_), __VA_ARGS__)
#else
#define debug(f_, ...)
#endif

enum roots_num
{
    INF_SOLUTIONS = -1, 
    NO_SOLUTIONS  = 0,
    ONE_SOLUTIONS  = 1,
    TWO_SOLUTIONS  = 2,
};

struct quadr_coeffs
{
    double a;
    double b;
    double c;
};

struct quadr_roots
{
    double x1;
    double x2;
};

int QE_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots);
    
void init_quadr_coeffs(struct quadr_coeffs *const coeffs);

#endif // QUAD_EQU_H
