#ifndef LABA3_CDIO_H
#define LABA3_CDIO_H
#include <stdio.h>

int input_matrix_dim(int *n, int *m);
int **allocate_matrix(int n, int m);
void free_matrix(int **matrix, int n);
int keyboard_input(int **matrix, int n, int m, int *nonzero);
int file_input(FILE *f, int **matrix1, int **matrix2, int n1, int m1, int n2, int m2, int *nonzero1, int *nonzero2);
void print_whole_matrix(int **matrix, int n, int m);
int create_sparse_type(int **A, int **IA, int **JA, int n, int col);
void sparse_conversion(int **matrix, int n, int m, type_sparse_matrix *sparse_matrix);
void print_sparse_view(const type_sparse_matrix *matrix, int n, int col);
void free_sparse_matrix(int **A, int **IA, int **JA);

#endif //LABA3_CDIO_H
