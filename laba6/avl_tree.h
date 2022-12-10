#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include "avl_tree_node.h"

avl_tree_node_t *create_avl_tree_from_file(FILE *f_in);
avl_tree_node_t *insert_avl_tree(avl_tree_node_t *tree, avl_tree_node_t *node);
void free_avl_tree(avl_tree_node_t *tree);
void print_avl_tree(FILE *f_out, avl_tree_node_t *tree);
avl_tree_node_t *balance_tree(avl_tree_node_t *tree);
avl_tree_node_t *find_avl_tree(avl_tree_node_t *tree, const char *word, int *count_comp);

#endif // AVL_TREE_H
