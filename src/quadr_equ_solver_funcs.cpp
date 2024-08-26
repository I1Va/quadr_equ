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

void init_quadr_coeffs(struct quadr_coeffs *coeffs) {
    coeffs->a = NAN;
    coeffs->b = NAN;
    coeffs->c = NAN;
}

void init_quadr_roots(struct quadr_roots *roots) {
    roots->x1 = NAN;
    roots->x2 = NAN;
}

int quadr_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots) {
    if (fabs(coeffs.a) < EPS) {
        if (fabs(coeffs.b) < EPS) {
            if (fabs(coeffs.c) < EPS) {
                return INF_SOLUTIONS;
            } else {
                return NO_SOLUTIONS;
            }
        } else {
            double x1 = -coeffs.c / coeffs.b;
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
    const double sqrt_discr = sqrt(discr); // !поменять название sqrt_sqdef...

    debug("Sq_D: %lg\n", sqrt_discr);
    debug("-b: %lg\n", -coeffs.b);

    roots->x1 = (-coeffs.b - sqrt_discr) / 2.0 / coeffs.a;
    roots->x2 = (-coeffs.b + sqrt_discr) / 2.0 / coeffs.a;

    return TWO_SOLUTIONS;
}

int scanf_quadr_coeffs(struct quadr_coeffs *coeffs) {
    for (size_t i = 0; i < N_ATTEMPTS; i++) {
        int n_suc_args = scanf("%lg %lg %lg", &(coeffs->a), &(coeffs->b), &(coeffs->c));
        debug("n_suc_args: %d\n", n_suc_args);

        if (n_suc_args < 3) {
            fprintf(stdout, "Invalid data format. Repeat input: \n");
            // fprintf(stderr, "%s", strerror(errno));
            int c = EOF;
            while ((c = getchar()) != EOF && c != '\n');
        } else {
            // fprintf(stderr, "%s", strerror(errno));
            return RETURN_SUCCES;
        }
    }
    fprintf(stdout, "Invalid data format. Program exit\n");
    return RETURN_FAILURE;
}

int fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ) {
    if (fscanf(
            stream, "%lg %lg %lg %lg %lg %d", \
            &equ->coeffs.a, &equ->coeffs.b, &equ->coeffs.c, \
            &equ->roots.x1, &equ->roots.x2, &equ->n_roots
        ) != 6) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }


    return RETURN_SUCCES;
}

int fprintf_num_solutions(FILE* stream, const int n_roots) {
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
    default:
        fprintf(stderr, "fprintf_num_solutions hasn't recognise n_roots = %d", n_roots);
    }
    return RETURN_SUCCES;
}

