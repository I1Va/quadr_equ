#include <stddef.h>
#include <cmath>
#include <float.h>

#include "quadr_equ.h"


static struct quadr_equ_obj MANUAL_TESTS[] = 
{
    INIT_QUADR_EQU_OBJ(0, 0, 0, NAN, NAN, INF_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, 0, 1, NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, 1, 0, 0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(0, 1, 1, -1, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1, 0, 0, 0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1, 0, 1, NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1, 1, 0, -1, 0, TWO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1, 1, 1, NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, DBL_MAX, DBL_MIN, 0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(0, DBL_MIN, DBL_MAX, -INFINITY, NAN, ONE_SOLUTION),
};

const size_t MAX_N_TESTS = 100;


int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots);

void generate_tests_to_file(const char path[], const size_t n_tests);

size_t get_tests_from_file(const char path[], quadr_equ_obj test_data[]);

void quadr_equ_solver_manual_testing(size_t n_tests, const quadr_equ_obj test_data[]);

void quadr_equ_solver_file_testing(const char path[]);

