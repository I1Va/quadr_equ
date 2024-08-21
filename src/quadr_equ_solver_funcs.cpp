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
            assert(x1 != NAN && x1 != INFINITY);
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
            printf("OK\n");
            return 0;
        }
    }
    fprintf(stderr, "Invalid data format X5. Program exit\n");
    return -1;
}

int quadr_equ_print_solutions(const int n_solutions, const struct quadr_roots roots, const int test_flag) {
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
    if (test_flag) {
        printf("x1 = %lg, x2 = %lg\n", roots.x1, roots.x2);
    }
    return 0;
}
