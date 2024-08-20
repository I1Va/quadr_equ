#include <assert.h>
#include <math.h>
#include "Quad_Equ.h"

void init_quadr_coeffs(struct quadr_coeffs *val) {
    val->a = NAN;
    val->b = NAN;
    val->c = NAN;
}

int QE_solver(const struct quadr_coeffs coeffs, double *const x1, double *const x2) {
    assert(x1 != x2);
    if (coeffs.a == 0) {
        if (coeffs.b == 0) {
            if (coeffs.c == 0) {
                return QE_Inf_Solutions;
            } else {
                return QE_No_Solutions;
            }
        } else {
            *x1 = -coeffs.c / coeffs.b;
            return QE_One_Solution;
        }
    }
    double Discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
    if (Discr < 0) {
        return QE_No_Solutions;
    } else if (Discr == 0) {
        *x1 = -coeffs.b / 2.0 / coeffs.a;
        return QE_One_Solution;
    }
    double S_Discr = sqrt(Discr); // !поменять название sqrt_sqdef...
    *x1 = (-coeffs.b - S_Discr) / 2.0 / coeffs.a;
    *x2 = (-coeffs.b + S_Discr) / 2.0 / coeffs.a;
    return QE_Two_Solutions;
}

