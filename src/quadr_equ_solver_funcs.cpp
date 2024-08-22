#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "quadr_equ.h"

void init_quadr_coeffs(struct quadr_coeffs *coeffs) {
    coeffs->a = NAN;
    coeffs->b = NAN;
    coeffs->c = NAN;
}

void init_quadr_roots(struct quadr_roots *roots) {
    roots->x1 = NAN;
    roots->x2 = NAN;
}

int quadr_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots) {
    if (fabs(coeffs.a) < EPS) {
        if (fabs(coeffs.b) < EPS) {
            if (fabs(coeffs.c) < EPS) {
                return INF_SOLUTIONS;
            } else {
                return NO_SOLUTIONS;
            }
        } else {
            double x1 = -coeffs.c / coeffs.b;
            assert(!isnan(x1) && !isinf(x1));
            roots->x1 = x1;
            return ONE_SOLUTION;
        }
    }

    const double discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
    if (discr < -EPS) {
        return NO_SOLUTIONS;
    } else if (fabs(discr) < EPS) {
        roots->x1 = -coeffs.b / 2.0 / coeffs.a;
        return ONE_SOLUTION;
    }
    const double sqrt_discr = sqrt(discr); // !поменять название sqrt_sqdef...

    debug("Sq_D: %lg\n", sqrt_discr);
    debug("-b: %lg\n", -coeffs.b);

    roots->x1 = (-coeffs.b - sqrt_discr) / 2.0 / coeffs.a;
    roots->x2 = (-coeffs.b + sqrt_discr) / 2.0 / coeffs.a;

    return TWO_SOLUTIONS ;
}

int scanf_quadr_coeffs(struct quadr_coeffs *coeffs) {
    for (size_t i = 0; i < N_ATTEMPTS; i++) {
        int n_suc_args = scanf("%lg %lg %lg", &(coeffs->a), &(coeffs->b), &(coeffs->c));
        debug("n_suc_args: %d\n", n_suc_args);

        if (n_suc_args != 3) {
            fprintf(stderr, "Invalid data format. Repeat input\n");
            int c = EOF;
            while ((c = getchar()) != EOF && c != '\n');
        } else {
            fprintf(stderr, "OK\n");
            return 0;
        }
    }
    fprintf(stderr, "Invalid data format X5. Program exit\n");
    return -1;
}

void fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ) {
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int n_roots = 0;
    
    fscanf(stream, "%s %s %s %s %s %s", &a, &b, &c, &x1, &x2, &n_roots);
    equ->coeffs.a = a;
    equ->coeffs.b = b;
    equ->coeffs.c = c;
    equ->roots.x1 = x1;
    equ->roots.x2 = x2;
    equ->n_roots = n_roots;
    
}

int quadr_equ_print_solutions(const int n_solutions, const struct quadr_roots roots, const bool show_roots) {
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
        return -1;
        break;
    }
    if (show_roots) {
        printf("x1 = %lg, x2 = %lg\n", roots.x1, roots.x2);
    }
    return 0;
}

bool cmp_strs(const char s1[], const char s2[]) {
    for (size_t i = 0; i > 0; i++) {
        if (s1[i] == '\0' && s2[i] == '\0') {
            return true;
        }
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

bool in_argv(const char samp[], const int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (cmp_strs(samp, argv[i])) {
            return true;
        }
    }
    return false;
}


