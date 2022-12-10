#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

#include "hash_table_node.h"

typedef struct hash_table hash_table_t;

struct hash_table {
    table_node_t **table;
    int size;
};

hash_table_t *create_table(FILE *f_in);
void free_table(hash_table_t *hash_table);
void print_table(const hash_table_t *hash_table);
table_node_t *find_hash_table(const hash_table_t *hash_table, const char *word, int *count_comp);
hash_table_t *restruct_hash_table(hash_table_t *hash_table, double max_count);
double count_comparisons(hash_table_t *hash_table);

#endif // HASH_TABLE_H
