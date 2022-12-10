#include <stdio.h>
#include "list.h"
#include "array.h"
#include "errors.h"
#include "comparison.h"
#include "queue_simulation.h"

int main() {
    setbuf(stdout, NULL);
    queue_list_t queue_list = {0};
    queue_arr_t queue_arr = {0};

    double min_arrival_time = 0.0;
    double max_arrival_time = 6.0;

    double min_process_time = 0.0;
    double max_process_time = 1.0;

    int rc = 0;

    int choice = -1;
    while (choice) {
        puts("Choose an action:\n"
               "1-Modeling queue by array\n"
               "2-Modeling queue by list\n"
               "3-Time change\n"
               "4-Comparison of two implementations\n"
               "0-Exit");
        puts("Enter a choice");
        if (scanf("%d", &choice) != 1) {
            puts("Incorrect choice.\n");
            choice = -1;
            scanf("%*[^\n]");
            continue;
        }
        switch (choice) {
            case 0:
                break;
            case 1:
                rc = queue_simulation(&queue_arr, push_arr_elem, pop_arr_elem, arr_queue_is_empty, get_value_arr, min_arrival_time, max_arrival_time, min_process_time, max_process_time, ARRAY);
                if (rc == EMPTY_QUEUE) {
                    puts("Empty queue.\n");
                    return rc;
                }
                else if (rc == OVERFLOW_QUEUE) {
                    puts ("Overflow queue.\n");
                    return rc;
                }
                for (int i = 0; i < MAX_SIZE; ++i)
                    queue_arr.array[i] = 0;
                queue_arr.p_in = 0;
                queue_arr.p_out = 0;
                break;
            case 2:
                rc = queue_simulation(&queue_list, push_list_elem, pop_list_elem, list_queue_is_empty, get_value_list, min_arrival_time, max_arrival_time, min_process_time, max_process_time, LIST);
                if (rc == EMPTY_QUEUE) {
                    free_list(&queue_list);
                    puts("Empty queue.\n");
                    return rc;
                }
                else if (rc == OVERFLOW_QUEUE) {
                    free_list(&queue_list);
                    puts ("Overflow queue.\n");
                    return rc;
                }
                free_list(&queue_list);
                break;
            case 3:
                time_change(&min_arrival_time, &max_arrival_time, &min_process_time, &max_process_time);
                break;
            case 4:
                rc = compare();
                if (rc)
                    return rc;
                break;
            default:
                puts("Incorrect choice.\n");
                continue;
        }
    }
    return 0;
}
