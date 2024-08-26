#include <stdio.h>

#include "quadr_config.h"
#include "quadr_equ.h"

// Borland C/C++ random constants
static const unsigned long long seed_mod = (1ll << 32);
static const unsigned long long seed_mult = 22695477;
static const unsigned long long seed_add = 1;


unsigned long long cong_rand() {
    FILE* f_seed_read = fopen(PATH_CUR_SEED, "r");
    if (f_seed_read == NULL) {
        fprintf(stderr, "Failed to open %s", PATH_CUR_SEED);
        return 0;
    }

    unsigned long long seed = 0;
    fscanf(f_seed_read, "%lld", &seed);
    fclose(f_seed_read);

    seed = (seed * seed_mult + seed_add) % seed_mod;

    FILE* f_seed_write = fopen(PATH_CUR_SEED, "w");
    if (f_seed_write == NULL) {
        fprintf(stderr, "Failed to open %s", PATH_CUR_SEED);
        return 0;
    }
    fprintf(f_seed_write, "%lld", seed);
    fclose(f_seed_write);

    return seed;
}

double cong_frand() {
    unsigned long long seed = cong_rand();
    return (double) seed / seed_mod;
}
