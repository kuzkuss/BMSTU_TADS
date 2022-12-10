#include <stdlib.h>
#include "list.h"
#include "errors.h"
#include <stdio.h>

int list_is_empty(const List *plist)
{
    if (*plist == NULL)
        return TRUE;
    else
        return FALSE;
}

int add_elem(char elem, List *plist, List *ptrs, int *n)
{
    Node *pnew = malloc(sizeof(Node));

    if (!pnew)
        return ALLOCATE_ERROR;

    for (int i = 0; i < *n; ++i)
        if (ptrs && ptrs[i] == pnew)
        {
            for (int j = i; j < *n - 1; ++j)
                ptrs[j] = ptrs[j + 1];
            --(*n);
        }
    pnew->next = NULL;
    pnew->value = elem;
    if (*plist == NULL)
        *plist = pnew;
    else
    {
        pnew->next = *plist;
        pnew->value = elem;
        *plist = pnew;
    }
    return OK;
}

int del_elem(List *plist)
{
    Node *top = *plist;
    if (list_is_empty(plist))
        return EMPTY_STACK;

    *plist = (*plist)->next;
    top->next = NULL;
    free(top);

    return OK;
}

void free_list(List *stack_list)
{
    Node *psave = NULL;
    while(*stack_list != NULL) {
        psave = (*stack_list)->next;
        free(*stack_list);
        *stack_list = psave;
    }
}
