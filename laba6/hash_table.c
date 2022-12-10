#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define TRUE 1
#define FALSE 0

static int is_prime(int n);
static int hash_function(const char *word, int size);

static int is_prime(int n)
{
    int res = TRUE;

    if (n < 2)
        return FALSE;

    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0) {
            res = FALSE;
            break;
        }
    }

    return res;
}

static int hash_function(const char *word, int size)
{
    int key = 0;
    for (; *word; word++)
    {
        key += *word;
    }
    return key % size;
}

hash_table_t *create_table(FILE *f_in)
{
    char *word = NULL;
    hash_table_t *hash_table = malloc(sizeof(hash_table_t));
    if(!hash_table)
        return NULL;
    int size = 0;
    while (fscanf(f_in, "%ms", &word) == 1)
    {
        size++;
        free(word);
    }

    if (!feof(f_in))
    {
        free(hash_table);
        return NULL;
    }

    while(!is_prime(size))
        size++;

    hash_table->size = size;

    hash_table->table = calloc(size, sizeof(table_node_t *));
    if(!hash_table->table)
    {
        free(hash_table);
        return NULL;
    }

    rewind(f_in);

    while (fscanf(f_in, "%ms", &word) == 1)
    {
        table_node_t *node = create_table_node(word);
        if (!node)
        {
            free_table(hash_table);
            return NULL;
        }
        int key = hash_function(word, size);
        hash_table->table[key] = add_table_node(node, hash_table->table[key]);
    }

    return hash_table;
}

void free_table(hash_table_t *hash_table)
{
    if (!hash_table)
        return;

    for (int i = 0; i < hash_table->size; ++i)
        if (hash_table->table[i])
            free_table_node(hash_table->table[i]);

    free(hash_table);
}

void print_table(const hash_table_t *hash_table)
{
    if (!hash_table)
        return;

    for (int i = 0; i < hash_table->size; ++i)
        if (hash_table->table[i])
        {
            printf("%d: ", i);
            print_table_node(hash_table->table[i]);
        }
        else
            printf("%d: \n", i);
}

table_node_t *find_hash_table(const hash_table_t *hash_table, const char *word, int *count_comp)
{
    int key = hash_function(word, hash_table->size);
    table_node_t *elem = hash_table->table[key];

    while (elem)
    {
        (*count_comp)++;
        if (strcmp(word, elem->value) == 0)
            return elem;
        elem = elem->next;
    }

    return NULL;
}

hash_table_t *restruct_hash_table(hash_table_t *hash_table, double max_count)
{
    hash_table_t *new_hash_table = malloc(sizeof(hash_table_t));

    int size = hash_table->size;
    size++;
    while(!is_prime(size))
        size++;

    new_hash_table->size = size;

    new_hash_table->table = calloc(new_hash_table->size, sizeof(table_node_t *));

    for (int i = 0; i < hash_table->size; ++i)
        if (hash_table->table[i])
        {
            table_node_t *elem = hash_table->table[i];
            while (elem)
            {
                table_node_t *node = create_table_node(elem->value);
                int key = hash_function(elem->value, new_hash_table->size);
                new_hash_table->table[key] = add_table_node(node, new_hash_table->table[key]);
                elem = elem->next;
            }
        }

    free_table(hash_table);

    if (count_comparisons(hash_table) > max_count)
        new_hash_table = restruct_hash_table(new_hash_table, max_count);

    return new_hash_table;
}

double count_comparisons(hash_table_t *hash_table)
{
    if (!hash_table)
        return 0;

    double res = 0.0;
    int counter = 0;

    for (int i = 0; i < hash_table->size; ++i)
        if (hash_table->table[i])
        {
            counter++;
            table_node_t *elem = hash_table->table[i];
            while (elem)
            {
                res++;
                elem = elem->next;
            }
        }

    return res / counter;
}
