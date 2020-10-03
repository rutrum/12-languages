#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

// const* cant change data
// *const cant change pointer
// const*const can't change either
void mutate(size_t len, int a[len]) {
    a[0] = 1;
    int* b = {0};
}

void birthday(int* age) {
    *age += 1;
}

int main() {
    int a[5] = {0};

    mutate(5, a);

    //for (int i = 0; i < 5; i++) {
    //    printf("%i ", a[i]);
    //}
    //printf("\nEnter a num: ");

    int b = 0;
    /*
    int result = scanf("%i", &b);
    if (!!result) {
        printf("double your num: %i\n", b * 2);
    } else {
        printf("thats not an integer!\n");
    }
    */
    char letter = '\0';
    int success = read(STDIN_FILENO, &letter, 1);
    if (!success) return EXIT_FAILURE;
    printf("...You typed %c\n", letter);

    /*
    int age = 20;
    birthday(&age);
    printf("%i", age);

    char* names[3] = {"asdf", "ab", "c"};
    printf("%s", names[0]);
    */

    return EXIT_SUCCESS;
}
