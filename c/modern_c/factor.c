// Challenge 9
// Factorization
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Literally the worst algorithm I could write (it's about
// the language not the optimizations of the algorithm)
size_t smallest_prime_divisor(size_t N) {
    for (size_t d = 2; d * d <= N; d += 1) {

        // check if d is prime
        bool is_prime = true;
        for (int i = 2; i * i <= d; i += 1) {
            if (!(d % i)) {
                is_prime = false;
                break;
            }
        }

        // if prime, check divisibilty of N
        if (is_prime && !(N % d)) {
            return d;
        }
    }

    // no smaller divisor found, N must be prime
    return N;
}

int main(int argc, char* argv[argc + 1]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t N = atoi(argv[1]);
    printf("%zu: ", N);

    size_t n = N;
    size_t d = smallest_prime_divisor(N);
    while (n != 1) {
        d = smallest_prime_divisor(n);
        n = n / d;
        printf("%zu ", d);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
