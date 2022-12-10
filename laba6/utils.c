#include <stdlib.h>
#include <string.h>

#include "utils.h"

int find_file(FILE *f_in, const char *word, int *count_comp)
{
    char *read_word = NULL;
    int index = -1;

    while (fscanf(f_in, "%ms", &read_word) == 1)
    {
        index++;
        (*count_comp)++;
        if (strcmp(read_word, word) == 0)
        {
            free(read_word);
	    return index;
        }
	free(read_word);
    }
    return -1;
}

void print_comparisons(int comp_bin_tree, int comp_avl_tree, int comp_hash_table, int comp_file)
{
    puts("Number of comparisons:");
    printf("In binary search tree: %d\n", comp_bin_tree);
    printf("In avl tree: %d\n", comp_avl_tree);
    printf("In hash_table: %d\n", comp_hash_table);
    printf("In file: %d\n", comp_file);
}
