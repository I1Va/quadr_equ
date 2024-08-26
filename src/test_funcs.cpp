#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <cerrno>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "quadr_equ.h"
#include "quadr_config.h"
#include "colors.h"
#include "test_funcs.h"

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

size_t get_tests_from_file(const char path[], quadr_equ_obj test_data[]) {
    FILE* f_test_data_read = fopen(path, "r");
    if (f_test_data_read == NULL) {
        fprintf(stderr, "Failed to open %s", path);
        return 0;
    }

    size_t n_tests = 0;
    fscanf(f_test_data_read, "%ld", &n_tests);
    for (size_t i = 0; i < n_tests; i++) {
        fscanf_quadr_equ_obj(f_test_data_read, &test_data[i]);
    }
    fclose(f_test_data_read);

    return n_tests;
}

int generate_tests_to_file(const char path[], const size_t n_tests) {
    FILE* f_test_data_write = fopen(path, "w");
    if (f_test_data_write == NULL) {
        fprintf(stderr, "Failed to open %s", path);
        return EXIT_FAILURE;
    }
    fprintf(f_test_data_write, "%ld\n", n_tests);

    for (size_t i = 0; i < n_tests; i++) {
        struct quadr_coeffs coeffs = INIT_QUADR_COEFFS( \
        cong_frand() * ((double) (cong_rand() % 100)), \
        cong_frand() * ((double) (cong_rand() % 100)), \
        cong_frand() * ((double) (cong_rand() % 100)));

        struct quadr_roots roots;
        int n_roots = simple_quadr_solve(coeffs, &roots);
        
        fprintf(f_test_data_write, "%lg %lg %lg %lg %lg %d\n", \
            coeffs.a, coeffs.b, coeffs.c, roots.x1, roots.x2, n_roots);
    }
    fclose(f_test_data_write);

    return EXIT_SUCCESS;
}

int quadr_equ_solver_file_testing(const char path[]) {
    struct quadr_equ_obj test_data[MAX_N_TESTS];
    size_t n_tests = get_tests_from_file(path, test_data);

    for (size_t i = 0; i < n_tests; i++) {
        struct quadr_equ_obj equation = test_data[i];
        struct quadr_roots roots;
        init_quadr_roots(&roots);

        int n_solutions = quadr_equ_solver(equation.coeffs, &roots);

        printf("coefs: %lg %lg %lg\n", equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);
        if (!cmp_eq_roots(roots, equation.roots) || 
                n_solutions != equation.n_roots) {
            printf("\nTEST %ld:" RED "WA" YEL "\n"
                   "a, b, c = %lg, %lg, %lg\n" WHT,
                   i, equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);
            printf(GRN "CORRECT ANSWER:\n");
            fprintf_quadr_equ_obj(stdout, equation);
            printf(RED "WRONG ANSWER:\n");

            struct quadr_equ_obj wrong_equation = INIT_QUADR_EQU_OBJ_STRUCTS(equation.coeffs, roots, n_solutions);
            fprintf_quadr_equ_obj(stdout, wrong_equation);
            printf(WHT "\n\n");
        } else {
            printf("TEST %ld:" GRN "OK" WHT "\n", i);
        } 
    }

    return EXIT_SUCCESS;
}

int quadr_equ_solver_manual_testing(size_t n_tests, const quadr_equ_obj test_data[]) {
    for (size_t i = 0; i < n_tests; i++) {
        struct quadr_equ_obj equation = test_data[i];
        struct quadr_roots roots;
        init_quadr_roots(&roots);

        int n_solutions = quadr_equ_solver(equation.coeffs, &roots);

        printf("coefs: %lg %lg %lg\n", equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);

        if (!cmp_eq_roots(roots, equation.roots) || 
                n_solutions != equation.n_roots) {
            printf("\nTEST %ld:" RED "WA" YEL "\n"
                   "a, b, c = %lg, %lg, %lg\n" WHT,
                   i, equation.coeffs.a, equation.coeffs.b, equation.coeffs.c);
            printf(GRN "CORRECT ANSWER:\n");
            fprintf_quadr_equ_obj(stdout, equation);
            printf(RED "WRONG ANSWER:\n");

            struct quadr_equ_obj wrong_equation = INIT_QUADR_EQU_OBJ_STRUCTS(equation.coeffs, roots, n_solutions);
            fprintf_quadr_equ_obj(stdout, wrong_equation);
            printf(WHT "\n\n");
        } else {
            printf("TEST %ld:" GRN "OK" WHT "\n", i);
        }
    }

    return EXIT_SUCCESS;
}
