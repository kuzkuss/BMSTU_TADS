#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

double time_src(subscriber *subscribers, int n);
double time_key(type_key_table *key_table, int n);
double time_quicksort_key(type_key_table *key_table, int n);
double time_quicksort_src(subscriber *subscribers, int n);

#endif //TIME_MEASUREMENT_H
