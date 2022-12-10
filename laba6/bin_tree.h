#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stdio.h>
#include "bin_tree_node.h"

bin_tree_node_t *create_bin_tree_from_file(FILE *f_in);
bin_tree_node_t *insert_bin_tree(bin_tree_node_t *tree, bin_tree_node_t *node);
void free_bin_tree(bin_tree_node_t *tree);
void print_bin_tree(FILE *f_out, bin_tree_node_t *tree);
bin_tree_node_t *find_bin_tree(bin_tree_node_t *tree, const char *word, int *count_comp);

#endif // BIN_TREE_H
