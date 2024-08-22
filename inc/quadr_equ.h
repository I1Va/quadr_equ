#ifndef QUADR_EQU_H
#define QUADR_EQU_H

#include <stdint.h>

#ifdef _DEBUG
#define debug(f_, ...) fprintf(stderr, f_, __VA_ARGS__) // stderr,
#else
#define debug(f_, ...)
#endif // _DEBUG

#define GRN "\e[0;32m"
#define WHT "\e[0;37m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

enum roots_num
{
    INF_SOLUTIONS = -1, 
    NO_SOLUTIONS  = 0,
    ONE_SOLUTION  = 1,
    TWO_SOLUTIONS = 2,
};

static const double EPS = 1e-6;
static const size_t N_ATTEMPTS = 5;
static const char TESING_ARG[] = "-testing";

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

int quadr_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots);
    
void init_quadr_coeffs(struct quadr_coeffs *const coeffs);

void init_quadr_roots(struct quadr_roots *const roots);

int scanf_quadr_coeffs(struct quadr_coeffs *coeffs);

void quadr_equ_solver_testing();

int quadr_equ_print_solutions(const int n_solutions, const struct quadr_roots, const bool show_roots);

bool cmp_eq(const double x1, const double x2);

bool cmp_strs(const char s1[], const char s2[]);

bool cmp_eq_roots(const struct quadr_roots r1, const struct quadr_roots r2);

bool in_argv(const char samp[], const size_t argc, char *argv[]);

#endif // QUADR_EQU_H
