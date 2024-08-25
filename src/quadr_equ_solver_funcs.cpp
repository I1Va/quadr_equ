#include <assert.h>
#include <cstddef>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <getopt.h>

#include "quadr_equ.h"
#include "colors.h"
#include "file_path.h"
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

    return TWO_SOLUTIONS ;
}

int scanf_quadr_coeffs(struct quadr_coeffs *coeffs) {
    for (size_t i = 0; i < N_ATTEMPTS; i++) {
        int n_suc_args = scanf("%lg %lg %lg", &(coeffs->a), &(coeffs->b), &(coeffs->c));
        debug("n_suc_args: %d\n", n_suc_args);

        if (n_suc_args != 3) {
            fprintf(stderr, "Invalid data format. Repeat input\n");
            int c = EOF;
            while ((c = getchar()) != EOF && c != '\n');
        } else {
            fprintf(stderr, "OK\n");
            return 0;
        }
    }
    fprintf(stderr, "Invalid data format X5. Program exit\n");
    return -1;
}

void fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ) {
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int n_roots = 0;
    
    fscanf(stream, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &x1, &x2, &n_roots);
    equ->coeffs.a = a;
    equ->coeffs.b = b;
    equ->coeffs.c = c;
    equ->roots.x1 = x1;
    equ->roots.x2 = x2;
    equ->n_roots = n_roots;
    
}

void fprintf_num_solutions(FILE* stream, const int n_roots) {
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
        break;
    }
    return;
}

void fprintf_quadr_equ_obj(FILE* stream, const struct quadr_equ_obj equ) {
    print_border;
    fprintf(stream, YEL "%lgx²", equ.coeffs.a);

    if (equ.coeffs.b > 0) {
        printf(YEL " + ");
    }    
    fprintf(stream, YEL "%lgx", equ.coeffs.b);

    if (equ.coeffs.c > 0) {
        printf(YEL " + ");
    }
    fprintf(stream, YEL "%lg\n", equ.coeffs.c);
    fprintf(stream, "x1 = %lg\n", equ.roots.x1);
    fprintf(stream, "x2 = %lg\n", equ.roots.x2);
    fprintf_num_solutions(stream, equ.n_roots);
    print_border;
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

bool in_argv(const char samp[], const int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (cmp_strs(samp, argv[i])) {
            return true;
        }
    }
    return false;
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

void example_mode_launch() {
    printf(RED "\n----------------------------> EXAMPLE MODE <----------------------------\n");
    generate_tests_to_file(PATH_EXAMPLE, 1);
    struct quadr_equ_obj example_data[1];
    get_tests_from_file(PATH_EXAMPLE, example_data);
    fprintf_quadr_equ_obj(stdout, example_data[0]);
}

void user_mode_launch() {
    printf(RED "\n-----------------------------> USER MODE <------------------------------\n");
    struct quadr_coeffs coeffs;
    init_quadr_coeffs(&coeffs);
    printf(YEL"# Program for quadratic equation solution\n"
           "# Abryutin I. D. \n\n");
    printf(WHT"# Enter coefficients(a, b, c): ");

    if (scanf_quadr_coeffs(&coeffs) == -1) {
        return;
    }

    debug("a, b, c: %lg, %lg, %lg\n", coeffs.a, coeffs.b, coeffs.c);
    assert(!isnan(coeffs.b));
    assert(!isnan(coeffs.b));
    assert(!isnan(coeffs.c));

    struct quadr_roots roots;
    init_quadr_roots(&roots);
    int n_solutions = quadr_equ_solver(coeffs, &roots);

    debug("sols: %d\n", n_solutions);
    struct quadr_equ_obj equation = INIT_QUADR_EQU_OBJ_STRUCTS(coeffs, roots, n_solutions);
    fprintf_quadr_equ_obj(stdout,equation);
}

void testing_mode_launch() {
    printf(RED "\n----------------------------> TESTING MODE <-----------------------------\n");
    printf("Launch auto or manual test mode? [A/m] ");
    int v1 = getchar();
    if (v1 == '\n' || v1 == 'A' || v1 == 'a') {
        printf(YEL "Generate new tests? [Y/n]: " WHT);
        int v2 = getchar();
        if (v2 == '\n' || v2 == 'Y' || v2 == 'y') {
            printf(YEL"How many tests? (MAX: %ld): " WHT, MAX_N_TESTS);
            size_t n_tests = 0;
            if (!scanf("%ld", &n_tests)) {
                printf(RED "Invalid data format. Enter positive integer" WHT);
                return;
            }
            generate_tests_to_file(PATH_AUTO_TESTS, n_tests);
            quadr_equ_solver_file_testing(PATH_AUTO_TESTS);
        }
    } else {
        quadr_equ_solver_manual_testing(ARR_SIZE(MANUAL_TESTS), MANUAL_TESTS);
    }
    
}

void mode_manager(int argc, char **argv) {
    int user_mode_flag = 0;
	int testing_mode_flag = 0;
	int example_mode_flag = 0;
    const char* short_options = "";
	const struct option long_options[] = {
		{ "user", no_argument, &user_mode_flag, 1 },
		{ "testing", no_argument, &testing_mode_flag, 1 },
		{ "example", no_argument, &example_mode_flag,  1 },
		{ NULL, 0, NULL, 0}
	};

	while (getopt_long(argc, argv, short_options,
		long_options, NULL)!=-1);

    if (example_mode_flag) {
        example_mode_launch();
    }
    if (user_mode_flag) {
        user_mode_launch();
    }
    if (testing_mode_flag) {
        testing_mode_launch();
    }
	
}