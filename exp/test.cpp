#include <stdio.h>
#include <math.h>

const char path_a[] = "/home/ivana/projects/quadr_equ/exp/a.txt";

int main() {
    FILE *fp = fopen(path_a, "r");
    if (fp != NULL) {
        int a = 0, b = 0, c = 0, d = 0;
        fscanf(fp, "%d %d %d %d", &a, &b, &c, &d);
        printf("%d %d %d %d", a, b, c, d);
    } else {
        printf("ERROR\n");
    }

}