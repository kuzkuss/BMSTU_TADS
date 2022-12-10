#ifndef LABA3_ADDITION_H
#define LABA3_ADDITION_H

void addition_sparse_matrices (type_sparse_matrix matrix1, type_sparse_matrix matrix2,
                               int **result, int *nonzero, int n);
void addition_traditional_matrices (int **result, int **matrix1, int **matrix2, int n, int m);

#endif //LABA3_ADDITION_H
