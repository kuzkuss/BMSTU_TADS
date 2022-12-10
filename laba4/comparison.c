#include <time.h>
#include <stdio.h>
#include "comparison.h"
#include "stack_array.h"
#include "list.h"
#include "errors.h"
#define N 1000

int comparison(void)
{
    clock_t start, finish;
    List *ptrs = NULL;
    int n = 0;

    double res1;
    double sum = 0.0;
    start = clock();
    Stack stack_arr = {0};
    stack_arr.top = -1;
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < N; ++i) {

            if (push_elem('a', &stack_arr)) {
                puts("Overflow stack.\n");
                return OVERFLOW_STACK;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (pop_elem(&stack_arr)) {
                puts("Empty stack.\n");
                return EMPTY_STACK;
            }
        }
    }
    finish = clock();
    sum += finish - start;
    res1 = sum / N / 2 / 1000 / CLOCKS_PER_SEC * 1000000;

    double res2;

    sum = 0.0;
    start = clock();
    List stack_list = NULL;
    for (int j = 0; j < 10000; ++j) {
        for (int i = 0; i < N; ++i) {
            if (add_elem('a', &stack_list, ptrs, &n)) {
                puts("Overflow stack.\n");
                return OVERFLOW_STACK;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (del_elem(&stack_list)) {
                puts("Empty stack.\n");
                return EMPTY_STACK;
            }
        }
    }
    finish = clock();
    sum += finish - start;
    res2 = sum / N / 2 / 1000 / CLOCKS_PER_SEC * 1000000;

    printf("┌──────────────┬─────────────────────────────────────┬────────────────────────────────────┐\n");
    printf("│   Parameter  │ Addition element in the array stack │ Addition element in the list stack │\n");
    printf("├──────────────┼─────────────────────────────────────┼────────────────────────────────────┤\n");
    printf("│%-14s│%-37lf│%-36lf│\n", "time (us)", res1, res2);
    printf("├──────────────┼─────────────────────────────────────┼────────────────────────────────────┤\n");
    printf("│%-14s│%-37lld│%-36lld│\n", "memory (bytes)", sizeof (Stack), sizeof (Node) * N);
    printf("└──────────────┴─────────────────────────────────────┴────────────────────────────────────┘\n");

    if (stack_list)
        free_list(&stack_list);
    return OK;
}