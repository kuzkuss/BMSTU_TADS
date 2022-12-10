#include <string.h>
#include "avl_tree.h"

#define TRUE 1
#define FALSE 0

extern int count_null;

typedef void (*ptr_action_t)(avl_tree_node_t *, void *);
static void avl_tree_apply_pre(avl_tree_node_t *tree, ptr_action_t f, void *arg);
static void avl_tree_export_to_dot(FILE *f_out, const char *tree_name, avl_tree_node_t *tree);
static int is_balance_tree(avl_tree_node_t *tree);

avl_tree_node_t *create_avl_tree_from_file(FILE *f_in)
{
    char *word = NULL;
    avl_tree_node_t *tree = NULL;
    while (fscanf(f_in, "%ms", &word) == 1)
    {
        avl_tree_node_t *node = create_avl_tree_node(word);
        if (!node)
        {
            free_avl_tree(tree);
            return NULL;
        }
        tree = insert_avl_tree(tree, node);
        if (!tree)
        {
            free_avl_tree(tree);
            return NULL;
        }
    }
    if (!feof(f_in))
    {
        free_avl_tree(tree);
        return NULL;
    }

    return tree;
}

avl_tree_node_t *insert_avl_tree(avl_tree_node_t *tree, avl_tree_node_t *node)
{
    if (!tree)
    {
        return node;
    }

    int cmp = strcmp(node->word, tree->word);

    if(cmp == 0)
        return NULL;

    else if (cmp < 0)
    {
        if (!tree->left && !tree->right)
            tree->height++;
        tree->left = insert_avl_tree(tree->left, node);
        if (!tree->left)
            return NULL;
    }

    else if (cmp > 0)
    {
        if (!tree->left && !tree->right)
            tree->height++;
        tree->right = insert_avl_tree(tree->right, node);
        if (!tree->right)
            return NULL;
    }

    calc_height(tree);

    return tree;
}

void free_avl_tree(avl_tree_node_t *tree)
{
    if (!tree)
        return;

    free_avl_tree(tree->left);
    free_avl_tree(tree->right);
    free_avl_tree_node(tree);
}

static void avl_tree_apply_pre(avl_tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (!tree)
        return;

    f(tree, arg);
    avl_tree_apply_pre(tree->left, f, arg);
    avl_tree_apply_pre(tree->right, f, arg);
}

static void avl_tree_export_to_dot(FILE *f_out, const char *tree_name, avl_tree_node_t *tree)
{
    count_null = 0;

    fprintf(f_out, "digraph %s {\n", tree_name);

    avl_tree_apply_pre(tree, avl_tree_node_to_dot, f_out);

    fprintf(f_out, "}\n");
}

void print_avl_tree(FILE *f_out, avl_tree_node_t *tree)
{
    avl_tree_export_to_dot(f_out, "avl_tree", tree);
}

static int is_balance_tree(avl_tree_node_t *tree)
{
    if (!tree)
        return TRUE;

    int res = TRUE;

    res = is_balance_tree(tree->left);
    if(!res)
        return res;
    res = is_balance_tree(tree->right);
    if(!res)
        return res;
    res = is_balance_node(tree);

    return res;
}

avl_tree_node_t *balance_tree(avl_tree_node_t *tree)
{
    if (!tree)
        return tree;

    tree->left = balance_tree(tree->left);
    tree->right = balance_tree(tree->right);
    tree = balance_node(tree);

    if (!is_balance_tree(tree))
        tree = balance_tree(tree);

    return tree;
}

avl_tree_node_t *find_avl_tree(avl_tree_node_t *tree, const char *word, int *count_comp)
{
    int cmp;

    while(tree)
    {
        (*count_comp)++;
        cmp = strcmp(word, tree->word);
        if(cmp == 0)
            return tree;
        else if(cmp < 0)
            tree= tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}

