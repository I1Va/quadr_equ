/*!
    \file
    \brief Header file with basic classes, funtions declaration
*/

#ifndef QUADR_EQU_H
#define QUADR_EQU_H

#include <stdint.h>

#ifdef _DEBUG
#define debug(f_, ...) fprintf(stderr, f_, ##__VA_ARGS__) // stderr,
#else
#define debug(f_, ...)
#endif // _DEBUG

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define INIT_QUADR_COEFFS(a_, b_, c_) {.a = a_, .b = b_, .c = c_}
#define INIT_QUADR_ROOTS(x1_, x2_) {.x1 = x1_, .x2 = x2_}

#define INIT_QUADR_EQU_OBJ(a_, b_, c_, x1_, x2_, n_roots_) \
    { \
    .coeffs = INIT_QUADR_COEFFS(a_, b_, c_), \
    .roots = INIT_QUADR_ROOTS(x1_, x2_), \
    .n_roots = n_roots_ \
    }

#define INIT_QUADR_EQU_OBJ_STRUCTS(coeffs_, roots_, n_roots_) \
    { \
    .coeffs = coeffs_, \
    .roots = roots_, \
    .n_roots = n_roots_ \
    }

#define print_border fprintf(stream, WHT "########################################################################\n")

enum roots_num
{
    INF_SOLUTIONS = -1, 
    NO_SOLUTIONS  = 0,
    ONE_SOLUTION  = 1,
    TWO_SOLUTIONS = 2,
};

enum modes
{
    USER_MODE = 0,
    TESTING_MODE = 1,
    EXAMPLE_MODE = 2,
};

static const double EPS = 1e-4;
static const size_t N_ATTEMPTS = 5;

static const char TESING_ARG[] = "--testing";

/*! \brief Class of quadratic equation coefficients */
struct quadr_coeffs
{
    double a; ///< first coef in quadratic equation before x²
    double b; ///< second coef in quadratic equation before x
    double c; ///< third coef in quadratic equation
};


/*! \brief Class of quadratic equation roots */
struct quadr_roots
{
    double x1; ///< first root
    double x2; ///< second root
};


/*! \brief Class of quadratic equation: coeffs, roots, number os solutions */
struct quadr_equ_obj
{
    struct quadr_coeffs coeffs; ///< coefficients
    struct quadr_roots roots; ///< roots 
    int n_roots; ///< number of roots
};



/* 
#########################################################################
INITIALIZATION FUNCTIONS
#########################################################################
*/



/*! 
    \brief initialization variables to Nan of quadratic equation coefficients class 

    \param[out] coeffs;
*/
void init_quadr_coeffs(struct quadr_coeffs *const coeffs);


/*! 
    \brief initialization variables to Nan of quadratic equation roots class 

    \param[out] roots;
*/
void init_quadr_roots(struct quadr_roots *const roots);



/* 
#########################################################################
ALGORITHM FUNCTIONS
#########################################################################
*/



/*! 
    \brief function solving quadratic equation

    \warning if input values are close to 0 or inf function behavior can be undefined because of 
    limited accuracy of double values compare 
    \param[in] coeffs
    \param[out] roots
    \return n_roots 
*/
int quadr_equ_solver(const struct quadr_coeffs coeffs, struct quadr_roots *const roots);



/* 
#########################################################################
INPUT FUNCTIONS
#########################################################################
*/



/*! 
    \brief function of input quadratic equation coeffs from stdin

    \param[out] coeffs
    \return exit_code
*/
int scanf_quadr_coeffs(struct quadr_coeffs *coeffs);


/*! 
    \brief function of input quadratic equation coeffs from stream

    \param[in] stream 
    \param[out] equ
*/
void fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ);



/* 
#########################################################################
COMPARE FUNCTIONS
#########################################################################
*/



/*! 
    \brief check equality of quadratic equation roots with some error

    takes into account cases of NaN, +inf, -inf
    \param[in] x1, x2
    \return equality
*/
bool cmp_eq(const double x1, const double x2);


/*! 
    \brief check equality of strings 

    \param[in] s1, s2
    \return equality
*/
bool cmp_strs(const char s1[], const char s2[]);


/*! 
    \brief check equality of quad_roots equation with some error

    takes into account cases of NaN, +inf, -inf
    \param[in] r1, r2
    \return equality
*/
bool cmp_eq_roots(const struct quadr_roots r1, const struct quadr_roots r2);



/* 
#########################################################################
OUTPUT FUNCTIONS
#########################################################################
*/



/*! 
    \brief function of root number of quadratic equation output to stream

    \param[in] stream 
    \param[in] n_roots
*/
void fprintf_num_solutions(FILE* stream, const int n_roots);


/*! 
    \brief function of quadr_equ_obj output to stream

    \param[in] stream 
    \param[in] equ
*/
void fprintf_quadr_equ_obj(FILE* stream, const struct quadr_equ_obj equ);



/* 
#########################################################################
RANDOM FUNCTIONS
#########################################################################
*/



/*! 
    \brief Linear congruential generator of random unsigned int numbers

    writes current seed into cur_seed.txt
    uses Borland C/C++ random constants
    \param[out] random_number
*/
unsigned long long my_rand();

/*! 
    \brief Generates random double number
    \param[out] random_number
*/
double my_frand();



/* 
#########################################################################
MODE FUNCTIONS
#########################################################################
*/



/*! 
    \brief processes comand line arguments and manages mode launhes

    \param[in] argc
    \param[in] argv
*/
void mode_manager(int argc, char **argv);


/*! 
    \brief launch example mode

    generate random quadratic equation and solve it
*/
void example_mode_launch();


/*! 
    \brief launch user mode

    user input of quadratic equation coefficients 
    it solution and output
*/
void user_mode_launch();


/*! 
    \brief launch testing mode

    loading tests from file/array
    testing
*/
void testing_mode_launch();


#endif // QUADR_EQU_H
