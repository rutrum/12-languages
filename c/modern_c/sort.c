// Challenge 1
// Sorting algorithms

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge(size_t s, size_t m, size_t e, double A[]) {
    int i = s;
    int j = m;
    int k = 0;
    double B[e - s]; // can't initialize here?
    while (i < m && j < e) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            i += 1;
        } else {
            B[k] = A[j];
            j += 1;
        }
        k += 1;
    }

    while (i < m) {
        B[k] = A[i];
        i += 1;
    }
    while (j < e) {
        B[k] = A[j];
        j += 1;
    }

    for (int z = 0; z < e - s; z += 1) {
        A[z + s] = B[z];
    }
}

void mergesort_part(size_t s, size_t e, double A[]) {
    if (e - s < 2) {
        return;
    }
    size_t m = (e - s) / 2 + s;
    mergesort_part(s, m, A);
    mergesort_part(m, e, A);
    merge(s, m, e, A);
}

void mergesort(size_t len, double A[]) {
    mergesort_part(0, len, A);
}

bool is_sorted(size_t len, double A[]) {
    for (int i = 0; i < len - 1; i += 1) {
        if (A[i] > A[i + 1]) return false;
    }
    return true;
}

int main() {
    size_t len = 6;
    double A[] = { 5.2, 1.2, 3, 4, 10, -4 };
    printf("%i\n", is_sorted(len, A));

    mergesort(len, A);
    printf("%i\n", is_sorted(len, A));

    return EXIT_SUCCESS;
}
