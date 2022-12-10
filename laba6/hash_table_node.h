#ifndef HASH_TABLE_NODE_H
#define HASH_TABLE_NODE_H

typedef struct table_node table_node_t;

struct table_node {
    char *value;
    table_node_t *next;
};

table_node_t *create_table_node(const char *word);
void free_table_node(table_node_t *head);
table_node_t *add_table_node(table_node_t *new_node, table_node_t *head);
void print_table_node(table_node_t *head);

#endif // HASH_TABLE_NODE_H
