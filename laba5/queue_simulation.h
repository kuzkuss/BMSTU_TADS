#ifndef QUEUE_SIMULATION_H
#define QUEUE_SIMULATION_H

typedef enum {
    LIST,
    ARRAY,
} kind_t;

void time_change(double *min_arrival_time, double *max_arrival_time, double *min_process_time, double *max_process_time);
int queue_simulation(void *queue, int (*push)(int, void *), int (*pop)(void *), int (*is_empty)(const void *), int (*get_value)(void *), const double min_arrival_time,const double max_arrival_time, const double min_process_time, const double max_process_time, kind_t kind);

#endif //QUEUE_SIMULATION_H
