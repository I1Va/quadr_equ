#ifndef QUAD_EQU_H
#define QUAD_EQU_H

#ifdef DEBUG
#define debug(f_, ...) fprintf(stderr, (f_), __VA_ARGS__)
#else
#define debug(f_, ...)
#endif

static const int QE_Inf_Solutions = -1;
static const int QE_No_Solutions = 0;
static const int QE_One_Solution = 1;
static const int QE_Two_Solutions = 2;

struct quadr_coeffs
{
    double a;
    double b;
    double c;
};

int QE_solver(const struct quadr_coeffs, double *const x1, double *const x2);
    
void init_quadr_coeffs(struct quadr_coeffs *constcoeffs);

#endif // QUAD_EQU_H
