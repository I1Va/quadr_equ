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
#include "test_funcs.h"

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

int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots) {
    double a = coeffs.a, b = coeffs.b, c = coeffs.c;
    if (fabs(a) < EPS) { // a = 0
        if (fabs(b) < EPS) { // b = 0
            if (fabs(c) < EPS) { // c = 0
                roots->x1 = NAN;
                roots->x2 = NAN;
                return INF_SOLUTIONS;
            } else { // a, b = 0; c != 0
                roots->x1 = NAN;
                roots->x2 = NAN;
                return NO_SOLUTIONS;
            }
        } else { // a = 0, b != 0
            if (fabs(c) < EPS) { // c = 0
                roots->x1 = 0.0;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            } else { // c != 0
                roots->x1 = -c / b;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            }
        }
    } else { // a != 0
        if (fabs(b) < EPS) { // b = 0
            if (fabs(c) < EPS) { // c = 0;
                roots->x1 = 0.0;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            } else { // c != 0
                double k = -c / a;
                if (k < 0) {
                    roots->x1 = NAN;
                    roots->x2 = NAN;
                    return NO_SOLUTIONS;
                } else {
                    double sqrt_k = sqrt(k);
                    roots->x1 = -sqrt_k;
                    roots->x2 = sqrt_k;
                    return TWO_SOLUTIONS;
                }
            }
        } else { // b != 0
            if (fabs(c) < EPS) {
                roots->x1 = -b / a;
                roots->x2 = 0.0;
                return TWO_SOLUTIONS;
            } else { // c != 0
                double discr = b * b - 4 * a * c;
                if (fabs(discr) < EPS) {
                    roots->x1 = -b / (2 * a);
                    roots->x2 = NAN;
                    return ONE_SOLUTION;
                } else if (discr < 0) {
                    roots->x1 = NAN;
                    roots->x2 = NAN;
                    return NO_SOLUTIONS;
                } else { // discr > 0
                    double sqrt_discr = sqrt(discr);
                    roots->x1 = (-b - sqrt_discr) / (2 * a);
                    roots->x2 = (-b + sqrt_discr) / (2 * a);
                    return TWO_SOLUTIONS;
                }
            }

        }
    }
}

void get_tests_from_file(const char path[], quadr_equ_obj test_data[]) {
    FILE* f_test_data_read = fopen(path, "r");
    if (f_test_data_read == NULL) {
        fprintf(stderr, "Failed to open %s", path);
        return;
    }
    size_t n_tests = 0;
    fscanf(f_test_data_read, "%ld", &n_tests);
    for (size_t i = 0; i < n_tests; i++) {
        fscanf_quadr_equ_obj(f_test_data_read, &test_data[i]);
    }
    fclose(f_test_data_read);
}

void generate_tests_to_file(const char path[], const size_t n_tests) {
    FILE* f_test_data_write = fopen(path, "w");
    if (f_test_data_write == NULL) {
        fprintf(stderr, "Failed to open %s", path);
        return;
    }
    fprintf(f_test_data_write, "%ld\n", n_tests);
    for (size_t i = 0; i < n_tests; i++) {
        struct quadr_coeffs coeffs = INIT_QUADR_COEFFS( \
        my_frand() * ((double) (my_rand() % 100)), \
        my_frand() * ((double) (my_rand() % 100)), \
        my_frand() * ((double) (my_rand() % 100)));

        struct quadr_roots roots;
        int n_roots = simple_quadr_solve(coeffs, &roots);
        
        
        fprintf(f_test_data_write, "%lg %lg %lg %lg %lg %d", \
            coeffs.a, coeffs.b, coeffs.c, roots.x1, roots.x2, n_roots);
    }
    fclose(f_test_data_write);
    
}

// void quadr_equ_solver_testing() {
//     FILE *f_all_tests = fopen(PATH_ALL_TESTS, "r");
//     if (f_all_tests == NULL) {
//         fprintf(stderr, RED "error: %s [%s]\n" WHT, strerror(errno), PATH_ALL_TESTS);
//         return;
//     }
//     size_t n_tests = 0;
//     fscanf(f_all_tests, "%ld", &n_tests);
//     struct quadr_equ_obj equation;
//     fscanf_quadr_equ_obj(f_all_tests, &equation);
//     fclose(f_all_tests); /// TODO: Проверить, нету ли открытого файла в каком нибудь пространстве памяти
//     for (size_t i = 0; i < n_tests; i++) {
//         struct quadr_roots roots;
//         init_quadr_roots(&roots);

//         int n_solutions = quadr_equ_solver(equation.coeffs, &roots);

//         printf("coefs: %lg %lg %lg\n", equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);

//         quadr_equ_print_solutions(equation.n_roots, equation.roots, 1);

//         if (!cmp_eq_roots(roots, equation.roots) || 
//                 n_solutions != equation.n_roots) {
//             printf("\nTEST %ld:" RED "WA" YEL "\n"
//                    "a, b, c = %lg, %lg, %lg\n" WHT,
//                    i, equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);
//             printf(GRN "CORRECT ANSWER:\n");
//             quadr_equ_print_solutions(equation.n_roots, equation.roots, true);
//             printf(RED "WRONG ANSWER:\n");
//             quadr_equ_print_solutions(n_solutions, roots, true);
//             printf(WHT "\n\n");
//         } else {
//             printf("TEST %ld:" GRN "OK" WHT "\n", i);
//         } 
//     }
// }
