#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "avl_tree_node.h"

#define TRUE 1
#define FALSE 0

extern int count_null;

static avl_tree_node_t *rotate_right(avl_tree_node_t *root);
static avl_tree_node_t *rotate_left(avl_tree_node_t *root);

avl_tree_node_t *create_avl_tree_node(const char *word)
{
    avl_tree_node_t *tree_node = malloc(sizeof(avl_tree_node_t));

    if (tree_node)
    {
        tree_node->word = strdup(word);
        if (!tree_node->word)
        {
            free(tree_node);
            return NULL;
        }
        tree_node->height = 0;
        tree_node->left = NULL;
        tree_node->right = NULL;
    }
    return tree_node;
}

void free_avl_tree_node(avl_tree_node_t *node)
{
    free(node->word);
    node->word = NULL;
    free(node);
}

void avl_tree_node_to_dot(avl_tree_node_t *node, void *param)
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

void calc_height(avl_tree_node_t *root)
{
    if (root->left && root->right)
    {
        root->height = root->left->height > root->right->height ? root->left->height + 1 : root->right->height + 1;
    }
    else if(root->left)
    {
        root->height = root->left->height + 1;
    }
    else if(root->right)
    {
        root->height = root->right->height + 1;
    }
    else
        root->height = 0;
}

avl_tree_node_t *rotate_right(avl_tree_node_t *root)
{
    avl_tree_node_t *new_root = root->left;
    root->left = new_root->right;
    calc_height(root);
    new_root->right = root;
    calc_height(new_root);
    return new_root;
}

avl_tree_node_t *rotate_left(avl_tree_node_t *root)
{
    avl_tree_node_t *new_root = root->right;
    root->right = new_root->left;
    calc_height(root);
    new_root->left = root;
    calc_height(new_root);
    return new_root;
}

int is_balance_node(avl_tree_node_t *node)
{
    int l_height = 0;
    int r_height = 0;

    if (!node->left)
        l_height = -1;
    else
        l_height = node->left->height;

    if(!node->right)
        r_height = -1;
    else
        r_height = node->right->height;

    if (abs(l_height - r_height) > 1)
        return FALSE;

    else
        return TRUE;
}

avl_tree_node_t *balance_node(avl_tree_node_t *node)
{
    int l_height = 0;
    int r_height = 0;

    if (!node->left)
        l_height = -1;
    else
        l_height = node->left->height;

    if(!node->right)
        r_height = -1;
    else
        r_height = node->right->height;

    if (abs(l_height - r_height) > 1)
    {
        if (l_height > r_height)
        {
            int l_l_height = 0;
            int l_r_height = 0;

            if (!node->left->left)
                l_l_height = -1;
            else
                l_l_height = node->left->left->height;

            if(!node->left->right)
                l_r_height = -1;
            else
                l_r_height = node->left->right->height;

            if (l_l_height >= l_r_height)
                node = rotate_right(node);
            else
            {
                node->left = rotate_left(node->left);
                node = rotate_right(node);
            }
        }
        else
        {
            int r_l_height = 0;
            int r_r_height = 0;

            if (!node->right->left)
                r_l_height = -1;
            else
                r_l_height = node->right->left->height;

            if(!node->right->right)
                r_r_height = -1;
            else
                r_r_height = node->right->right->height;

            if (r_r_height >= r_l_height)
                node = rotate_left(node);
            else
            {
                node->right = rotate_right(node->right);
                node = rotate_left(node);
            }
        }
    }
    return node;
}
