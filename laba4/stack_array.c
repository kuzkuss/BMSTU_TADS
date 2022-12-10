#include "stack_array.h"
#include "errors.h"

int stack_is_empty(const Stack *pstack)
{
    if (pstack->top == -1)
        return TRUE;
    else
        return FALSE;
}

int stack_is_full(const Stack *pstack)
{
    return pstack->top == MAX_STACK - 1;
}

int push_elem(char elem, Stack *pstack)
{
    if (stack_is_full(pstack))
        return OVERFLOW_STACK;
    else
        pstack->array[++pstack->top] = elem;
    return OK;
}

int pop_elem(Stack *pstack)
{
    if (stack_is_empty(pstack))
        return EMPTY_STACK;
    else
        --(pstack->top);
    return OK;
}