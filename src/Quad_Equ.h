#ifndef QUAD_EQU_H
#define QUAD_EQU_H

#ifdef DEBUG
#define debug(f_, ...) printf(f_, __VA_ARGS__) // stderr,
#else
#define debug(f_, ...)
#endif

#ifdef TESTING
#define test 1
#else 
#define test 0
#endif

enum roots_num
{
    INF_SOLUTIONS = -1, 
    NO_SOLUTIONS  = 0,
    ONE_SOLUTION  = 1,
    TWO_SOLUTIONS  = 2,
};
static const int N_TESTS = 10;
const double EPS = 1e-6;
const int N_REPEATS = 5;

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

int quad_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots);
    
void init_quadr_coeffs(struct quadr_coeffs *const coeffs);

int scanf_coeffs(struct quadr_coeffs *coeffs);

struct quadr_coeffs make_coeffs(double a, double b, double c);

int tests();

#endif // QUAD_EQU_H
