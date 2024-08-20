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
    double x1 = NAN, x2 = NAN;
    int solutions = QE_solver(coeffs, &x1, &x2);
    debug("sols: %d\n", solutions);
    switch (solutions)
    {
    case QE_No_Solutions: 
        printf("quadratic equation hasn't solutions\n");
        break;
    case QE_One_Solution: 
        printf("x = %lg\n");
        break;
    case QE_Two_Solutions: 
        printf("x1 = %0.3lg, x2 = %lg\n");
        break;
    case QE_Inf_Solutions: 
        printf("quadratic equation has infinity solutions\n");
        break;
    default:
        printf("quadratic equation has infinity solutions\n");
        break;
    }
}

// void QE_solver(double a, double b, double c, double* x1, double* x2);
