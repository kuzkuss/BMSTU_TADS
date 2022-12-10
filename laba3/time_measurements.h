#ifndef LABA3_TIME_MEASUREMENTS_H
#define LABA3_TIME_MEASUREMENTS_H

double time_sparse_matrices(type_sparse_matrix matrix1,
                            type_sparse_matrix matrix2, int **result, type_sparse_matrix *sparse_result, int n, int m);
double time_traditional_matrices (int **matrix1, int **matrix2, int n, int m, int **result);
void fill_matrix(int nonzero, int n, int m, int **matrix);
int time_measure(void);

#endif //LABA3_TIME_MEASUREMENTS_H
