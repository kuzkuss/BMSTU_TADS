#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table_node.h"

table_node_t *create_table_node(const char *word)
{
    table_node_t *table_node = malloc(sizeof(table_node_t));

    if (table_node)
    {
        table_node->value = strdup(word);
        if (!table_node->value)
        {
            free(table_node);
            return NULL;
        }
        table_node->next = NULL;
    }
    return table_node;
}

void free_table_node(table_node_t *head)
{
    table_node_t *next = NULL;
    while (head)
    {
        next = head->next;
        free(head->value);
        head->value = NULL;
        free(head);
        head = next;
    }
}

table_node_t *add_table_node(table_node_t *new_node, table_node_t *head)
{
    if (!head)
        return new_node;
    table_node_t *cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = new_node;
    return head;
}

void print_table_node(table_node_t *head)
{
    while (head->next)
    {
        printf("%s, ", head->value);
        head = head->next;
    }

    printf("%s\n", head->value);
}

