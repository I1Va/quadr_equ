#include <assert.h>
#include <math.h>
#include "Quad_Equ.h"

void init_quadr_coeffs(struct quadr_coeffs *val) {
    val->a = NAN;
    val->b = NAN;
    val->c = NAN;
}

int QE_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots) {
    if (coeffs.a == 0) {
        if (coeffs.b == 0) {
            if (coeffs.c == 0) {
                return QE_INF_SOLUTIONS;
            } else {
                return QE_NO_SOLUTIONS;
            }
        } else {
            roots->x1 = -coeffs.c / coeffs.b;
            return QE_ONE_SOLUTIONS;
        }
    }
    double Discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
    if (Discr < 0) {
        return QE_NO_SOLUTIONS;
    } else if (Discr == 0) {
        roots->x1 = -coeffs.b / 2.0 / coeffs.a;
        return QE_ONE_SOLUTIONS;
    }
    double S_Discr = sqrt(Discr); // !поменять название sqrt_sqdef...
    roots->x1 = (-coeffs.b - S_Discr) / 2.0 / coeffs.a;
    roots->x2 = (-coeffs.b + S_Discr) / 2.0 / coeffs.a;
    return QE_TWO_SOLUTIONS ;
}

