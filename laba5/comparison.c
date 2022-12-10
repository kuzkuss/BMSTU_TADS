#include <time.h>
#include <stdio.h>
#include "list.h"
#include "array.h"
#include "comparison.h"
#include "errors.h"

int time_measure(void *queue, int (*push)(int, void *), int (*pop)(void *), double *res) {
    const int elem = 1;
    clock_t start, finish;
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        start = clock();
        for (int j = 0; j < SIZE; ++j) {
            if (push(elem, queue) != OK) {
                puts("Overflow queue.");
                return OVERFLOW_QUEUE;
            }
        }
        for (int j = 0; j < SIZE; ++j) {
            if (pop(queue) != OK) {
                puts("Empty queue.");
                return EMPTY_QUEUE;
            }
        }
        finish = clock();
        sum += finish - start;
    }
    *res = sum / N / SIZE / CLOCKS_PER_SEC * 1000000;
    return OK;
}

int compare(void) {
    queue_arr_t queue_arr = {0};
    queue_list_t queue_list = {0};
    double res_arr = 0.0;
    double res_list = 0.0;
    puts("|--------------|-------------|------------|");
    puts("|   Parameter  | Array queue | List queue |");
    puts("|--------------|-------------|------------|");
//    puts("┌──────────────┬─────────────┬────────────┐");
//    puts("│   Parameter  │ Array queue │ List queue │");
//    puts("├──────────────┼─────────────┼────────────┤");
    int rc = time_measure(&queue_arr, push_arr_elem, pop_arr_elem, &res_arr);
    if (rc)
        return rc;
    rc = time_measure(&queue_list, push_list_elem, pop_list_elem, &res_list);
    if (rc)
        return rc;
    printf("|%-14s|%-13lf|%-12lf|\n", "time (us)", res_arr, res_list);
    puts("|--------------|-------------|------------|");
    printf("|%-14s|%-13llu|%-12llu|\n", "memory (bytes)", sizeof (queue_arr_t), sizeof (node_t) * N + sizeof(queue_list_t));
    puts("|--------------|-------------|------------|");
    return OK;
}
