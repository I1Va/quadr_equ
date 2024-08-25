#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "quadr_equ.h"
#include "colors.h"
#include <test_funcs.h>
#include "file_path.h"

int main() {
    // struct quadr_equ_obj data = INIT_QUADR_EQU_OBJ(1, 2, 3, 4, 5, TWO_SOLUTIONS);
    // fprintf_quadr_equ_obj(stdout, data);
    struct quadr_equ_obj data[MAX_N_TESTS];
    generate_tests_to_file(PATH_AUTO_TESTS, 12);
    get_tests_from_file(PATH_AUTO_TESTS, data);
    fprintf_quadr_equ_obj(stdout, data[0]);

    
}