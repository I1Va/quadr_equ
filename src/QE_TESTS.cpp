#include "Quad_Equ.h"

static struct quadr_coeffs QE_TESTS[] = 
{
    make_coeffs(0, 0, 0),
    make_coeffs(0, 0, 1),
    make_coeffs(0, 1, 0),
    make_coeffs(0, 1, 1),
    make_coeffs(1, 0, 0),
    make_coeffs(1, 0, 1),
    make_coeffs(1, 1, 0),
    make_coeffs(1, 1, 1),
    make_coeffs(0, 1e100, 1e-100),
    make_coeffs(0, 1e-100, 1e100),
    make_coeffs(142879.123, 12.434, 1232.222),
};