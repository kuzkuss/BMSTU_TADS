#include "constants_definitions.h"
#include "time_measurements.h"
#include "addition.h"
#include "cdio.h"
#include "errors.h"
#include <time.h>
#include <stdlib.h>

double time_sparse_matrices(type_sparse_matrix matrix1,
                            type_sparse_matrix matrix2, int **result, type_sparse_matrix *sparse_result, int n, int m) {
    clock_t start, finish;
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        start = clock();
        addition_sparse_matrices (matrix1, matrix2, result, &sparse_result->amount, m);
        finish = clock();
        sum += finish - start;
    }

    return sum / N / CLOCKS_PER_SEC * 1000000;
}

double time_traditional_matrices (int **matrix1, int **matrix2, int n, int m, int **result) {
    clock_t start, finish;
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        start = clock();
        addition_traditional_matrices(result, matrix1, matrix2, n, m);
        finish = clock();
        sum += finish - start;
    }
    return sum / N / CLOCKS_PER_SEC * 1000000;
}

void fill_matrix(int nonzero, int n, int m, int **matrix) {
    int i = 0;
    int index_i, index_j;
    while (i < nonzero) {
        index_i = rand() % n;
        index_j = rand() % m;
        if (matrix[index_i][index_j] == 0) {
            matrix[index_i][index_j] = rand() % 50 + 1;
            ++i;
        }
    }
}

int time_measure(void) {
    int n1 = 0, m1 = 0;
    int n2 = 0, m2 = 0;
    printf("Enter the dimension of the first matrix:\n");
    input_matrix_dim(&n1, &m1);
    printf("Enter the dimension of the second matrix:\n");
    input_matrix_dim(&n2, &m2);
    if (n1 != n2 || m1 != m2)
        return DIM_ERROR;
    int **matrix1 = allocate_matrix(n1, m1);
    int **matrix2 = allocate_matrix(n2, m2);
    int **result = allocate_matrix(n1, m1);
    if (!matrix1 || !matrix2 || !result)
        return ALLOCATE_ERROR;
    printf("┌──────────┬────────────────────┬──────────────────────────────────┬"
           "──────────────────────┬─────────────────────────────────────┐\n");
    printf("│ Percents │ Time with standard │  Time with an algorithm using a  │"
           " Memory with standard │   Memory with an algorithm using a  │\n");
    printf("│          │   algorithm, us    │ sparse matrix storage method, us │"
           "   algorithm, bytes   │ sparse matrix storage method, bytes │\n");
    for (int percents = 0; percents <= 100; percents += 10) {

        printf("├──────────┼────────────────────┼──────────────────────────────────┼"
               "──────────────────────┼─────────────────────────────────────┤\n");

        type_sparse_matrix sparse_matrix1 = {};
        type_sparse_matrix sparse_matrix2 = {};
        type_sparse_matrix sparse_result = {};

        int nonzero = n1 * m1 * percents / 100;

        fill_matrix(nonzero, n1, m1, matrix1);
        fill_matrix(nonzero, n2, m2, matrix2);

        int rc = create_sparse_type(&sparse_matrix1.A, &sparse_matrix1.IA, &sparse_matrix1.JA, nonzero, m1 + 1);
        if (rc)
            return rc;
        sparse_matrix1.amount = nonzero;
        sparse_conversion(matrix1, n1, m1, &sparse_matrix1);

        rc = create_sparse_type(&sparse_matrix2.A, &sparse_matrix2.IA, &sparse_matrix2.JA, nonzero, m2 + 1);
        if (rc)
            return rc;
        sparse_matrix2.amount = nonzero;
        sparse_conversion(matrix2, n2, m2, &sparse_matrix2);

        printf("│%-10d│%-20lf│", percents,
               time_traditional_matrices(matrix1, matrix2, n1, m1, result));

        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                result[i][j] = 0;

        printf("%-34lf│%-22zu│%-37zu│\n",
               time_sparse_matrices(sparse_matrix1, sparse_matrix2, result, &sparse_result, n1, m1),
               3 * (sizeof (int **) + sizeof (int *) * n1 + sizeof(int) * m1 * n1),
               3 * (sizeof (type_sparse_matrix) + nonzero * 2 * sizeof(int) + (m1 + 1) * sizeof(int)));

        free_sparse_matrix(&sparse_matrix1.A, &sparse_matrix1.IA, &sparse_matrix1.JA);
        free_sparse_matrix(&sparse_matrix2.A, &sparse_matrix2.IA, &sparse_matrix2.JA);

        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                result[i][j] = 0;
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                matrix1[i][j] = 0;
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                matrix2[i][j] = 0;
    }
    printf("└──────────┴────────────────────┴──────────────────────────────────┴"
           "──────────────────────┴─────────────────────────────────────┘\n");
    free_matrix(matrix1, n1);
    free_matrix(matrix2, n2);
    free_matrix(result, n1);
    return OK;
}
