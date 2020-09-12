#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

// Note: This takes advantage of how my machine defines "long" and "int" but
// could fail on other applications.  Also see CHAR_BIT  and UCHAR_MAX for
// unsigned char array casting.

typedef struct Args Args;
struct Args {
    bool sign;
    bool exponent;
    bool mantissa;
};

Args parse_args(int argc, char* argv[argc + 1]);
void print_f32(float);
void print_f64(double);

int main(int argc, char* argv[argc + 1]) {
    if (argc < 2) {
        printf("Please enter a floating point number\n");
        return EXIT_FAILURE;
    }

    Args a = parse_args(argc, argv);

    // do something with a

    float f = atof(argv[1]);
    double d = atof(argv[1]);

    print_f32(f);
    print_f64(d);

    return EXIT_SUCCESS;
}

Args parse_args(int argc, char* argv[argc + 1]) {
    Args a = {
        .sign = true,
        .exponent = true,
        .mantissa = true,
    };
    return a;
}

void print_f32(float f) {
    unsigned char* cs = (unsigned char*)&f;

    for (size_t i = 0; i < sizeof(float); i++) {
        unsigned char c = cs[sizeof(float) - i - 1];
        for (size_t j = 0; j < CHAR_BIT; j++) {
            size_t ord = CHAR_BIT * i + j;
            if (ord == 1 || ord == 1 + 8) {
                printf(" ");
            }

            size_t b = (c & 1 << (CHAR_BIT - j - 1)) == 0 ? 0 : 1;
            printf("%zu", b);
        }
    }
    printf("\n");
}

// Don't cast to types you shouldn't, don't use void*,
// just cast to unsigned char* because its actually allowed; lessons learned
void print_f64(double f) {
    unsigned char* cs = (unsigned char*)&f;

    for (size_t i = 0; i < sizeof(double); i++) {
        unsigned char c = cs[sizeof(double) - i - 1];
        for (size_t j = 0; j < CHAR_BIT; j++) {
            size_t ord = CHAR_BIT * i + j;
            if (ord == 1 || ord == 1 + 11) {
                printf(" ");
            }

            size_t b = (c & 1 << (CHAR_BIT - j - 1)) == 0 ? 0 : 1;
            printf("%zu", b);
        }
    }
    printf("\n");

    /*
    long* fi = (void*)&f; // to allow for & operator
    printf("\n%lu %lu\n", sizeof(long), sizeof(double));

    // wrong but not sure why (figured it out)
    for (int i = 63; i >= 0; i -= 1) {
        printf("%i", (*fi & 1 << i) == 0 ? 0 : 1);
        if (i == 64 - 1 || i == 64 - 1 - 11) {
            printf(" ");
        }
    }
    printf("\n");
    */
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
