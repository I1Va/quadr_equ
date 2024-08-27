/*!
    \file
    \brief Header file with testing funtions declaration
*/

#ifndef TEST_FUNCS_H
#define TEST_FUNCS_H

#include <stddef.h>
#include <cmath>
#include <float.h>
#include <stdio.h>

#include "quadr_equ.h"


const size_t MAX_N_TESTS = 128;


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
    \return return_state
*/
int generate_tests_to_file(const char path[], const size_t n_tests);


/*!
    \brief get tests from file into array of quadr_equ_obj

    \param[in] path_to_file
    \param[out] test_data 
    \return number of successful readed tests
*/
size_t get_tests_from_file(const char path[], quadr_equ_obj test_data[]);


/*!
    \brief testing with test_data from manual array of quadr_equ_obj

    \param[in] n_tests
    \param[in] test_data 
*/
int quadr_equ_solver_manual_testing(size_t n_tests, const quadr_equ_obj test_data[]);


/*!
    \brief testing with test_data from file

    \param[in] path_to_file
*/
int quadr_equ_solver_file_testing(const char path[]);

#endif // TEST_FUNCS_H