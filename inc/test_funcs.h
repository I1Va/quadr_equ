#include <stddef.h>


const size_t MAX_N_TESTS = 100;


int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots);

void generate_tests_to_file(const char path[], const size_t n_tests);

void get_tests_from_file(const char path[], quadr_equ_obj test_data[]);
