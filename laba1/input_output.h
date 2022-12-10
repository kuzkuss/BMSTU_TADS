#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#define OK 0
#define INPUT_ERROR 1
#define OVERFLOW_MANTISSA 6
#define OVERFLOW_INT 7
#define SIZE_NUM1 40
#define SIZE_NUM2 32
#define RES_SIZE 60
#include <stdio.h>

int read_numbers(char *num1, char *num2, int *len1, int *len2);
void print_to_normal(const char *num1, const char *num2, const int *res, int start, int exp);

#endif // INPUT_OUTPUT_H
