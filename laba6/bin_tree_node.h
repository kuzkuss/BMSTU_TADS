#ifndef BIN_TREE_NODE_H
#define BIN_TREE_NODE_H

typedef struct bin_tree_node bin_tree_node_t;

struct bin_tree_node
{
    char *word;
    bin_tree_node_t *left;
    bin_tree_node_t *right;
};

bin_tree_node_t *create_bin_tree_node(const char *word);
void free_bin_tree_node(bin_tree_node_t *node);
void bin_tree_node_to_dot(bin_tree_node_t *node, void *param);

#endif // BIN_TREE_NODE_H
