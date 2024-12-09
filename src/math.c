

#include "math.h"
#include <stddef.h>

float fmodf(float x, float y) {
    if (y == 0.0f) {
        // Handle division by zero; return NaN (Not a Number)
        return 0.0f / 0.0f; // This generates a NaN
    }

    // Calculate the remainder of x divided by y
    float quotient = x / y;
    float remainder = x - ((int)quotient) * y;

    // Adjust remainder for negative values
    if (remainder < 0.0f) {
        remainder += (y > 0.0f) ? y : -y;
    }

    return remainder;
}

// Compute absolute value of a float
float fabsf(float a) {
    return a < 0.0f ? -a : a;
}

// Compute minimum of two floats
float fmin(float a, float b) {
    return a < b ? a : b;
}

// Compute maximum of two floats
float fmax(float a, float b) {
    return a > b ? a : b;
}

// Compute floor of a float (round down)
float floor(float a) {
    int i = (int)a;
    return (a < 0.0f && a != i) ? i - 1 : i;
}

// Compute ceiling of a float (round up)
float ceil(float a) {
    int i = (int)a;
    return (a > 0.0f && a != i) ? i + 1 : i;
}

// Compute square root using Newton's method
float sqrtf(float a) {
    if (a < 0.0f) return 0.0f; // Naive handling of negative inputs
    float x = a;
    float prev;
    do {
        prev = x;
        x = 0.5f * (x + a / x);
    } while (fabsf(x - prev) > 1e-6f); // Tolerance for convergence
    return x;
}

// Compute cosine using Taylor series expansion
float cos(float a) {
    a = fmodf(a, 2 * PI); // Reduce the angle
    float term = 1.0f, sum = 0.0f, x2 = a * a;
    int sign = 1;
    for (int n = 0; n < 10; n++) { // 10 terms of the Taylor series
        sum += sign * term;
        term *= x2 / ((2 * n + 1) * (2 * n + 2));
        sign = -sign;
    }
    return sum;
}

// Compute sine using Taylor series expansion
float sin(float a) {
    a = fmodf(a, 2 * PI); // Reduce the angle
    float term = a, sum = 0.0f, x2 = a * a;
    int sign = 1;
    for (int n = 0; n < 10; n++) { // 10 terms of the Taylor series
        sum += sign * term;
        term *= x2 / ((2 * n + 2) * (2 * n + 3));
        sign = -sign;
    }
    return sum;
}

// Compute tangent using sine and cosine
float tan(float a) {
    float cos_val = cos(a);
    if (cos_val == 0.0f) {
        // Return a large value to represent infinity
        return (a > 0.0f) ? 1e30f : -1e30f;
    }
    return sin(a) / cos_val;
}

// Swap two elements in memory
static void swap(void *a, void *b, size_t size) {
    unsigned char temp;
    unsigned char *x = (unsigned char *)a;
    unsigned char *y = (unsigned char *)b;

    while (size--) {
        temp = *x;
        *x++ = *y;
        *y++ = temp;
    }
}

// Partition the array and return the pivot index
static int partition(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    unsigned char *array = (unsigned char *)base;
    unsigned char *pivot = array + (nmemb - 1) * size;
    size_t i = 0;

    for (size_t j = 0; j < nmemb - 1; ++j) {
        if (compar(array + j * size, pivot) < 0) {
            swap(array + i * size, array + j * size, size);
            i++;
        }
    }

    swap(array + i * size, pivot, size);
    return i;
}

// Recursive quicksort implementation
static void quicksort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    if (nmemb <= 1) {
        return; // Base case: array of size 0 or 1 is already sorted
    }

    int pivot_index = partition(base, nmemb, size, compar);

    quicksort(base, pivot_index, size, compar);
    quicksort((unsigned char *)base + (pivot_index + 1) * size, nmemb - pivot_index - 1, size, compar);
}

// Public interface for `qsort`
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    if (base == NULL || compar == NULL || size == 0 || nmemb == 0) {
        return; // Handle invalid input
    }

    quicksort(base, nmemb, size, compar);
}
