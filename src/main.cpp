#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "quadr_equ.h"

int main(size_t argc, char *argv[]) {
    if (in_argv(TESING_ARG, argc, argv)) {
        quadr_equ_solver_testing();
        return 0;
    }
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    printf(YEL"# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf(WHT"# Enter coefficients(a, b, c): ");

    if (scanf_quadr_coeffs(&coeffs) == -1) {
        return EXIT_FAILURE;
    }

    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    assert(!isnan(coeffs.b));
    assert(!isnan(coeffs.b));
    assert(!isnan(coeffs.c));

    struct quadr_roots roots;
    init_quadr_roots(&roots);
    int n_solutions = quadr_equ_solver(coeffs, &roots);

    debug("sols: %d\n", n_solutions);
    assert(quadr_equ_print_solutions(n_solutions, roots, false) != -1);
}
