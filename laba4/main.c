#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "list.h"
#include "stack_array.h"
#include "check_brackets.h"
#include "cdio.h"
#include "comparison.h"

int main() {
    setbuf(stdout, NULL);
    List stack_list = NULL;

    Stack stack_array = {0};
    stack_array.top = -1;

    int rc = 0;
    char elem;
    int amount = 0;

    List *ptrs = NULL;
    List tmp = NULL;

    int choice = -1;
    while (choice) {
        printf("Choose an action:\n"
               "1-Push element on the array stack\n"
               "2-Pop element of the array stack\n"
               "3-Push element on the list stack\n"
               "4-Pop element of the list stack\n"
               "5-Checking the correct placement of brackets in the array stack\n"
               "6-Checking the correct placement of brackets in the list stack\n"
               "7-Output the array stack\n"
               "8-Output the list stack\n"
               "9-Comparison of time and memory when working with two algorithms\n"
               "0-Exit\n");
        printf("Enter a choice:\n");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input.\n");
            choice = -1;
            scanf("%*[^\n]");
            continue;
        }
        getchar();
        switch (choice) {
            case 0:
                break;
            case 1:
                printf("Input the symbol:\n");
                if (scanf("%c", &elem) != 1 || getchar() != '\n'){
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                if (push_elem(elem, &stack_array))
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                break;
            case 2:
                if (pop_elem(&stack_array))
                {
                    puts("Empty stack.\n");
                    return EMPTY_STACK;
                }
                break;
            case 3:
                printf("Input the symbol:\n");
                if (scanf("%c", &elem) != 1 || getchar() != '\n'){
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                if (add_elem(elem, &stack_list, ptrs, &amount))
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                break;
            case 4:
                ++amount;
                ptrs = realloc(ptrs, amount * sizeof(Node *));
                tmp = stack_list;
                ptrs[amount - 1] = tmp;
                if (del_elem(&stack_list))
                {
                    puts("Empty stack.\n");
                    return EMPTY_STACK;
                }
                break;
            case 5:
                stack_array.top = -1;
                rc = check_brackets_array(&stack_array);
                if (rc == OVERFLOW_STACK)
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                else if (rc == NONE)
                    puts("No brackets.");
                else if (rc == TRUE)
                    puts("Correct brackets.\n");
                else if (rc == FALSE)
                    puts("Incorrect brackets.\n");
                break;
            case 6:
                stack_list = NULL;
                rc = check_brackets_list(&stack_list, ptrs, amount);
                if (rc == OVERFLOW_STACK)
                {
                    puts("Overflow stack.\n");
                    return OVERFLOW_STACK;
                }
                else if (rc == NONE)
                    puts("No brackets.");
                else if (rc == TRUE)
                    puts("Correct brackets.\n");
                else if (rc == FALSE)
                {
                    free_list(&stack_list);
                    puts("Incorrect brackets.\n");
                }
                break;
            case 7:
                output_array(&stack_array);
                break;
            case 8:
                output_list(&stack_list, amount, ptrs);
                break;
            case 9:
                rc = comparison();
                if (rc)
                    return rc;
                break;
        }
    }
    if (stack_list)
        free_list(&stack_list);
    if (ptrs)
        free(ptrs);
    return OK;
}

