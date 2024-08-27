#include <stdio.h>
#include <math.h>

#define int long long

int main() {
    long double a, b, c;
    scanf("%lg %lg %lg", &a, &b, &c);
    long double sd = sqrt(b * b - 4 * a * c);
    long double x1 = (-b - sd) / (2 * a);
    long double x2 = (-b + sd) / (2 * a);
    printf("x1: %lg, x2: %lg", x1, x2);
}
