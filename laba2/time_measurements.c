#include <time.h>
#include "constants_declarations.h"
#include "sorting.h"
#include "time_measurement.h"

double time_src(subscriber *subscribers, int n)
{
    double sum = 0.0;
    for (int i = 1; i < 100; i++)
    {
        clock_t start = clock();
        bubble_sort_source_table(subscribers, n);
        clock_t finish = clock();
        sum += finish - start;
    }
    return sum / CLOCKS_PER_SEC * 10000;
}

double time_key(type_key_table *key_table, int n)
{
    double sum = 0.0;
    for (int i = 1; i < 100; i++)
    {
        clock_t start = clock();
        bubble_sort_key_table(key_table, n);
        clock_t finish = clock();
        sum += finish - start;
    }
    return sum / CLOCKS_PER_SEC * 10000;
}

double time_quicksort_key(type_key_table *key_table, int n)
{
    double sum = 0.0;
    for (int i = 1; i < 100; i++)
    {
        clock_t start = clock();
        quick_sort_key_table(key_table, n);
        clock_t finish = clock();
        sum += finish - start;
    }
    return sum / CLOCKS_PER_SEC * 10000;
}

double time_quicksort_src(subscriber *subscribers, int n)
{
    double sum = 0.0;
    for (int i = 1; i < 100; i++)
    {
        clock_t start = clock();
        quick_sort_source_table(subscribers, n);
        clock_t finish = clock();
        sum += finish - start;
    }
    return sum / CLOCKS_PER_SEC * 10000;
}
