#include <stdio.h>
#include "quad_equ.h"

#define INIT_QUAD_COEFFS(a_, b_, c_) {.a = a_, .b = b_, .c = c_}

static struct quadr_coeffs QE_TESTS[] = 
{
    INIT_QUAD_COEFFS(0, 0, 0),
    INIT_QUAD_COEFFS(0, 0, 1),
    INIT_QUAD_COEFFS(0, 1, 0),
    INIT_QUAD_COEFFS(0, 1, 1),
    INIT_QUAD_COEFFS(1, 0, 0),
    INIT_QUAD_COEFFS(1, 0, 1),
    INIT_QUAD_COEFFS(1, 1, 0),
    INIT_QUAD_COEFFS(1, 1, 1),
    INIT_QUAD_COEFFS(0, 1e100, 1e-100),
    INIT_QUAD_COEFFS(0, 1e-100, 1e100),
    INIT_QUAD_COEFFS(142879.123, 12.434, 1232.222),
};

const size_t N_TESTS = ARR_SIZE(QE_TESTS);

void quad_equ_solver_testing() {
    for (size_t i = 0; i < N_TESTS; i++) {
        struct quadr_roots roots;
        quad_equ_solver(QE_TESTS[i], &roots);
        printf("TEST %d:OK\n", i);
    }
}