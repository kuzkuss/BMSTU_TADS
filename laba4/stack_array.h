#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#define MAX_STACK 1000

typedef struct stack {
    char array[MAX_STACK];
    int top;
} Stack;

int stack_is_empty(const Stack *pstack);
int stack_is_full(const Stack *pstack);
int push_elem(char elem, Stack *pstack);
int pop_elem(Stack *pstack);

#endif //STACK_ARRAY_H
