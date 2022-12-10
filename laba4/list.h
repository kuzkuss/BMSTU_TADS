#ifndef LIST_H
#define LIST_H

struct node {
    char value;
    struct node *next;
};

typedef struct node Node;

typedef Node *List;

int list_is_empty(const List *plist);
int add_elem(char elem, List *plist, List *ptrs, int *n);
void free_list(List *stack_list);
int del_elem(List *plist);

#endif //LIST_H
