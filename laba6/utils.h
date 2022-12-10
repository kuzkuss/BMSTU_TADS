#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

int find_file(FILE *f_in, const char *word, int *count_comp);
void print_comparisons(int comp_bin_tree, int comp_avl_tree, int comp_hash_table, int comp_file);

#endif // UTILS_H
