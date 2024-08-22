#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#include "quadr_equ.h"

const char PATH_SEED_CONF[] = "C:/Users/User/Documents/qu_eq_sol/quadr_equ/quadr_tests/seed_config.txt";
const char PATH_SEED_CUR_VAL[] = "C:/Users/User/Documents/qu_eq_sol/quadr_equ/quadr_tests/seed_cur_val.txt";

int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots);

double frand();

int get_seed();

long f_get_num(FILE* fp);

int simple_quadr_solve(const quadr_coeffs coeffs, quadr_roots *roots) {
    double a = coeffs.a, b = coeffs.b, c = coeffs.c;
    if (fabs(a) < EPS) { // a = 0
        if (fabs(b) < EPS) { // b = 0
            if (fabs(c) < EPS) { // c = 0
                roots->x1 = NAN;
                roots->x2 = NAN;
                return INF_SOLUTIONS;
            } else { // a, b = 0; c != 0
                roots->x1 = NAN;
                roots->x2 = NAN;
                return NO_SOLUTIONS;
            }
        } else { // a = 0, b != 0
            if (fabs(c) < EPS) { // c = 0
                roots->x1 = 0.0;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            } else { // c != 0
                roots->x1 = -c / b;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            }
        }
    } else { // a != 0
        if (fabs(b) < EPS) { // b = 0
            if (fabs(c) < EPS) { // c = 0;
                roots->x1 = 0.0;
                roots->x2 = NAN;
                return ONE_SOLUTION;
            } else { // c != 0
                double k = -c / a;
                if (k < 0) {
                    roots->x1 = NAN;
                    roots->x2 = NAN;
                    return NO_SOLUTIONS;
                } else {
                    double sqrt_k = sqrt(k);
                    roots->x1 = -sqrt_k;
                    roots->x2 = sqrt_k;
                    return TWO_SOLUTIONS;
                }
            }
        } else { // b != 0
            if (fabs(c) < EPS) {
                roots->x1 = -b / a;
                roots->x2 = 0.0;
                return TWO_SOLUTIONS;
            } else { // c != 0
                double discr = b * b - 4 * a * c;
                if (fabs(discr) < EPS) {
                    roots->x1 = -b / (2 * a);
                    roots->x2 = NAN;
                    return ONE_SOLUTION;
                } else if (discr < 0) {
                    roots->x1 = NAN;
                    roots->x2 = NAN;
                    return NO_SOLUTIONS;
                } else { // discr > 0
                    double sqrt_discr = sqrt(discr);
                    roots->x1 = (-b - sqrt_discr) / (2 * a);
                    roots->x2 = (-b + sqrt_discr) / (2 * a);
                    return TWO_SOLUTIONS;
                }
            }

        }
    }
}

double frand() {
    return (double) (rand()) / RAND_MAX;
}

long f_getline_only_num(FILE* fp) { /// FIXME: можно заменить на getline
    char str[BUFSIZ] = {0};
    size_t str_idx = 0;
    for (size_t i = 0; i < BUFSIZ; i++) {
        int v = fgetc(fp);
        if (v == '\n' || v == EOF) {
            break;
        }
        if (isdigit(v)) {
            str[str_idx++] = (char) v; /// FIXME: warnings: решить через (char) v
        } else {
            continue; // Пропускаем символы
        }
    }
    return atoi(str); /// FIXME: заменить atoi на strtol
}

int get_seed() {
    // int seed_step = 0;
    // int seed_mod = 0;
    // int seed_cur_val = 0;

    // FILE *f_seed_conf = fopen(PATH_SEED_CONF, "r");
    // if (f_seed_conf == NULL) {
    //     fprintf(stderr, RED "error: %s [%s]\n" WHT, strerror(errno), PATH_SEED_CONF);
    //     return -1;
    // }
    // seed_step = f_get_num(f_seed_conf);
    // seed_mod = f_get_num(f_seed_conf);
    // fclose(f_seed_conf);
    // fprintf(stderr, RED "error: %s [%s]\n" WHT, strerror(errno), PATH_SEED_CONF);
    // FILE *f_seed_cur_val = fopen(PATH_SEED_CUR_VAL, "r");
    //  if (f_seed_cur_val == NULL) {
    //     fprintf(stderr, RED "failed to open seed_cur_val file for reading" WHT);
    //     return -1;
    // } else {
    //     seed_cur_val = f_get_num(f_seed_cur_val);
    // }
    // fclose(f_seed_cur_val);

    // f_seed_cur_val = fopen(PATH_SEED_CUR_VAL, "w");
    //  if (f_seed_cur_val == NULL) {
    //     printf(RED "failed to open seed_cur_val file for writing" WHT);
    //     return -1;
    // } else {
    //     char str_seed_cur_val[SEED_STR_MAX_SIZE];
    //     itoa(seed_cur_val, str_seed_cur_val, 10);
    //     printf("seed: %s\n", str_seed_cur_val);
    //     printf("seed1: %c\n", str_seed_cur_val[0]);
    //     int str_seed_cur_val_idx = 0;
    //     while (1) {
    //         char v = str_seed_cur_val[str_seed_cur_val_idx++];
    //         if (v == '\n' || v == EOF) {
    //             break;
    //         }
    //         printf("cur_char: %d\n", v);
    //         // fputc(v, f_seed_cur_val);
    //     }
        
    // }
    // fclose(f_seed_cur_val);

}
int main() {
    printf(YEL "TESTS_MANAGER IS LAUNCHED\n" WHT);
    get_seed();
    // srand(get_seed());
    // printf("random double = %lg", frand());

}
