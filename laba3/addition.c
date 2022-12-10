#include "constants_definitions.h"
#include "addition.h"

void addition_sparse_matrices (type_sparse_matrix matrix1, type_sparse_matrix matrix2, int **result, int *nonzero, int n) {
    for (int i = 0; i < n; ++i) {
        while (i < n && matrix1.JA[i] == 0)
            ++i;
        int index_j = i;
        int start = matrix1.JA[i] - 1;
        while (i < n && matrix1.JA[i + 1] == 0)
            ++i;
        if (i == n)
            break;
        int finish = matrix1.JA[i + 1] - 1;
        for (int j = start; j < finish; ++j) {
            result[matrix1.IA[j] - 1][index_j] = matrix1.A[j];
            ++(*nonzero);
        }
    }
    for (int i = 0; i < n; ++i) {
        while (i < n && matrix2.JA[i] == 0)
            ++i;
        int index_j = i;
        int start = matrix2.JA[i] - 1;
        while (i < n && matrix2.JA[i + 1] == 0)
            ++i;
        if (i == n)
            break;
        int finish = matrix2.JA[i + 1] - 1;
        for (int j = start; j < finish; ++j) {
            if (result[matrix2.IA[j] - 1][index_j] == 0)
                ++(*nonzero);
            result[matrix2.IA[j] - 1][index_j] += matrix2.A[j];
        }
    }
}

void addition_traditional_matrices (int **result, int **matrix1, int **matrix2, int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            result[i][j] = matrix1[i][j] + matrix2[i][j];
}
