#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "Quad_Equ.h"

int main(void) {
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    printf("# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf("# Enter coefficients(a, b, c): ");
    scanf("%lg %lg %lg", &coeffs.a, &coeffs.b, &coeffs.c); // цикл, пока не вернет три норм значения
    // getcharami поройтись до \n eof.
    // printf("%lg %lg %lg", coeffs.a, coeffs.b, coeffs.c);
    assert(coeffs.a != NAN);
    assert(coeffs.b != NAN);
    assert(coeffs.c != NAN);
    struct quadr_roots roots;
    int n_solutions = QE_solver(coeffs, &roots);
    debug("sols: %d\n", n_solutions);
    switch (n_solutions)
    {
    case QE_NO_SOLUTIONS: 
        printf("quadratic equation hasn't solutions\n");
        break;
    case QE_ONE_SOLUTIONS: 
        printf("x = %lg\n");
        break;
    case QE_TWO_SOLUTIONS : 
        printf("x1 = %0.3lg, x2 = %lg\n");
        break;
    case QE_INF_SOLUTIONS: 
        printf("quadratic equation has infinity solutions\n");
        break;
    default:
        printf("quadratic equation has infinity solutions\n");
        break;
    }
}

// void QE_solver(double a, double b, double c, double* x1, double* x2);
