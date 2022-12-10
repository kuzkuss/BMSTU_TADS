#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

typedef struct avl_tree_node avl_tree_node_t;

struct avl_tree_node
{
    char *word;
    int height;
    avl_tree_node_t *left;
    avl_tree_node_t *right;
};

avl_tree_node_t *create_avl_tree_node(const char *word);
void free_avl_tree_node(avl_tree_node_t *node);
void avl_tree_node_to_dot(avl_tree_node_t *node, void *param);
void calc_height(avl_tree_node_t *root);
avl_tree_node_t *balance_node(avl_tree_node_t *node);
int is_balance_node(avl_tree_node_t *node);

#endif // AVL_TREE_NODE_H
