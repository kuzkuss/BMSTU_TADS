#include <string.h>
#include "bin_tree.h"

int count_null = 0;

typedef void (*ptr_action_t)(bin_tree_node_t *, void *);
static void bin_tree_apply_pre(bin_tree_node_t *tree, ptr_action_t f, void *arg);
static void bin_tree_export_to_dot(FILE *f_out, const char *tree_name, bin_tree_node_t *tree);

bin_tree_node_t *create_bin_tree_from_file(FILE *f_in)
{
    char *word = NULL;
    bin_tree_node_t *tree = NULL;
    while (fscanf(f_in, "%ms", &word) == 1)
    {
        bin_tree_node_t *node = create_bin_tree_node(word);
        if (!node)
        {
            free_bin_tree(tree);
            return NULL;
        }
        tree = insert_bin_tree(tree, node);
        if (!tree)
        {
            free_bin_tree(tree);
            return NULL;
        }
    }
    if (!feof(f_in))
    {
        free_bin_tree(tree);
        return NULL;
    }

    return tree;
}

bin_tree_node_t *insert_bin_tree(bin_tree_node_t *tree, bin_tree_node_t *node)
{
    if (!tree)
    {
        return node;
    }

    int cmp = strcmp(node->word, tree->word);

    if (cmp == 0)
        return NULL;

    else if (cmp < 0)
    {
        tree->left = insert_bin_tree(tree->left, node);
        if (!tree->left)
            return NULL;
    }
    else if (cmp > 0)
    {
        tree->right = insert_bin_tree(tree->right, node);
        if (!tree->right)
            return NULL;
    }

    return tree;
}

void free_bin_tree(bin_tree_node_t *tree)
{
    if (!tree)
        return;

    free_bin_tree(tree->left);
    free_bin_tree(tree->right);
    free_bin_tree_node(tree);
}

static void bin_tree_apply_pre(bin_tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (!tree)
        return;

    f(tree, arg);
    bin_tree_apply_pre(tree->left, f, arg);
    bin_tree_apply_pre(tree->right, f, arg);
}

static void bin_tree_export_to_dot(FILE *f_out, const char *tree_name, bin_tree_node_t *tree)
{
    count_null = 0;

    fprintf(f_out, "digraph %s {\n", tree_name);

    bin_tree_apply_pre(tree, bin_tree_node_to_dot, f_out);

    fprintf(f_out, "}\n");
}

void print_bin_tree(FILE *f_out, bin_tree_node_t *tree)
{
    bin_tree_export_to_dot(f_out, "binary_tree", tree);
}

bin_tree_node_t *find_bin_tree(bin_tree_node_t *tree, const char *word, int *count_comp)
{
    int cmp;

    while (tree)
    {
        (*count_comp)++;
        cmp = strcmp(word, tree->word);
        if(cmp == 0)
            return tree;
        else if(cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}

