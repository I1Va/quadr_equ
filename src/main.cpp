#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "Quad_Equ.h"
#include "quad_equ_tests.cpp"


int main(void) {
    // printf("printf: %d", printf("\n"));
    if (test) {
        for (int i = 0; i < N_TESTS; i++) {
            struct quadr_roots temp_roots;
            quad_equ_solver(QE_TESTS[i], &temp_roots);
            printf("TEST %d:OK\n", i);
        }
        return 0;
    }
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    printf("# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf("# Enter coefficients(a, b, c): ");
    if (scanf_coeffs(&coeffs)) {
        for (int i = 0; i < N_TESTS; i++) {

        }
        return 0;
    }
    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    // getcharami поройтись до \n eof.
    // printf("%lg %lg %lg", coeffs.a, coeffs.b, coeffs.c);
    assert(coeffs.a != NAN);
    assert(coeffs.b != NAN);
    assert(coeffs.c != NAN);
    struct quadr_roots roots;
    int n_solutions = quad_equ_solver(coeffs, &roots);
    debug("sols: %d\n", n_solutions);
    switch (n_solutions)
    {
    case NO_SOLUTIONS: 
        printf("quadratic equation hasn't solutions\n");
        break;
    case ONE_SOLUTION: 
        printf("x = %lg\n", roots.x1);
        break;
    case TWO_SOLUTIONS : 
        printf("x1 = %0.3lg, x2 = %lg\n", roots.x1, roots.x2);
        break;
    case INF_SOLUTIONS: 
        printf("quadratic equation has infinity solutions\n");
        break;
    default:
        printf("quadratic equation has infinity solutions\n");
        break;
    }
}
