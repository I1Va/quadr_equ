#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "quad_equ.h"

int main(void) {
#ifdef TESTING
    quad_equ_solver_testing();
#endif
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    // printf("\e[0;32m");
    // printf("\e[0;37m");
    printf("# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf("# Enter coefficients(a, b, c): ");
    if (scanf_coeffs(&coeffs)) {
        return EXIT_FAILURE;
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
