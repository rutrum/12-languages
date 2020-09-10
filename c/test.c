#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// const* cant change data
// *const cant change pointer
// const*const can't change either
void mutate(size_t len, int const a[len]) {
    a[0] = 1;
    int* b = {0};
}

int main() {
    int a[5] = {0};

    mutate(5, a);

    for (int i = 0; i < 5; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
