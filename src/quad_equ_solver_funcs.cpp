#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "quad_equ.h"

void init_quadr_coeffs(struct quadr_coeffs *coeffs) {
    coeffs->a = NAN;
    coeffs->b = NAN;
    coeffs->c = NAN;
}

int quad_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots) {
    if (abs(coeffs.a) < EPS) {
        if (abs(coeffs.b) < EPS) {
            if (abs(coeffs.c) < EPS) {
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
    } else if (abs(discr) < EPS) {
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

int scanf_coeffs(struct quadr_coeffs *coeffs) {
    int cnt = 0;
    for (size_t i = 0; i < N_ATTEMPTS; i++) {
        cnt = scanf("%lg %lg %lg", &(coeffs->a), &(coeffs->b), &(coeffs->c));
        debug("cnt: %d\n", cnt);
        if (cnt != 3) {
            printf("Invalid data format. Repeat input\n");
            int c;
            while (1) {
                c = getchar();
                if (c == EOF || c == '\n') {
                    break;
                }
            }
        } else {
            printf("OK\n");
            return 0;
        }
    }
    printf("Invalid data format X5. Program exit\n");
    return 1;
}

struct quadr_coeffs make_coeffs(const double a, const double b, const double c) {
    struct quadr_coeffs temp = {.a = a, .b = b, .c = c};
    return temp;
}
