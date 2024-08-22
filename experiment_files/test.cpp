#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

const char path_a[] = "/home/ivana/projects/quadr_equ/experiment_files/a.txt";

int main() {
    FILE *fp = fopen(path_a, "w");
    if (fp != NULL) {
        double a = NAN;
        fprintf(fp, "%lg", a);
    } else {
        printf("ERROR\n");
    }
    fclose(fp);

}