#include "array.h"
#include "errors.h"

int arr_queue_is_empty(const void *queue_arr) {
    const queue_arr_t *pqueue_arr = queue_arr;
    return (pqueue_arr->p_in == pqueue_arr->p_out && pqueue_arr->array[pqueue_arr->p_in] == 0);
}

int arr_queue_is_full(const queue_arr_t *pqueue_arr) {
    return (pqueue_arr->p_in == pqueue_arr->p_out && pqueue_arr->array[pqueue_arr->p_in] != 0);
}

int push_arr_elem(int elem, void *queue_arr) {
    queue_arr_t *pqueue_arr = queue_arr;
    if (arr_queue_is_full(pqueue_arr))
        return OVERFLOW_QUEUE;
    pqueue_arr->array[pqueue_arr->p_in] = elem;
    pqueue_arr->p_in = (pqueue_arr->p_in + 1) % MAX_SIZE;
    return OK;
}

int pop_arr_elem(void *queue_arr) {
    queue_arr_t *pqueue_arr = queue_arr;
    if (arr_queue_is_empty(pqueue_arr))
        return EMPTY_QUEUE;
    pqueue_arr->array[pqueue_arr->p_out] = 0;
    pqueue_arr->p_out = (pqueue_arr->p_out + 1) % MAX_SIZE;
    return OK;
}

int get_value_arr(void *queue_arr) {
    queue_arr_t *pqueue_arr = queue_arr;
    return pqueue_arr->array[pqueue_arr->p_out];
}
