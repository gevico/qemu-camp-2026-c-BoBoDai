#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

// Portable implementations using compiler intrinsics or simple math
int check_add_overflow_asm(unsigned int a, unsigned int b) {
#if defined(__GNUC__) || defined(__clang__)
    unsigned int result;
    int overflow = __builtin_add_overflow(a, b, &result);
    return overflow;
#else
    unsigned int result = a + b;
    return result < a;  // Overflow if result wraps around
#endif
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
#if defined(__GNUC__) || defined(__clang__)
    unsigned int result;
    int overflow = __builtin_sub_overflow(a, b, &result);
    return overflow;
#else
    unsigned int result = a - b;
    return result > a;  // Overflow if result wraps around
#endif
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
#if defined(__GNUC__) || defined(__clang__)
    unsigned int result;
    int overflow = __builtin_mul_overflow(a, b, &result);
    return overflow;
#else
    if (a == 0 || b == 0) return 0;
    return a > UINT_MAX / b;  // Overflow if a * b > UINT_MAX
#endif
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    return b == 0;  // Division by zero
}

int main() {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}
