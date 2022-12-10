#include <string.h>
#include "constants_declarations.h"
#include "sorting.h"

void bubble_sort_key_table(type_key_table *key_table, int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (strcmp(key_table[j].last_name, key_table[j + 1].last_name) > 0)
            {
                type_key_table tmp;
                tmp = key_table[j];
                key_table[j] = key_table[j + 1];
                key_table[j + 1] = tmp;
            }
}

void bubble_sort_source_table(subscriber *subscribers, int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (strcmp(subscribers[j].last_name, subscribers[j + 1].last_name) > 0)
            {
                subscriber tmp;
                tmp = subscribers[j];
                subscribers[j] = subscribers[j + 1];
                subscribers[j + 1] = tmp;
            }
}

void quick_sort_key_table(type_key_table *key_table, int n)
{
    int start = 0;
    int end = n - 1;
    type_key_table mid = key_table[n / 2];
    while (start <= end)
    {
        while (strcmp(key_table[start].last_name, mid.last_name) < 0)
            start++;
        while (strcmp(key_table[end].last_name, mid.last_name) > 0)
            end--;
        if (start <= end)
        {
            type_key_table tmp = key_table[start];
            key_table[start] = key_table[end];
            key_table[end] = tmp;
            start++;
            end--;
        }
    }
    if (end > 0)
        quick_sort_key_table(key_table, end + 1);
    if (start < n)
        quick_sort_key_table(&key_table[start], n - start);
}

void quick_sort_source_table(subscriber *subscribers, int n)
{
    int start = 0;
    int end = n - 1;
    subscriber mid = subscribers[n / 2];
    while (start <= end)
    {
        while (strcmp(subscribers[start].last_name, mid.last_name) < 0)
            start++;
        while (strcmp(subscribers[end].last_name, mid.last_name) > 0)
            end--;
        if (start <= end)
        {
            subscriber tmp = subscribers[start];
            subscribers[start] = subscribers[end];
            subscribers[end] = tmp;
            start++;
            end--;
        }
    }
    if (end > 0)
        quick_sort_source_table(subscribers, end + 1);
    if (start < n)
        quick_sort_source_table(&subscribers[start], n - start);
}
