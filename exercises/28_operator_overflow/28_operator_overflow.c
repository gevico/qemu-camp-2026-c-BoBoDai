#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "add %2, %0;\n"
        "jnc 1f;\n"
        "mov $1, %1;\n"
        "jmp 2f;\n"
        "1:\n"
        "mov $0, %1;\n"
        "2:\n"
        : "+r" (a), "=r" (carry)
        : "r" (b)
        : "cc"
    );
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "sub %2, %0;\n"
        "jnc 1f;\n"
        "mov $1, %1;\n"
        "jmp 2f;\n"
        "1:\n"
        "mov $0, %1;\n"
        "2:\n"
        : "+r" (a), "=r" (carry)
        : "r" (b)
        : "cc"
    );
    return carry;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int high_bits;
    unsigned char overflow;
    __asm__ volatile(
        "mul %2;\n"
        "test %edx, %edx;\n"
        "jz 1f;\n"
        "mov $1, %0;\n"
        "jmp 2f;\n"
        "1:\n"
        "mov $0, %0;\n"
        "2:\n"
        : "=r" (overflow)
        : "a" (a), "r" (b)
        : "edx", "cc"
    );
    return overflow;
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char is_div_zero;
    __asm__ volatile(
        "test %2, %2;\n"
        "jz 1f;\n"
        "mov $0, %1;\n"
        "jmp 2f;\n"
        "1:\n"
        "mov $1, %1;\n"
        "2:\n"
        : "+r" (a), "=r" (is_div_zero)
        : "r" (b)
        : "cc"
    );
    return is_div_zero;
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
