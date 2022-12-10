#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue_simulation.h"
#include "list.h"

static double random_time(double min_time, double max_time);

static void output_addresses(node_t **ptrs, int amount_reused, int amount_unused);
static void output_info(int cur_queue_length, double average_queue_length);

void time_change(double *min_arrival_time, double *max_arrival_time, double *min_process_time, double *max_process_time) {
    printf("Select:\n"
         "1-Change arrival time (now from %.1lf to %.1lf)\n"
         "2-Change processing time (now from %.1lf to %.1lf)\n", *min_arrival_time, *max_arrival_time, *min_process_time, *max_process_time);
    int choice = 0;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        printf("Incorrect input.\n");
        return;
    }
    switch (choice) {
        case 1:
            puts("Enter the minimum time of arrival:");
            if (scanf("%lf", min_arrival_time) != 1) {
                printf("Incorrect input.\n");
                return;
            }
            puts("Enter the maximum time of arrival:");
            if (scanf("%lf", max_arrival_time) != 1) {
                printf("Incorrect input.\n");
                return;
            }
            break;
        case 2:
            puts("Enter the minimum processing time:");
            if (scanf("%lf", min_process_time) != 1) {
                printf("Incorrect input.\n");
                return;
            }
            puts("Enter the maximum processing time:");
            if (scanf("%lf", max_process_time) != 1) {
                printf("Incorrect input.\n");
                return;
            }
            break;
    }
}

static double random_time(double min_time, double max_time) {
    return (double) rand() / RAND_MAX * (max_time - min_time) + min_time;
}

static void output_addresses(node_t **ptrs, int amount_reused, int amount_unused) {
    puts("Show information about memory fragmentation?\n"
         "1-YES, 2-NO");
    int choice = 0;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        printf("Incorrect input.\n");
        return;
    }
    switch (choice) {
        case 1:
            puts("Number of reused addresses:");
            printf("%d\n", amount_reused);
            puts("Number of unused addresses:");
            printf("%d\n", amount_unused);
            puts("Unused addresses:");
            for (int i = 0; i < 10; ++i)
                printf("%p\n", (void *) ptrs[i]);
            puts("...");
            break;
        case 2:
            break;
    }
}

static void output_info(int cur_queue_length, double average_queue_length) {
    printf("Current queue length: %d\n", cur_queue_length);
    printf("Average queue length: %lf\n", average_queue_length);
}

int queue_simulation(void *queue, int (*push)(int, void *), int (*pop)(void *), int (*is_empty)(const void *), int (*get_value)(void *), const double min_arrival_time,const double max_arrival_time, const double min_process_time, const double max_process_time, kind_t kind) {
    int count = 0;

    int amount_unused = 0;
    int total_amount = 0;
    double average_arrival = 0.0;
    double average_process = 0.0;
    int rc = 0;

    int requests_out = 0;
    int requests_in = 0;

    int cur_queue_length = 0;
    unsigned long long int sum_queue_length = 0;

    double total_time = 0.0;
    double work_time = 0.0;
    double downtime = 0.0;
    int count_operations = 0;

    node_t **ptrs = NULL;

    double cur_time_process = 0.0;
    double diff = 0.0;
    while (requests_out < 1000) {
        double arrival_time = random_time(min_arrival_time, max_arrival_time);
        average_arrival += arrival_time;
        if (arrival_time - diff < 0) {
            arrival_time = 0.0;
            diff -= arrival_time;
        }
        else {
            arrival_time -= diff;
            diff = 0.0;
        }
        if (total_time > 0) {
            int value = 0;
            while (arrival_time > cur_time_process) {
                if (is_empty(queue)) {
                    total_time += arrival_time - cur_time_process;
                    downtime += arrival_time - cur_time_process;
                    break;
                }
                value = get_value(queue);
                double processing_time = random_time(min_process_time, max_process_time);
                average_process += processing_time;
                cur_time_process += processing_time;
                work_time += processing_time;
                count_operations++;
                total_time += processing_time;

                if (kind == LIST) {
                    total_amount++;
                    amount_unused++;
                    ptrs = realloc(ptrs, amount_unused * sizeof(node_t *));
                    ptrs[amount_unused - 1] = get_address_pout(queue);
                }
                rc = pop(queue);
                if (rc)
                    return rc;

                if (++value < 6 && arrival_time > cur_time_process) {
                    rc = push(value, queue);
                    if (rc)
                        return rc;
                    if (kind == LIST) {
                        node_t *new_address = get_address_pin(queue);
                        for (int i = 0; i < amount_unused; ++i)
                            if (ptrs[i] == new_address) {
                                ptrs[i] = ptrs[amount_unused - 1];
                                --amount_unused;
                            }
                    }
                }
                else if (value == 6) {
                    cur_queue_length--;
                    sum_queue_length += cur_queue_length;
                    count++;
                    if (++requests_out % 100 == 0) {
                        printf("%d requests:\n", requests_out);
                        output_info(cur_queue_length, (double) sum_queue_length / count);
                    }
                    if (requests_out == 1000)
                        break;
                }
            }
            if (requests_out < 1000) {
                if (cur_time_process - arrival_time > 0)
                    diff = cur_time_process - arrival_time;

                push(1, queue);
                requests_in++;
                cur_queue_length++;
                cur_time_process = 0.0;
                if (value < 6 && value > 0) {
                    rc = push(value, queue);
                    if (rc)
                        return rc;
                }
                sum_queue_length += cur_queue_length;
                count++;
            }
        }
        else {
            rc = push(1, queue);
            if (rc)
                return rc;
            requests_in++;
            total_time += arrival_time;
            downtime += arrival_time;
            cur_queue_length++;
        }
    }
    double amount_requests = total_time / (min_arrival_time + max_arrival_time) * 2;
    printf("\nTotal time: %lf\n", total_time);
    printf("The error is %lf%%\n", fabs(requests_in - amount_requests) * 100 / amount_requests);
    printf("Work time: %lf\n", work_time);
    printf("Downtime: %lf\n", downtime);
    //printf("Current length of queue: %d\n", cur_queue_length);
    //printf("Average process: %lf\n", average_process / 1000 / 5);
    //printf("Average arrival: %lf\n", average_arrival / 1000);
    printf("Number of requests that left the system: %d\n", requests_out);
    printf("Number of requests entered into the system: %d\n", requests_in);
    printf("Number of operations of the service device: %d\n", count_operations);

    if (kind == LIST)
        output_addresses(ptrs, total_amount - amount_unused, amount_unused);
    free(ptrs);
    return rc;
}