int fprintf_quadr_equ_obj(FILE* stream, const struct quadr_equ_obj equ) {
    print_border();
    if (fprintf(stream, YEL "%lgx²", equ.coeffs.a) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }
    
    if (equ.coeffs.b > 0) {
        printf(YEL " + ");
    } else {
        printf(YEL " - ");
    }
    if (fprintf(stream, YEL "%lgx", fabs(equ.coeffs.b)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RETURN_FAILURE;
    }
    if (equ.coeffs.c > 0) {
        printf(YEL " + ");
    } else {
        printf(YEL " - ");
    }
    fprintf(stream, YEL "%lg\n", fabs(equ.coeffs.c));
    fprintf(stream, "x1 = %lg\n", equ.roots.x1);
    fprintf(stream, "x2 = %lg\n", equ.roots.x2);
    fprintf_num_solutions(stream, equ.n_roots);
    print_border();
    return EXIT_SUCCESS;
}

bool cmp_strs(const char s1[], const char s2[]) {
    for (size_t i = 0; i > 0; i++) {
        if (s1[i] == '\0' && s2[i] == '\0') {
            return true;
        }
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

bool cmp_eq(const double x1, const double x2) {
    if (fpclassify(x1) != fpclassify(x2)) {
        return false;
    }
    if (isnormal(x1) && isnormal(x2) && fabs(x1 - x2) > EPS) {
        return false;
    }
    return true;
}

bool cmp_eq_roots(const struct quadr_roots r1, const struct quadr_roots r2) {
    return cmp_eq(r1.x1, r2.x1) && cmp_eq(r1.x2, r2.x2);
}

int example_mode_launch() {
    printf(RED "\n----------------------------> EXAMPLE MODE <----------------------------\n");

    generate_tests_to_file(PATH_EXAMPLE, 1);

    struct quadr_equ_obj example_data[1];
    get_tests_from_file(PATH_EXAMPLE, example_data);

    if (fprintf_quadr_equ_obj(stdout, example_data[0])) {
        fprintf(stderr, "%s: FAILED TO: fprintf_quadr_equ_obj()\n", __PRETTY_FUNCTION__);
        return RETURN_FAILURE;
    }

    return RETURN_SUCCES;
}

int user_mode_launch() {
    printf(RED "\n-----------------------------> USER MODE <------------------------------\n");

    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);

    printf(YEL"# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf(WHT"# Enter coefficients(a, b, c): ");

    if (scanf_quadr_coeffs(&coeffs) == RETURN_FAILURE) {
        fprintf(stderr, "%s: FAILED TO: scanf_quadr_coeffs()\n", __PRETTY_FUNCTION__);
        return RETURN_FAILURE;
    }

    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    assert(!isnan(coeffs.b));
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
    return RETURN_SUCCES;
}

int testing_mode_launch() {
    printf(RED "\n----------------------------> TESTING MODE <-----------------------------\n");
    printf("Launch auto or manual test mode? [A/m] ");
    int v1 = getchar();
    if (v1 == '\n' || v1 == 'A' || v1 == 'a') {
        printf(YEL "Generate new tests? [Y/n]: " WHT);

        int v2 = getchar();

        bool input_state = false;
        size_t n_tests = 0;
        if (v2 == '\n' || v2 == 'Y' || v2 == 'y') {
            for (size_t i = 0; i < N_ATTEMPTS; i++) {
                printf(YEL"How many tests? (MAX: %ld): " WHT, MAX_N_TESTS);

                if (!scanf("%ld", &n_tests)) {
                    fprintf(stderr, RED "Invalid data format. enter positive integer: " WHT);
                } else {
                    input_state = true;
                    break;
                }
            }
        }
        if (!input_state) {
            fprintf(stdout, "Invalid data format. Mode exit\n");
            return RETURN_FAILURE;
        } 

        if (generate_tests_to_file(PATH_AUTO_TESTS, n_tests) == RETURN_FAILURE) {
            fprintf(stderr, "%s: FAILED TO: generate_tests_to_file()\n", __PRETTY_FUNCTION__);
            return RETURN_FAILURE;
        }

        if (quadr_equ_solver_file_testing(PATH_AUTO_TESTS)) {
            fprintf(stderr, "%s: FAILED TO: quadr_equ_solver_file_testing()\n", __PRETTY_FUNCTION__);
            return RETURN_FAILURE;
        }

    } else {
        if (quadr_equ_solver_manual_testing(ARR_SIZE(MANUAL_TESTS), MANUAL_TESTS) == RETURN_FAILURE) {
            fprintf(stderr, "%s: FAILED TO: quadr_equ_solver_manual_testing()\n", __PRETTY_FUNCTION__);
            return RETURN_FAILURE;
        }
    }

    return RETURN_SUCCES;
}


// strtod

// char* get_num_from_string(char *ptr, char *str) {
//     bool start = true;
//     bool num = false;
//     bool sep = false;
//     char sign = '0';
//     while (1) {
//         if (*ptr == '+' || *ptr == '-') {
//             sign = *ptr;
//             if (start) {
//                 *str = *ptr;
//                 ptr++;
//                 str++;
//                 start = false;
//             } else {
//                 return NULL;
//             }
//         } else if (*ptr >= '0' && *ptr <= '9') {
//             num = true;
//             *str = *ptr;
//             ptr++;
//             str++;
//             start = false;
//         } else if (*ptr == '.' || *ptr == ',') {
//             if (!num || sep) {
//                 return NULL;
//             }
//             *str = *ptr;
//             ptr++;
//             str++;
//             start = false;
//         } else {
//             if (!num) {
//                 if (start) {
//                     *str = '1';
//                     str++;
//                 } else if (sign == 1) {
                    
//                 }
//             }
//             if (start) {
//                 return ptr;
//             }
//             if (!num) {
//                 return NULL;
//             }
//             return ptr;
//         }
//     }
// }

char* check_x_2(char *s1) {
    if (*s1 != 'x' && *s1 != 'X') {
        return NULL;
    }
    s1++;
    if (*s1 == '^') {
        s1++;
    } else if (*s1 == '*' && *(s1 + 1) == '*') {
        s1 += 2;
    } else {
        return NULL;
    }
    if (*s1 != '2') {
        return NULL;
    }
    s1++;
    return s1;
}

// for (size_t i = 0; com[i] != '\0'; i++) {
//         cur->str[cur->idx++] = com[i];
//         if (com[i] >= '0' && com[i] <= '9') {
//             cur->num = true;
//         } else if (com[i] == '.' || com[i] == ',') {
//             if (!cur->num || cur->sep) {
//                 printf("Invalid input\n");
//                 return RETURN_FAILURE;
//             }
//             cur->sep = true;
//         } else if (com[i] == 'x') {
//             if (!cur->num) {
//                 cur->val = 1;
                
//             }
//         }
//     } 

char* get_num(double *val, char* ptr) {
    char *prev = ptr;
    *val = strtod(ptr, &ptr);
    if (prev == ptr) {
        *val = 1.0;
        if (*ptr == '-') {
            *val *= -1.0;
        }
        ptr++;
    }
    return ptr;
}

int parsing_mode_launch() {
    printf(RED "\n----------------------------> PARSING MODE <-----------------------------\n");
    print_border();
    
    printf(YEL "Enter your quadratic equation without spaces:\n");

    char com[MAX_STRING_SIZE];
    char *com_ptr = com;
    scanf("%s", com);

    quadr_equ_obj equation;
    
    com_ptr = get_num(&equation.coeffs.a, com_ptr);
    if ((com_ptr = check_x_2(com_ptr)) == NULL) {
        printf("Invalid input\n");
        return RETURN_FAILURE;
    }

    com_ptr = get_num(&equation.coeffs.b, com_ptr);
    if (*com_ptr != 'x') {
        printf("Invalid input\n");
        return RETURN_FAILURE;
    }
    com_ptr++;

    com_ptr = get_num(&equation.coeffs.c, com_ptr);

    int n_roots = simple_quadr_solve(equation.coeffs, &equation.roots);
    equation.n_roots = n_roots;

    fprintf_quadr_equ_obj(stdout, equation);
    
    return RETURN_SUCCES;
}

void mode_manager(int argc, char **argv) {
    int user_mode_flag = 0;
	int testing_mode_flag = 0;
	int example_mode_flag = 0;
    int parsing_mode_flag = 0;

    const char* short_options = "utep";
	const struct option long_options[] = {
		{ "user", no_argument, &user_mode_flag, 1 },
		{ "testing", no_argument, &testing_mode_flag, 1 },
		{ "example", no_argument, &example_mode_flag,  1 },
        { "parsing", no_argument, &parsing_mode_flag,  1 },
		{ NULL, 0, NULL, 0}
	};
    int res;
	while ((res = getopt_long(argc, argv, short_options,
		long_options, NULL))!=-1) {
            switch (res) {
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
            fprintf(stderr, "%s: FAILED TO: example_mode_launch()\n", __PRETTY_FUNCTION__);
        }
    }
    if (user_mode_flag) {
        if (user_mode_launch() == RETURN_FAILURE) {
            fprintf(stderr, "%s: FAILED TO: user_mode_launch()\n", __PRETTY_FUNCTION__);
        }
    }
    if (testing_mode_flag) {
        if (testing_mode_launch() == RETURN_FAILURE) {
            fprintf(stderr, "%s: FAILED TO: testing_mode_launch()\n", __PRETTY_FUNCTION__);
        }
    }
    if (parsing_mode_flag) {
        if (parsing_mode_launch() == RETURN_FAILURE) {
            fprintf(stderr, "mode_manager: FAILED TO: parsing_mode_launch()\n");
        }
    }
}