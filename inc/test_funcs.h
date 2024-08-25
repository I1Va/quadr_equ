#include <stddef.h>
#include <cmath>
#include <float.h>

#include "quadr_equ.h"


const size_t MAX_N_TESTS = 100;


int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots);

void generate_tests_to_file(const char path[], const size_t n_tests);

size_t get_tests_from_file(const char path[], quadr_equ_obj test_data[]);

void quadr_equ_solver_manual_testing(size_t n_tests, const quadr_equ_obj test_data[]);

void quadr_equ_solver_file_testing(const char path[]);

