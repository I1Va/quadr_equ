#include <assert.h>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#include "quadr_equ.h"
#include "colors.h"
#include "quadr_config.h"
#include "test_funcs.h"

const static struct quadr_equ_obj MANUAL_TESTS[] = {
    INIT_QUADR_EQU_OBJ(0,       0,       0,       NAN, NAN, INF_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0,       0,       1,       NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0,       1,       0,         0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(0,       1,       1,        -1, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1,       0,       0,         0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(1,       0,       1,       NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1,       1,       0,        -1,   0, TWO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(1,       1,       1,       NAN, NAN, NO_SOLUTIONS),
    INIT_QUADR_EQU_OBJ(0, DBL_MAX, DBL_MIN,         0, NAN, ONE_SOLUTION),
    INIT_QUADR_EQU_OBJ(0, DBL_MIN, DBL_MAX, -INFINITY, NAN, ONE_SOLUTION),
};

void init_quadr_coeffs(struct quadr_coeffs *coeffs) {
    coeffs->a = NAN;
    coeffs->b = NAN;
    coeffs->c = NAN;
}

void init_quadr_roots(struct quadr_roots *roots) {
    roots->x1 = NAN;
    roots->x2 = NAN;
}

void init_quadr_obj(struct quadr_equ_obj *equation) {
    init_quadr_coeffs(&equation->coeffs);
    init_quadr_roots(&equation->roots);
    equation->n_roots = INIT_SOLUTIONS;
}

int quadr_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots) {
    assert(roots != NULL);
    if (fabs(coeffs.a) < EPS) {
        if (fabs(coeffs.b) < EPS) {
            if (fabs(coeffs.c) < EPS) {
                return INF_SOLUTIONS;
            } else {
                return NO_SOLUTIONS;
            }
        } else {
            const double x1 = -coeffs.c / coeffs.b;
            assert(!isnan(x1));
            roots->x1 = x1;
            return ONE_SOLUTION;
        }
    }

    const double discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
    if (discr < -EPS) {
        return NO_SOLUTIONS;
    } else if (fabs(discr) < EPS) {
        roots->x1 = -coeffs.b / 2.0 / coeffs.a;
        return ONE_SOLUTION;
    }
    const double sqrt_discr = sqrt(discr);

    debug("Sq_D: %lg\n", sqrt_discr);
    debug("-b: %lg\n", -coeffs.b);

    roots->x1 = (-coeffs.b - sqrt_discr) / 2.0 / coeffs.a;
    roots->x2 = (-coeffs.b + sqrt_discr) / 2.0 / coeffs.a;

    return TWO_SOLUTIONS;
}

int scanf_quadr_coeffs(struct quadr_coeffs *coeffs) {
    assert(coeffs != NULL);
    for (size_t i = 0; i < N_ATTEMPTS; i++) {
        const int n_suc_args = scanf("%lg %lg %lg", &(coeffs->a), &(coeffs->b), &(coeffs->c));
        debug("n_suc_args: %d\n", n_suc_args);

        if (n_suc_args < 3) {
            fprintf(stdout, "Invalid data format. Repeat input: \n");
            int c = EOF;
            while ((c = getchar()) != EOF && c != '\n');
        } else {
            return RETURN_SUCCESS;
        }
    }
    fprintf(stdout, "Invalid data format. Program exit\n");
    return RETURN_FAILURE;
}

int fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ) {
    assert(equ != NULL);
    assert(stream != NULL);

    if (fscanf(
            stream, "%lg %lg %lg %lg %lg %d", \
            &equ->coeffs.a, &equ->coeffs.b, &equ->coeffs.c, \
            &equ->roots.x1, &equ->roots.x2, &equ->n_roots
        ) != 6) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

int fprintf_num_solutions(FILE *stream, const int n_roots) {
    assert(stream != NULL);

    switch (n_roots)
    {
    case NO_SOLUTIONS: 
        fprintf(stream, "quadratic equation hasn't solutions\n");
        break;
    case ONE_SOLUTION: 
        fprintf(stream, "quadratic equation has one solution\n");
        break;
    case TWO_SOLUTIONS : 
        fprintf(stream, "quadratic equation has two solutions\n");
        break;
    case INF_SOLUTIONS: 
        fprintf(stream, "quadratic equation has infinity solutions\n");
        break;
    case INIT_SOLUTIONS:
        fprintf(stream, "ERROR: quadratic equation roots have INIT_VALUE: %d", INIT_SOLUTIONS);
        return RETURN_FAILURE;
    default:
        fprintf(stderr, "fprintf_num_solutions hasn't recognise n_roots = %d", n_roots);
        return RETURN_FAILURE;
    }
    
    return RETURN_SUCCESS;
}

int fprintf_quadr_equ_obj(FILE *stream, const struct quadr_equ_obj equ) {
    assert(stream != NULL);

    print_border();
    if (fprintf_yel(stream, "%lgx²", equ.coeffs.a) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }
    
    if (equ.coeffs.b > 0) {
        fprintf_yel(stream, " + ");
    } else {
        fprintf_yel(stream, " - ");
    }

    if (fprintf_yel(stream, "%lgx", fabs(equ.coeffs.b)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }

    if (equ.coeffs.c > 0) {
        fprintf_yel(stream, " + ");
    } else {
        fprintf_yel(stream, " - ");
    }

    fprintf_yel(stream, "%lg = 0\n", fabs(equ.coeffs.c));

    fprintf_grn(stream, "x1 = %lg\n", equ.roots.x1);
    fprintf_grn(stream, "x2 = %lg\n", equ.roots.x2);
    fprintf_num_solutions(stream, equ.n_roots);

    print_border();
    return EXIT_SUCCESS;
}


bool eq_doubles(const double x1, const double x2) {
    if (fpclassify(x1) != fpclassify(x2)) {
        return false;
    }
    if (isnormal(x1) && isnormal(x2) && fabs(x1 - x2) > EPS) {
        return false;
    }
    return true;
}

bool eq_doubles_roots(const struct quadr_roots r1, const struct quadr_roots r2) {
    return eq_doubles(r1.x1, r2.x1) && eq_doubles(r1.x2, r2.x2);
}

int example_mode_launch() {
    printf_red("\n----------------------------> EXAMPLE MODE <----------------------------\n" WHT);
    generate_tests_to_file(PATH_EXAMPLE, 1);

    struct quadr_equ_obj example_test[1];
    get_tests_from_file(PATH_EXAMPLE, example_test);

    if (fprintf_quadr_equ_obj(stdout, example_test[0])) {
        fprintf(stderr, "%s: FAILED TO: fprintf_quadr_equ_obj()\n", __PRETTY_FUNCTION__);
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

int user_mode_launch() {
    printf_red("\n-----------------------------> USER MODE <------------------------------\n");

    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);

    printf_yel("# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf(WHT"# Enter coefficients(a, b, c): ");

    if (scanf_quadr_coeffs(&coeffs) == RETURN_FAILURE) {
        fprintf(stderr, "%s: FAILED TO: scanf_quadr_coeffs()\n", __PRETTY_FUNCTION__);
        return RETURN_FAILURE;
    }

    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    assert(!isnan(coeffs.a));
    assert(!isnan(coeffs.b));
    assert(!isnan(coeffs.c));

    struct quadr_roots roots;
    init_quadr_roots(&roots);
    const int n_solutions = quadr_equ_solver(coeffs, &roots);

    debug("sols: %d\n", n_solutions);
    struct quadr_equ_obj equation = INIT_QUADR_EQU_OBJ_STRUCTS(coeffs, roots, n_solutions);

    if (fprintf_quadr_equ_obj(stdout,equation) == RETURN_FAILURE) {
        fprintf(stderr, "user_mode_launch(): FAILED TO: fprintf_quadr_equ_obj()\n");
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

int testing_mode_launch() {
    printf_red("\n----------------------------> TESTING MODE <-----------------------------\n");
    printf_yel("Launch auto or manual test mode? [A/m] ");

    int cur_char = getchar();
    if (!(cur_char == '\n' || cur_char == 'A' || cur_char == 'a')) {
        if (quadr_equ_solver_manual_testing(ARR_SIZE(MANUAL_TESTS), MANUAL_TESTS) == RETURN_FAILURE) {
            debug("FAILED TO: quadr_equ_solver_manual_testing()\n");
            return RETURN_FAILURE;
        }

        return RETURN_SUCCESS;
    }

    printf_yel("Generate new tests? [Y/n]: ");
    cur_char = getchar();

    bool input_state = false;
    size_t n_tests = 0;

    if (cur_char == '\n' || cur_char == 'Y' || cur_char == 'y') {
        for (size_t i = 0; i < N_ATTEMPTS; i++) {
            printf_yel("How many tests? (MAX: %ld): ", MAX_N_TESTS);

            if (!scanf("%ld", &n_tests)) {
                while(getchar() != '\n');
            
                printf_red("Invalid data format. Enter positive integer\n");
            } else {
                input_state = true;
                break;
            }
        }
    }

    if (!input_state) {
        printf_red("Invalid data format. Mode exit\n");
        return RETURN_FAILURE;
    } 

    if (generate_tests_to_file(PATH_AUTO_TESTS, n_tests) == RETURN_FAILURE) {
        debug("FAILED TO: generate_tests_to_file()\n");
        return RETURN_FAILURE;
    }

    if (quadr_equ_solver_file_testing(PATH_AUTO_TESTS)) {
        debug("FAILED TO: quadr_equ_solver_file_testing()\n");
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

char* check_lexem_x2(char *string_ptr) {
    assert(string_ptr != NULL);

    if (*string_ptr != 'x' && *string_ptr != 'X') {
        return NULL;
    }
    string_ptr++;

    if (*string_ptr == '^') {
        string_ptr++;
    } else if (*string_ptr == '*' && *(string_ptr + 1) == '*') {
        string_ptr += 2;
    } else {
        return NULL;
    }

    if (*string_ptr != '2') {
        return NULL;
    }
    string_ptr++;

    return string_ptr;
}

char* check_lexem_x(char *string_ptr) {
    if (*string_ptr == 'x') {
        string_ptr++;
        return string_ptr;
    }
    return NULL;
}

void remove_spaces(char *string_ptr) {
    assert(string_ptr != NULL);

    char buffer_string[MAX_STRING_SIZE] = {0};

    char *buffer_string_ptr = buffer_string;
    char *cur_string_ptr = string_ptr;

    while (*cur_string_ptr != '\0') {
        if (*cur_string_ptr != ' ') {
            *buffer_string_ptr = *cur_string_ptr;
            buffer_string_ptr++;
        }
        cur_string_ptr++;
    }

    strcpy(string_ptr, buffer_string);
}

void getline(char *string_ptr) {
    assert(string_ptr != NULL);

    int cur_char = getchar();
    size_t idx = 0;
    while (cur_char != '\n' && idx < MAX_STRING_SIZE) {
        *string_ptr++ = (char) cur_char;
        cur_char = getchar();
        idx++;
    }
}

char* get_coeff_lexem(double *num_ptr, char *string_ptr) {
    assert(num_ptr != NULL);
    assert(string_ptr != NULL);

    char *start_string_ptr = string_ptr;
    *num_ptr = strtod(string_ptr, &string_ptr);
    if (start_string_ptr == string_ptr) {
        if (*string_ptr == '-') {
            *num_ptr *= -1.0;
            string_ptr++;
        } else if (*string_ptr == '+') {
            *num_ptr = 1.0;
            string_ptr++;
        } else {
            *num_ptr = 1.0;
        }
    }
    return string_ptr;
}

int parsing_mode_launch() {
    printf_red("\n----------------------------> PARSING MODE <-----------------------------\n");
    print_border();
    printf_yel("Enter your quadratic equation:\n");
    printf_yel("Example: -1.3444 x^2     -5.3x + 12.16\n");

    char equation_string[MAX_STRING_SIZE] = {0};
    getline(equation_string);
    remove_spaces(equation_string);
    char *equation_string_ptr = equation_string;

    quadr_equ_obj equation = {{0, 0, 0}, {0, 0}, 0};
    init_quadr_obj(&equation);
    
    equation_string_ptr = get_coeff_lexem(&equation.coeffs.a, equation_string_ptr);

    if ((equation_string_ptr = check_lexem_x2(equation_string_ptr)) == NULL) {
        printf_red("Invalid input\n");
        return RETURN_FAILURE;
    }

    equation_string_ptr = get_coeff_lexem(&equation.coeffs.b, equation_string_ptr);

    if ((equation_string_ptr = check_lexem_x(equation_string_ptr)) == NULL) {
        printf_red("Invalid input\n");
        return RETURN_FAILURE;
    }

    equation_string_ptr = get_coeff_lexem(&equation.coeffs.c, equation_string_ptr);

    const int n_roots = simple_quadr_solve(equation.coeffs, &equation.roots);
    equation.n_roots = n_roots;

    fprintf_quadr_equ_obj(stdout, equation);
    
    return RETURN_SUCCESS;
}

void mode_manager(const int argc, char *const argv[]) {
    int user_mode_flag = 0;
	int testing_mode_flag = 0;
	int example_mode_flag = 0;
    int parsing_mode_flag = 0;

    const char *const short_options = "utep";

    int short_option_switch = 0;

	const struct option long_options[] = {
		{ "user", no_argument, &user_mode_flag, 1 },
		{ "testing", no_argument, &testing_mode_flag, 1 },
		{ "example", no_argument, &example_mode_flag,  1 },
        { "parsing", no_argument, &parsing_mode_flag,  1 },
		{ NULL, 0, NULL, 0}
	};

	while ((short_option_switch = getopt_long(argc, argv, short_options,
		    long_options, NULL)) != -1) {
            switch (short_option_switch) {
                case 'u':
                    user_mode_flag = 1;
                    break;
                case 't':
                    testing_mode_flag = 1;
                    break;
                case 'e':
                    example_mode_flag = 1;
                    break;
                case 'p':
                    parsing_mode_flag = 1;
                    break;
                default:
                    break;
            }
        }

    if (example_mode_flag) {
        if (example_mode_launch() == RETURN_FAILURE) {
            debug("FAILED TO: example_mode_launch()\n");
        }
    }

    if (user_mode_flag) {
        if (user_mode_launch() == RETURN_FAILURE) {
            debug("FAILED TO: user_mode_launch()\n");
        }
    }

    if (testing_mode_flag) {
        if (testing_mode_launch() == RETURN_FAILURE) {
            debug("FAILED TO: testing_mode_launch()\n");
        }
    }

    if (parsing_mode_flag) {
        if (parsing_mode_launch() == RETURN_FAILURE) {
            debug("mode_manager: FAILED TO: parsing_mode_launch()\n");
        }
    }
}
