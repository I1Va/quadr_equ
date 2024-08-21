#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "quadr_equ.h"

#define INIT_QUADR_COEFFS(a_, b_, c_) {.a = a_, .b = b_, .c = c_}
#define INIT_QUADR_ROOTS(x1_, x2_) {.x1 = x1_, .x2 = x2_}
#define INIT_QUADR_EQU_OBJ(a_, b_, c_, x1_, x2_, n_roots_) \
    {.coeffs = INIT_QUADR_COEFFS(a_, b_, c_), \
    .roots = INIT_QUADR_ROOTS(x1_, x2_), \
    .n_roots = n_roots_}

struct quadr_equ_obj
{
    struct quadr_coeffs coeffs;
    struct quadr_roots roots;
    int n_roots;
};


static struct quadr_equ_obj QUADR_TESTS[] = 
{
    INIT_QUADR_EQU_OBJ(0, 0, 0, NAN, NAN, INF_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, 0, 1, NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, 1, 0, 0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(0, 1, 1, -1, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1, 0, 0, 0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1, 0, 1, NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1, 1, 0, -1, 0, TWO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1, 1, 1, NAN, NAN, NO_SOLUTIONS),
    // INIT_QUADR_EQU_OBJ(-12.52, 924.242, 1232.22),
    // INIT_QUADR_EQU_OBJ(0, 1e100, 1e-100),
    // INIT_QUADR_EQU_OBJ(0, 1e-100, 1e100),
};


// int quadr_equ_check_solver(const struct quadr_coeffs coeffs, struct quadr_coeffs *roots) {
//     return 
// }

const size_t N_TESTS = ARR_SIZE(QUADR_TESTS);

// void quadr_equ_obj_filler(struct quadr_equ_obj QUADR_TESTS[]) {
//     for (size_t i = 0; i < N_TESTS; i++) {
//         QUADR_TESTS[i].n_roots = quadr_equ_solver(QUADR_TESTS[i].coeffs, &QUADR_TESTS[i].roots);
//     }
// }

int eq_x(const double x1, const double x2) {
    if (isnan(x1) && isnan(x2)) {
        return 1;
    }
    else if (isnan(x1) && !isnan(x2)) {
        return 0;
    }
    else if (!isnan(x1) && isnan(x2)) {
        return 0;
    }
    else if (fabs(x1 - x2) > EPS) {
        return 0;
    } else {
        return 1;
    }
}

int eq_roots(const struct quadr_roots r1, const struct quadr_roots r2) {
    return eq_x(r1.x1, r2.x1) && eq_x(r1.x2, r2.x2);
}

void quadr_equ_solver_testing() {
    for (size_t i = 0; i < N_TESTS; i++) {
        struct quadr_roots roots;
        init_quadr_roots(&roots);
        int n_solutions = quadr_equ_solver(QUADR_TESTS[i].coeffs, &roots);

        if (!eq_roots(roots, QUADR_TESTS[i].roots) || 
                n_solutions != QUADR_TESTS[i].n_roots) {
            printf("\nTEST %d:" RED "WA" YEL "\na, b, c = %lg, %lg, %lg\n" WHT,
            i, QUADR_TESTS[i].coeffs.a, QUADR_TESTS[i].coeffs.b, QUADR_TESTS[i].coeffs.c);
            printf(GRN "CORRECT ANSWER:\n");
            quadr_equ_print_solutions(QUADR_TESTS[i].n_roots, QUADR_TESTS[i].roots, 1);
            printf(RED "WRONG ANSWER:\n");
            quadr_equ_print_solutions(n_solutions, roots, 1);
            printf(WHT "\n\n");
        } else {
            printf("TEST %d:" GRN "OK" WHT "\n", i);
        } 
    }
}
