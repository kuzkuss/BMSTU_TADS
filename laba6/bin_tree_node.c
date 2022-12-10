#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bin_tree_node.h"

extern int count_null;

bin_tree_node_t *create_bin_tree_node(const char *word)
{
    bin_tree_node_t *tree_node = malloc(sizeof(bin_tree_node_t));

    if (tree_node)
    {
        tree_node->word = strdup(word);
        if (!tree_node->word)
        {
            free(tree_node);
            return NULL;
        }
        tree_node->left = NULL;
        tree_node->right = NULL;
    }
    return tree_node;
}

void free_bin_tree_node(bin_tree_node_t *node)
{
    free(node->word);
    node->word = NULL;
    free(node);
}

void bin_tree_node_to_dot(bin_tree_node_t *node, void *param)
{
    FILE *f = param;

    if (node->left)
        fprintf(f, "%s -> %s;\n", node->word, node->left->word);
    else
    {
        fprintf(f, "%s -> NULL%d;\n", node->word, count_null);
        count_null++;
    }

    if(node->right)
        fprintf(f, "%s -> %s;\n", node->word, node->right->word);
    else
    {
        fprintf(f, "%s -> NULL%d;\n", node->word, count_null);
        count_null++;
    }
}
