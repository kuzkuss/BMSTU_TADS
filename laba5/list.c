#include <stdlib.h>
#include "list.h"
#include "errors.h"

int list_queue_is_empty(const void *queue_list) {
    const queue_list_t *pqueue_list = queue_list;
    return (pqueue_list->p_in == NULL && pqueue_list->p_out == NULL);
}

int push_list_elem(int elem, void *queue_list) {
    queue_list_t *pqueue_list = queue_list;
    node_t *new_node = calloc(1, sizeof(node_t));
    if (!new_node)
        return OVERFLOW_QUEUE;
    if (pqueue_list->p_in == NULL) {
        pqueue_list->p_in = new_node;
        pqueue_list->p_out = pqueue_list->p_in;
        pqueue_list->p_in->value = elem;
    }
    else {
        pqueue_list->p_in->next = new_node;
        pqueue_list->p_in->next->value = elem;
        pqueue_list->p_in = pqueue_list->p_in->next;
    }
    return OK;
}

int pop_list_elem(void *queue_list) {
    queue_list_t *pqueue_list = queue_list;
    if (list_queue_is_empty(pqueue_list))
        return EMPTY_QUEUE;
    node_t *tmp = pqueue_list->p_out;
    pqueue_list->p_out = pqueue_list->p_out->next;
    free(tmp);
    if (pqueue_list->p_out == NULL)
        pqueue_list->p_in = NULL;
    return OK;
}

void free_list(queue_list_t *pqueue_list) {
    node_t *next = NULL;
    while (pqueue_list->p_out != NULL) {
        next = pqueue_list->p_out->next;
        free(pqueue_list->p_out);
        pqueue_list->p_out = next;
    }
    pqueue_list->p_out = NULL;
    pqueue_list->p_in = NULL;
}

int get_value_list(void *queue_list) {
    queue_list_t *pqueue_list = queue_list;
    return pqueue_list->p_out->value;
}

node_t *get_address_pout(void *queue_list) {
    queue_list_t *pqueue_list = queue_list;
    return pqueue_list->p_out;
}

node_t *get_address_pin(void *queue_list) {
    queue_list_t *pqueue_list = queue_list;
    return pqueue_list->p_in;
}
