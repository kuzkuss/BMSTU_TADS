#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

#define N 100
#define LEN_STR 50
#define SIZE_WORDS 4

#define NOT_FOUND -1
#define OK 0
#define INPUT_ERROR 1
#define FILE_ERROR 2
#define KEY_ERROR 3
#define OVERFLOW_STRING 4
#define EMPTY_STRING 5

#define DELIMS "> ,\n"

typedef struct
{
    int duty;
    int length;
} weight_t;

typedef struct
{
    char name;
    int weight;
} vertex_t;

int input(char *filename, vertex_t *vertex, weight_t matrix[][N], int *amount_v);
void export_to_dot(FILE *f_out, const char *graph_name, weight_t matrix[][N], vertex_t *vertex, int n);

#endif // MATRIX_H
