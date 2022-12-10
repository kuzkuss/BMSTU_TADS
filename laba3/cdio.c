#include <stdlib.h>
#include "constants_definitions.h"
#include "cdio.h"
#include "errors.h"

int input_matrix_dim(int *n, int *m) {
    printf("Enter the number of rows of the matrix:\n");
    if (scanf("%d", n) != 1|| *n < 1 || *n > MAX_SIZE)
        return INPUT_ERROR;
    printf("Enter the number of columns of the matrix:\n");
    if (scanf("%d", m) != 1 || *m < 1 || *m > MAX_SIZE)
        return INPUT_ERROR;
    return OK;
}

int **allocate_matrix(int n, int m) {
    int **matrix = calloc(n, sizeof(int *));
    if (!matrix)
        return NULL;
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = calloc(m, sizeof(int));
        if (!matrix[i])
        {
            free_matrix(matrix, n);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; ++i)
        free(matrix[i]);
    free(matrix);
}

int keyboard_input(int **matrix, int n, int m, int *nonzero) {
    printf("Select:\n1-Index input\n2-Whole matrix input\n");
    int choice;
    if ((scanf("%d", &choice) != 1) || choice < 1 || choice > 2)
        return INPUT_ERROR;
    if (choice == 1) {
        while (*nonzero < n * m) {
            int i, j;
            printf("Enter row number (1-%d):\n", n);
            if (scanf("%d", &i) != 1 || i < 1 || i > n)
                return INPUT_ERROR;
            --i;
            printf("Enter column number (1-%d):\n", m);
            if (scanf("%d", &j) != 1 || j < 1 || j > m)
                return INPUT_ERROR;
            --j;
            int cur_val = matrix[i][j];
            printf("Enter the value of the element (to stop input enter not a number):\n");
            if (scanf("%d", &matrix[i][j]) != 1 || matrix[i][j] == 0) {
                scanf("%*[^\n]");
                break;
            }
            if (!cur_val)
                ++(*nonzero);
        }
    }
    else {
        printf("Enter the matrix:\n");
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (scanf("%d", &matrix[i][j]) != 1)
                    return INPUT_ERROR;
                if (matrix[i][j] != 0)
                    ++(*nonzero);
            }
    }
    return OK;
}

int file_input(FILE *f, int **matrix1, int **matrix2, int n1, int m1, int n2, int m2, int *nonzero1, int *nonzero2) {
    int i = 0;
    int j = 0;
    while (i < n1 && j < m1 && fscanf(f, "%d", &matrix1[i][j]) == 1) {
        if (matrix1[i][j] != 0)
            ++(*nonzero1);
        if (++j == m1) {
            j = 0;
            ++i;
        }
    }
    i = 0;
    j = 0;
    while (i < n2 && j < m2 && fscanf(f, "%d", &matrix2[i][j]) == 1) {
        if (matrix2[i][j] != 0)
            ++(*nonzero2);
        if (++j == m2) {
            j = 0;
            ++i;
        }
    }
    if (!feof(f)) {
        if (fgetc(f) != '\n')
            return INPUT_ERROR;
        else
            return OK;
    }
    return OK;
}

void print_whole_matrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int create_sparse_type(int **A, int **IA, int **JA, int n, int col) {
    *A = malloc(n * sizeof(int));
    if (!(*A))
        return ALLOCATE_ERROR;
    *IA = malloc(n * sizeof(int));
    if (!(*IA))
        return ALLOCATE_ERROR;
    *JA = calloc(col, sizeof(int));
    if (!(*JA))
        return ALLOCATE_ERROR;
    return OK;
}

void sparse_conversion(int **matrix, int n, int m, type_sparse_matrix *sparse_matrix) {
    int index = 0;
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            if (matrix[i][j] != 0) {
                sparse_matrix->A[index] = matrix[i][j];
                sparse_matrix->IA[index] = i + 1;
                if (sparse_matrix->JA[j] == 0)
                    sparse_matrix->JA[j] = index + 1;
                ++index;
            }
    if (sparse_matrix->amount != 0)
        sparse_matrix->JA[m] = sparse_matrix->amount + 1;
}

void print_sparse_view(const type_sparse_matrix *matrix, int n, int col) {
    printf("Vector of values of nonzero elements:\n");
    for (int i = 0; i < n; ++i)
        printf("%d ", matrix->A[i]);
    printf("\n");
    printf("Vector of row numbers of nonzero elements:\n");
    for (int i = 0; i < n; ++i)
        printf("%d ", matrix->IA[i]);
    printf("\n");
    printf("The numbers of the nonzero elements at which the column starts:\n");
    for (int i = 0; i < col; ++i)
        printf("%d ", matrix->JA[i]);
    printf("\n");
}

void free_sparse_matrix(int **A, int **IA, int **JA) {
    free(*A);
    free(*IA);
    free(*JA);
    *A = NULL;
    *IA = NULL;
    *JA = NULL;
}

