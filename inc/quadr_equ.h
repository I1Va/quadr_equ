/*!
    \file
    \brief Header file with basic classes, funtions declaration
*/


#ifndef QUADR_EQU_H
#define QUADR_EQU_H


#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#ifdef _DEBUG
#define debug(str_, ...) fprintf_red(stderr, "[%s: %d] " str_, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define debug(str_, ...)
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

#define print_border() fprintf(stdout, WHT "########################################################################\n")

enum roots_num
{
    INF_SOLUTIONS = -1, 
    NO_SOLUTIONS  = 0,
    ONE_SOLUTION  = 1,
    TWO_SOLUTIONS = 2,
    INIT_SOLUTIONS = -2,
};

enum modes
{
    USER_MODE = 0,
    TESTING_MODE = 1,
    EXAMPLE_MODE = 2,
};

enum return_states
{
    RETURN_SUCCESS = 0,
    RETURN_FAILURE = -1,
};

static const double EPS = 1e-4;
static const size_t N_ATTEMPTS = 5;
static const size_t MAX_STRING_SIZE = 100;

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
    \brief initialization variables to Nan of quadr_coeffs coefficients class 

    \param[out] coeffs;
*/
void init_quadr_coeffs(struct quadr_coeffs *const coeffs);


/*! 
    \brief initialization variables to Nan of quadr_roots class 

    \param[out] roots;
*/
void init_quadr_roots(struct quadr_roots *const roots);


/*! 
    \brief initialization variables of quadr_obj class 

    \param[out] roots;
*/
void init_quadr_obj(struct quadr_equ_obj *equation);


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
    \return return_code
*/
int scanf_quadr_coeffs(struct quadr_coeffs *coeffs);


/*! 
    \brief function of input quadratic equation coeffs from stream

    \param[in] stream 
    \param[out] equ
    \return return_code
*/
int fscanf_quadr_equ_obj(FILE *stream, struct quadr_equ_obj *equ);



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
bool eq_doubles(const double x1, const double x2);

/*! 
    \brief check equality of quad_roots class objects equation with some error

    takes into account cases of NaN, +inf, -inf
    \param[in] r1, r2
    \return equality
*/
bool eq_doubles_roots(const struct quadr_roots r1, const struct quadr_roots r2);



/* 
#########################################################################
OUTPUT FUNCTIONS
#########################################################################
*/



/*! 
    \brief function of root number of quadratic equation output to stream

    \param[in] stream 
    \param[in] n_roots
    \return return_code
*/
int fprintf_num_solutions(FILE* stream, const int n_roots);


/*! 
    \brief function of quadr_equ_obj output to stream

    \param[in] stream 
    \param[in] equ
    \return return_code
*/
int fprintf_quadr_equ_obj(FILE* stream, const struct quadr_equ_obj equ);



/* 
#########################################################################
RANDOM FUNCTIONS
#########################################################################
*/



/*! 
    \brief Linear congruential generator of random unsigned int numbers

    writes current seed into cur_seed.txt
    uses Borland C/C++ random constants
    \return random number
*/
unsigned long long cong_rand();

/*! 
    \brief Generates random double number
    \return random double number
*/
double cong_frand();



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
    \return return_code
*/
int example_mode_launch();


/*! 
    \brief launch user mode

    user's input of quadratic equation coefficients, it solution and output
    \return return_code
*/
int user_mode_launch();


/*! 
    \brief launch testing mode

    loading tests from file/array, testing
    \return return_code
*/
int testing_mode_launch();


/*! 
    \brief remove spaces from string
    \param[out] string
*/
int parsing_mode_launch();



/* 
#########################################################################
STRING PROCESSTING FUNCTIONS
#########################################################################
*/



/*! 
    \brief remove spaces from string
    \param[out] string
*/
void remove_spaces(char *start_ptr);



/*! 
    \brief read line from stdin stream
    \param[out] string
*/
void getline(char *ptr);



/* 
#########################################################################
STRING PROCESSTING FUNCTIONS
#########################################################################
*/


/*! 
    \brief check string prefix for the presence of a lexemes: x^2, x**2
    \return pointer to first symbol after lexeme.
    
    \return if lexeme hasn't found return NULL
*/
char* check_lexem_x2(char *s1);


/*! 
    \brief read quadratic equation coefficient lexeme from string prefix
    \return pointer to first symbol after lexeme
    
    \return if lexeme hasn't found return NULL
*/
char* get_coeff_lexem(double *val, char* ptr);


/*! 
    \brief check string prefix for the presence of a lexemes: x
    \return pointer to first symbol after lexeme.
    
    \return if lexeme hasn't found return NULL
*/
char* check_lexem_x(char *string_ptr);


#endif // QUADR_EQU_H
