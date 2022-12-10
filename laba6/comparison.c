#include <time.h>
#include <string.h>

#include "comparison.h"
#include "errors.h"
#include "utils.h"

#define N 100000
#define SIZE 107
#define SIZE2 107
#define SIZE_WORD 15

static double time_comparisons_measure_bin_tree(bin_tree_node_t *bin_tree, double *average_comp, char words[SIZE2][SIZE_WORD]);
static double time_comparisons_measure_avl_tree(avl_tree_node_t *avl_tree, double *average_comp, char words[SIZE2][SIZE_WORD]);
static double time_comparisons_measure_hash_table(hash_table_t *hash_table, double *average_comp, char words[SIZE2][SIZE_WORD]);
static double time_comparisons_measure_file(FILE *file, double *average_comp, char words[SIZE2][SIZE_WORD]);

static double time_comparisons_measure_bin_tree(bin_tree_node_t *bin_tree, double *average_comp, char words[SIZE2][SIZE_WORD])
{
    clock_t start, finish;
    double sum = 0.0;
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        int count_comp = 0.0;
        start = clock();
        find_bin_tree(bin_tree, words[j], &count_comp);
        finish = clock();
        if (++j == SIZE2)
            j = 0;
        sum += finish - start;
        (*average_comp) += count_comp;
    }

    (*average_comp) /= N;
    return sum / N / CLOCKS_PER_SEC * 1000000;
}

static double time_comparisons_measure_avl_tree(avl_tree_node_t *avl_tree, double *average_comp, char words[SIZE2][SIZE_WORD])
{
    clock_t start, finish;
    double sum = 0.0;
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        int count_comp = 0.0;
        start = clock();
        find_avl_tree(avl_tree, words[j], &count_comp);
        finish = clock();
        if (++j == SIZE2)
            j = 0;
        sum += finish - start;
        (*average_comp) += count_comp;
    }

    (*average_comp) /= N;
    return sum / N / CLOCKS_PER_SEC * 1000000;
}

static double time_comparisons_measure_hash_table(hash_table_t *hash_table, double *average_comp, char words[SIZE2][SIZE_WORD])
{
    clock_t start, finish;
    double sum_time = 0.0;
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        int count_comp = 0.0;
        start = clock();
        find_hash_table(hash_table, words[j], &count_comp);
        finish = clock();
        if (++j == SIZE2)
            j = 0;
        sum_time += finish - start;
        (*average_comp) += count_comp;
    }

    (*average_comp) /= N;
    return sum_time / N / CLOCKS_PER_SEC * 1000000;
}

static double time_comparisons_measure_file(FILE *file, double *average_comp, char words[SIZE2][SIZE_WORD])
{
    clock_t start, finish;
    double sum_time = 0.0;
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        int count_comp = 0.0;
        start = clock();
        find_file(file, words[j], &count_comp);
        finish = clock();
        if (++j == SIZE2)
            j = 0;
        sum_time += finish - start;
        (*average_comp) += count_comp;
        rewind(file);
    }

    (*average_comp) /= N;
    return sum_time / N / CLOCKS_PER_SEC * 1000000;
}

int compare(void)
{
    FILE *file = fopen("input_comparison.txt", "r");
    if (!file)
    {
        puts("File error.");
        return FILE_ERROR;
    }

    bin_tree_node_t *bin_tree = create_bin_tree_from_file(file);
    if(!bin_tree)
    {
       puts("Input error.");
       return INPUT_ERROR;
    }

    rewind(file);
    avl_tree_node_t *avl_tree = create_avl_tree_from_file(file);
    if(!avl_tree)
    {
        puts("Input error.");
        return INPUT_ERROR;
    }
    avl_tree = balance_tree(avl_tree);

    rewind(file);
    hash_table_t *hash_table = create_table(file);
    if(!hash_table)
    {
        puts("Input error.");
        return INPUT_ERROR;
    }

    rewind(file);
    char words[SIZE2][SIZE_WORD];
    int i = 0;
    int sum_len = 0;
    while (fscanf(file, "%s", words[i]) == 1)
    {
        sum_len += strlen(words[i]);
        i++;
    }

    puts("┌─────────────────────┬────────────────────┬──────────┬────────────┬──────────┐");
    puts("│       Parameter     │ Binary search tree │ AVL tree │ Hash table │   File   │");
    puts("├─────────────────────┼────────────────────┼──────────┼────────────┼──────────┤");
    double count_comp_bin_tree = 0;
    double time_bin_tree = time_comparisons_measure_bin_tree(bin_tree, &count_comp_bin_tree, words);
    double count_comp_avl_tree = 0;
    double time_avl_tree = time_comparisons_measure_avl_tree(avl_tree, &count_comp_avl_tree, words);
    double count_comp_hash_table = 0;
    double time_hash_table = time_comparisons_measure_hash_table(hash_table, &count_comp_hash_table, words);
    double count_comp_file = 0;
    double time_file = time_comparisons_measure_file(file, &count_comp_file, words);
    printf("│%-21s│%-20lf│%-10lf│%-12lf│%-10lf│\n", "time (us)", time_bin_tree, time_avl_tree, time_hash_table, time_file);
    puts("├─────────────────────┼────────────────────┼──────────┼────────────┼──────────┤");
    printf("│%-21s│%-20lld│%-10lld│%-12lld│%-10lld│\n", "memory (bytes)", sizeof(bin_tree_node_t) * SIZE2 + sizeof(char) * sum_len,
          sizeof(avl_tree_node_t) * SIZE2 + sizeof(char) * sum_len,
          sizeof(table_node_t) * SIZE2 + sizeof(hash_table_t) + sizeof(char) * sum_len,
          sizeof(file) + sizeof(char) * (sum_len - 1));
    puts("├─────────────────────┼────────────────────┼──────────┼────────────┼──────────┤");
    printf("│%-21s│%-20lf│%-10lf│%-12lf│%-10lf│\n", "number of comparisons", count_comp_bin_tree,
          count_comp_avl_tree, count_comp_hash_table, count_comp_file);
    puts("└─────────────────────┴────────────────────┴──────────┼────────────┼──────────┘");

    if (bin_tree)
        free_bin_tree(bin_tree);

    if (avl_tree)
        free_avl_tree(avl_tree);

    if (hash_table)
        free_table(hash_table);

    fclose(file);

    return OK;
}
