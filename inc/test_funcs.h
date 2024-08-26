/*!
    \file
    \brief Header file with testing funtions declaration
*/

#include <stddef.h>
#include <cmath>
#include <float.h>

#include "quadr_equ.h"


const size_t MAX_N_TESTS = 100;


/*!
    \brief correct quadratic equation solver function

    used in testing
    \param[in] coeffs
    \param[out] roots 
*/
int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots);


/*!
    \brief generate random tests into file

    \param[in] path_to_file
    \param[in] n_tests 
*/
void generate_tests_to_file(const char path[], const size_t n_tests);


/*!
    \brief get tests from file into array of quadr_equ_obj

    \param[in] path_to_file
    \param[out] test_data 
*/
size_t get_tests_from_file(const char path[], quadr_equ_obj test_data[]);


/*!
    \brief testing with test_data from manual array of quadr_equ_obj

    \param[in] n_tests
    \param[in] test_data 
*/
void quadr_equ_solver_manual_testing(size_t n_tests, const quadr_equ_obj test_data[]);


/*!
    \brief testing with test_data from file

    \param[in] path_to_file
*/
void quadr_equ_solver_file_testing(const char path[]);
