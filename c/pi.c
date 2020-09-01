// Modern C
// Challenge 3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int N = 5;
    double eps = pow(0.1, N);
    printf("%f\n", eps);
    
    double last = 0.0;
    double approx = 10.0;

    int i = 0;

    while (fabs(approx - last) > eps) {
        last = approx;
        approx = 0.0;
        for (int j = 0; j <= i; j += 1) {
            approx += pow(-3, -j) / (2 * j + 1);
        }
        approx *= sqrt(12);
        i++;
    }

    printf("%f\n", approx);

    return EXIT_SUCCESS;
}
