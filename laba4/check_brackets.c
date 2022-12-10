#include <stdio.h>
#include "check_brackets.h"
#include "stack_array.h"
#include "list.h"
#include "errors.h"

int check_brackets_array(Stack *pstack)
{
    int count = 0;
    puts("Enter string:\n");
    char elem = getchar();
    while (pstack->top < MAX_STACK && elem != '\n')
    {
        switch (elem) {
            case '{':
            case '(':
            case '[':
                if (push_elem(elem, pstack))
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                ++count;
                break;
            case '}':
                if (stack_is_empty(pstack))
                    return FALSE;
                if (pstack->array[pstack->top] == '{')
                    pop_elem(pstack);
                break;
            case ')':
                if (stack_is_empty(pstack))
                    return FALSE;
                if (pstack->array[pstack->top] == '(')
                    pop_elem(pstack);
                break;
            case ']':
                if (stack_is_empty(pstack))
                    return FALSE;
                if (pstack->array[pstack->top] == '[')
                    pop_elem(pstack);
                break;
        }
        elem = getchar();
    }
    if (count == 0)
        return NONE;
    else if (stack_is_empty(pstack))
        return TRUE;
    else
        return FALSE;
}

int check_brackets_list(List *plist, List *ptrs, int n)
{
    puts("Enter string:\n");
    int count = 0;
    char elem = getchar();
    while (elem != '\n')
    {
        switch (elem) {
            case '{':
            case '(':
            case '[':
                if (add_elem(elem, plist, ptrs, &n))
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                ++count;
                break;
            case '}':
                if (list_is_empty(plist))
                    return FALSE;
                if ((*plist)->value == '{')
                    del_elem(plist);
                break;
            case ')':
                if (list_is_empty(plist))
                    return FALSE;
                if ((*plist)->value == '(')
                    del_elem(plist);
                break;
            case ']':
                if (list_is_empty(plist))
                    return FALSE;
                if ((*plist)->value == '[')
                    del_elem(plist);
                break;
        }
        elem = getchar();
    }
    if (count == 0)
        return NONE;
    else if (list_is_empty(plist))
        return TRUE;
    else
        return FALSE;
}
