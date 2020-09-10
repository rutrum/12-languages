#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void print_f32(float);
void print_f64(double);

int main(int argc, char* argv[argc + 1]) {
    if (argc < 2) {
        printf("Please enter a floating point number\n");
        return EXIT_FAILURE;
    }

    float f = atof(argv[1]);
    double d = atof(argv[1]);

    print_f32(f);
    print_f64(d);

    return EXIT_SUCCESS;
}

void print_f32(float f) {
    int* fi = &f; // to allow for & operator

    for (int i = 31; i >= 0; i -= 1) {
        printf("%i", (*fi & 1 << i) == 0 ? 0 : 1);
        if (i == 32 - 1 || i == 32 - 1 - 8) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_f64(double f) {
    long* fi = &f; // to allow for & operator

    for (int i = 63; i >= 0; i -= 1) {
        printf("%i", (*fi & 1 << i) == 0 ? 0 : 1);
        if (i == 64 - 1 || i == 64 - 1 - 11) {
            printf(" ");
        }
    }
    printf("\n");
}

/* Before I realized I can pull bits straight off the float
typedef struct f32bits f32bits;
struct f32bits {
    bool sign;
    bool exponent[8];
    bool mantissa[23];
};

f32bits into_f32bits(float);
void print_f32bits(f32bits);
void find_mantissa(float, bool[23]);


f32bits into_f32bits(float f) {
    bool sign = 0;
    bool exponent[8] = {0};
    bool mantissa[23] = {0};
    mantissa[0] = 1;

    find_mantissa(f, mantissa);

    f32bits bits = {
        .sign = sign,
        .exponent = {0},
        .mantissa = {0},
    };
    memcpy(bits.exponent, exponent, 8);
    memcpy(bits.mantissa, mantissa, 23);
    return bits;
}

void find_mantissa(float f, bool mantissa[23]) {
    size_t integral = f;
    bool* m_p = mantissa; 


    mantissa[0] = 1;

    size_t q = integral / 2;
    size_t r = integral % 2;

    // Write down mantissa backwards
    while (q != 0) {
        // Write down r
        *m_p = r;
        m_p += 1;

        q = q / 2;
        r = q % 2;
    }

    size_t frac = f - integral;
}

void print_f32bits(f32bits f) {
    printf("%i ", f.sign);
    for (size_t i = 0; i < 8; i += 1) {
        printf("%i", f.exponent[i]);
    }
    printf(" ");
    for (size_t i = 0; i < 23; i += 1) {
        printf("%i", f.mantissa[i]);
    }
    printf("\n");
}
*/
