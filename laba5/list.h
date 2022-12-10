#ifndef LIST_H
#define LIST_H

struct node {
    int value;
    struct node *next;
};

typedef struct node node_t;
typedef struct {
    node_t *p_in;
    node_t *p_out;
} queue_list_t;

int list_queue_is_empty(const void *queue_list);
int push_list_elem(int elem, void *queue_list);
int pop_list_elem(void *queue_list);
void free_list(queue_list_t *pqueue_list);
int get_value_list(void *queue_list);
node_t *get_address_pout(void *queue_list);
node_t *get_address_pin(void *queue_list);

#endif //LIST_H
