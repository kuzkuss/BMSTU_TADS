#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdio.h"
#include "stack_array.h"
#include "errors.h"
#include "list.h"

void output_array(Stack *pstack)
{
    if (pstack->top == -1)
    {
        puts("Stack is empty.");
        return;
    }
    printf("Elements:\n");
    int i = pstack->top;
    while (i > -1)
    {
        printf("%c ", pstack->array[i]);
        --i;
    }
    puts("\n");
}

void output_list(List *plist, int n, List *ptrs)
{
    if (*plist == NULL)
    {
        puts("Stack is empty.");
        return;
    }
    printf("Elements:\n");
    List head = *plist;
    while (head->next != NULL)
    {
        printf("%c ", head->value);
        head = head->next;
    }
    printf("%c ", head->value);
    puts("\n");
    printf("Addresses:\n");
    for (int j = 0; j < n; ++j)
        printf("%p ", (void *) ptrs[j]);
    puts("\n");
}

