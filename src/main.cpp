#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "quadr_equ.h"

int main() {
#ifdef TESTING 
    quadr_equ_solver_testing();
#else 
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    printf("# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf("# Enter coefficients(a, b, c): ");
    if (scanf_quadr_coeffs(&coeffs) == -1) {
        return EXIT_FAILURE;
    }
    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    assert(coeffs.a != NAN);
    assert(coeffs.b != NAN);
    assert(coeffs.c != NAN);
    struct quadr_roots roots;
    init_quadr_roots(&roots);
    int n_solutions = quadr_equ_solver(coeffs, &roots);
    debug("sols: %d\n", n_solutions);
    assert(quadr_equ_print_solutions(n_solutions, roots, 0) != -1);
#endif // TESTING
}

