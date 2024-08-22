#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <cerrno>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#include "quadr_equ.h"
#include "file_path.h"


// struct quadr_equ_obj QUADR_TESTS[] = 
// {
//     INIT_QUADR_EQU_OBJ(0, 0, 0, NAN, NAN, INF_SOLUTIONS),
//     INIT_QUADR_EQU_OBJ(0, 0, 1, NAN, NAN, NO_SOLUTIONS),
//     INIT_QUADR_EQU_OBJ(0, 1, 0, 0, NAN, ONE_SOLUTION),
//     INIT_QUADR_EQU_OBJ(0, 1, 1, -1, NAN, ONE_SOLUTION),
//     INIT_QUADR_EQU_OBJ(1, 0, 0, 0, NAN, ONE_SOLUTION),
//     INIT_QUADR_EQU_OBJ(1, 0, 1, NAN, NAN, NO_SOLUTIONS),
//     INIT_QUADR_EQU_OBJ(1, 1, 0, -1, 0, TWO_SOLUTIONS),
//     INIT_QUADR_EQU_OBJ(1, 1, 1, NAN, NAN, NO_SOLUTIONS),
//     INIT_QUADR_EQU_OBJ(0, DBL_MAX, DBL_MIN, 0, NAN, ONE_SOLUTION),
//     INIT_QUADR_EQU_OBJ(0, DBL_MIN, DBL_MAX, -INFINITY, NAN, ONE_SOLUTION),
// };


// // int quadr_equ_check_solver(const struct quadr_coeffs coeffs, struct quadr_coeffs *roots) {
// //     return 
// // }

// const size_t N_TESTS = ARR_SIZE(QUADR_TESTS);

// void quadr_equ_obj_filler(struct quadr_equ_obj QUADR_TESTS[]) {
//     for (size_t i = 0; i < N_TESTS; i++) {
//         QUADR_TESTS[i].n_roots = quadr_equ_solver(QUADR_TESTS[i].coeffs, &QUADR_TESTS[i].roots);
//     }
// }

bool cmp_eq(const double x1, const double x2) {
    if (fpclassify(x1) != fpclassify(x2)) {
        return false;
    }
    if (isnormal(x1) && isnormal(x2) && fabs(x1 - x2) > EPS) {
        return false;
    }
    return true;
}

bool cmp_eq_roots(const struct quadr_roots r1, const struct quadr_roots r2) {
    return cmp_eq(r1.x1, r2.x1) && cmp_eq(r1.x2, r2.x2);
}

void quadr_equ_solver_testing() {
    FILE *f_all_tests = fopen(PATH_ALL_TESTS, "r");
    if (f_all_tests == NULL) {
        fprintf(stderr, RED "error: %s [%s]\n" WHT, strerror(errno), PATH_ALL_TESTS);
        return;
    }
    size_t n_tests = 0;
    fscanf(f_all_tests, "%ld", &n_tests);
    struct quadr_equ_obj equation;
    printf("received: %d", fscanf_quadr_equ_obj(f_all_tests, &equation));
    fclose(f_all_tests); /// TODO: Проверить, нету ли открытого файла в каком нибудь пространстве памяти
    for (size_t i = 0; i < n_tests; i++) {
        struct quadr_roots roots;
        init_quadr_roots(&roots);

        int n_solutions = quadr_equ_solver(equation.coeffs, &roots);

        printf("coefs: %lg %lg %lg\n", equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);

        quadr_equ_print_solutions(equation.n_roots, equation.roots, 1);

        if (!cmp_eq_roots(roots, equation.roots) || 
                n_solutions != equation.n_roots) {
            printf("\nTEST %ld:" RED "WA" YEL "\n"
                   "a, b, c = %lg, %lg, %lg\n" WHT,
                   i, equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);
            printf(GRN "CORRECT ANSWER:\n");
            quadr_equ_print_solutions(equation.n_roots, equation.roots, true);
            printf(RED "WRONG ANSWER:\n");
            quadr_equ_print_solutions(n_solutions, roots, true);
            printf(WHT "\n\n");
        } else {
            printf("TEST %ld:" GRN "OK" WHT "\n", i);
        } 
    }
}
