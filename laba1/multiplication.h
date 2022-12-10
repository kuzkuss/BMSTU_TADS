#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#define OK 0
#define INPUT_ERROR 1
#define OVERFLOW_EXP 2
#define EMPTY_MANTISSA 3
#define EMPTY_EXP 4
#define EMPTY_INT 5
#define OVERFLOW_MANTISSA 6
#define RES_SIZE 60
#define SIZE_EXP 7
#define SIZE_NUM2 32
#define SIZE_NUM1 40

int search_exp_point(char *num, int *len, int *count_exp, int *count_point, int *index_exp, int *index_point);
int multiplication(int *res, const char *num1, const char *num2, int len2, int start);
int search_start_and_exp(int *res, const char *num1, int len1, int count_e, int count_point, int *start, int *exp, int index_e, int index_point);

#endif // MULTIPLICATION_H
