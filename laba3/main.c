#include "constants_definitions.h"
#include "cdio.h"
#include "errors.h"
#include "addition.h"
#include "time_measurements.h"

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    if (argc > 2) {
        printf("Key error.\n");
        return KEY_ERROR;
    }
    int rc = 0;
    int n1 = 0, m1 = 0;
    int n2 = 0, m2 = 0;
    int **matrix_1 = NULL;
    int **matrix_2 = NULL;
    type_sparse_matrix sparse_matrix_1 = {};
    type_sparse_matrix sparse_matrix_2 = {};
    printf("Addition of two matrices:\n");
    if (argc == 2) {
        FILE *f_in;
        f_in = fopen(argv[1], "r");
        if (!f_in) {
            printf("File open error.\n");
            return FILE_ERROR;
        }
        if (fscanf(f_in, "%d%d", &n1, &m1) != 2 || n1 < 1 || n1 > 1000 || m1 < 1 || m1 > 1000) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        matrix_1 = allocate_matrix(n1, m1);
        if (!matrix_1) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        if (fscanf(f_in, "%d%d", &n2, &m2) != 2 || n2 < 1 || n2 > 1000 || m2 < 1 || m2 > 1000) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        if (n1 != n2 || m1 != m2) {
            printf("Incorrect dimension of matrices.\n");
            return DIM_ERROR;
        }
        matrix_2 = allocate_matrix(n2, m2);
        if (!matrix_2) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        rc = file_input(f_in, matrix_1, matrix_2 ,n1, m1, n2, m2, &sparse_matrix_1.amount, &sparse_matrix_2.amount);
        if (rc == INPUT_ERROR) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        else if (rc == ALLOCATE_ERROR) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        rc = create_sparse_type(&sparse_matrix_1.A, &sparse_matrix_1.IA, &sparse_matrix_1.JA, sparse_matrix_1.amount, m1 + 1);
        if (rc) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
		
        sparse_conversion(matrix_1, n1, m1, &sparse_matrix_1);
        rc = create_sparse_type(&sparse_matrix_2.A, &sparse_matrix_2.IA, &sparse_matrix_2.JA, sparse_matrix_2.amount, m2 + 1);
        if (rc) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        sparse_conversion(matrix_2, n2, m2, &sparse_matrix_2);
        fclose(f_in);
    }
    else {
        printf("Enter the dimension of the first matrix:\n");
        rc = input_matrix_dim(&n1, &m1);
        if (rc) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        matrix_1 = allocate_matrix(n1, m1);
        if (!matrix_1) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        if (keyboard_input(matrix_1, n1, m1, &sparse_matrix_1.amount) != OK) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        rc = create_sparse_type(&sparse_matrix_1.A, &sparse_matrix_1.IA, &sparse_matrix_1.JA, sparse_matrix_1.amount,
                           m1 + 1);
        if (rc) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        sparse_conversion(matrix_1, n1, m1, &sparse_matrix_1);
        printf("Enter the dimension of the second matrix:\n");
        rc = input_matrix_dim(&n2, &m2);
        if (rc) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        if (n1 != n2 || m1 != m2) {
            printf("Incorrect dimension of matrices.\n");
            return DIM_ERROR;
        }
        matrix_2 = allocate_matrix(n2, m2);
        if (!matrix_2) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        if (keyboard_input(matrix_2, n2, m2, &sparse_matrix_2.amount) != OK) {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        rc = create_sparse_type(&sparse_matrix_2.A, &sparse_matrix_2.IA, &sparse_matrix_2.JA, sparse_matrix_2.amount,
                           m2 + 1);
        if (rc) {
            printf("Memory allocation error.\n");
            return ALLOCATE_ERROR;
        }
        sparse_conversion(matrix_2, n2, m2, &sparse_matrix_2);
    }
    int **result = allocate_matrix(n1, m1);
    if (!result) {
        printf("Memory allocation error.\n");
        return ALLOCATE_ERROR;
    }
    type_sparse_matrix sparse_result = {};
    int choice = -1;
    while (choice) {
        printf("Choose an action:\n1-View standard matrices\n"
               "2-View matrices in sparse view\n"
               "3-Sparse matrix addition\n"
               "4-Standard matrix addition\n"
               "5-Comparison of time and memory when working with two algorithms\n"
               "0-Exit\n");
        printf("Enter a choice:\n");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input.\n");
            choice = -1;
            scanf("%*[^\n]");
            continue;
        }
        switch (choice) {
            case 0:
                break;
            case 1:
                printf("Matrix 1:\n");
                print_whole_matrix(matrix_1, n1, m1);
                printf("Matrix 2:\n");
                print_whole_matrix(matrix_2, n2, m2);
                break;
            case 2:
                printf("Matrix 1 in sparse view:\n");
                print_sparse_view(&sparse_matrix_1, sparse_matrix_1.amount, m1);
                printf("Matrix 2 in sparse view:\n");
                print_sparse_view(&sparse_matrix_2, sparse_matrix_2.amount, m2);
                break;
            case 3:
                addition_sparse_matrices(sparse_matrix_1, sparse_matrix_2, result, &sparse_result.amount, m1);

                rc = create_sparse_type(&sparse_result.A, &sparse_result.IA, &sparse_result.JA, sparse_result.amount,
                                   m1 + 1);
                if (rc) {
                    printf("Memory allocation error.\n");
                    return ALLOCATE_ERROR;
                }
                sparse_conversion(result, n1, m1, &sparse_result);
                printf("Result in sparse view:\n");
                print_sparse_view(&sparse_result, sparse_result.amount, m1);
				free_sparse_matrix(&sparse_result.A, &sparse_result.IA, &sparse_result.JA);
                sparse_result.amount = 0;
                for (int i = 0; i < n1; ++i)
                    for (int j = 0; j < m1; ++j)
                        result[i][j] = 0;
                break;
            case 4:
                addition_traditional_matrices(result, matrix_1, matrix_2, n1, m1);
                printf("Result:\n");
                print_whole_matrix(result, n1, m1);
                for (int i = 0; i < n1; ++i)
                    for (int j = 0; j < m1; ++j)
                        result[i][j] = 0;
                break;
            case 5:
                rc = time_measure();
                if (rc == ALLOCATE_ERROR) {
                    printf("Memory allocation error.\n");
                    return ALLOCATE_ERROR;
                }
                else if (rc == DIM_ERROR) {
                    printf("Incorrect dimension of matrices.\n");
                    return DIM_ERROR;
                }
                break;
        }
    }
    free_matrix(matrix_1, n1);
    free_matrix(matrix_2, n2);
    free_sparse_matrix(&sparse_matrix_1.A, &sparse_matrix_1.IA, &sparse_matrix_1.JA);
    free_sparse_matrix(&sparse_matrix_2.A, &sparse_matrix_2.IA, &sparse_matrix_2.JA);
    free_matrix(result, n1);
    return 0;
}
