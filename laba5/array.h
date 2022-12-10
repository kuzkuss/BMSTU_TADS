#ifndef ARRAY_H
#define ARRAY_H

#define MAX_SIZE 1000

typedef struct {
    int array[MAX_SIZE];
    int p_in;
    int p_out;
} queue_arr_t;

int arr_queue_is_empty(const void *queue_arr);
int arr_queue_is_full(const queue_arr_t *pqueue_arr);
int push_arr_elem(int elem, void *pqueue_arr);
int pop_arr_elem(void *pqueue_arr);
int get_value_arr(void *queue_arr);

#endif //ARRAY_H
