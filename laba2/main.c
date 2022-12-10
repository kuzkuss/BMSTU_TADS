#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "constants_declarations.h"
#include "errors.h"
#include "cdio.h"
#include "add_delete.h"
#include "search.h"
#include "sorting.h"
#include "time_measurement.h"

int main(int argc, char **argv)
{
    srand(time(0));
    setbuf(stdout, NULL);
    if (argc != 2)
    {
        printf("Key error.\n");
        return KEY_ERROR;
    }
    FILE *f_in;
    if (!(f_in = fopen(argv[1], "r")))
    {
        printf("File doesn't exist");
        return FILE_ERROR;
    }
    subscriber arr_subscribers[ARR_SIZE];
    int amount = 0;
    int rc = read_table(f_in, arr_subscribers, &amount);
    fclose(f_in);
    if (rc)
    {
        check_input(rc);
        return rc;
    }
    if (amount < 40)
    {
        printf("Too few records.\n");
        return FEW_RECORDS;
    }
    type_key_table key_table[ARR_SIZE];
    int choice = -1;
    while (choice != 0)
    {
        printf("Choose an action:\n1-View source table\n"
               "2-Adding one record to the end of the table\n"
               "3-Deleting a record by the specified field\n"
               "4-Search for friends who have birthday in the coming week\n"
               "5-Viewing a sorted key table when the source table is unsorted\n"
               "6-Sorted sorce table output\n"
               "7-Output the sorted source table using the sorted key table\n"
               "8-Output the results of comparing the efficiency of the program when "
               "processing data in the source table and in the key table\n"
               "9-Output the results of using various sorting algorithms\n0-Exit\n");
        printf("Enter a choice:\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Incorrect input.\n");
            choice = -1;
            scanf("%*[^\n]");
            continue;
        }
        switch(choice)
        {
            case 0:
                break;
            case 1:
                print_src_table(arr_subscribers, amount);
                break;
            case 2:
                f_in = fopen(argv[1], "a");
                rc = add_record(f_in, arr_subscribers, &amount);
                fclose(f_in);
                if (rc)
                {
                    check_input(rc);
                    return rc;
                }
                break;
            case 3:
                delete_record(arr_subscribers, &amount, argv[1]);
                break;
            case 4:
                search_birthdays(arr_subscribers, amount);
                break;
            case 5:
                create_key_table(arr_subscribers, amount, key_table);
                bubble_sort_key_table(key_table, amount);
                print_src_table(arr_subscribers, amount);
                print_key_table(key_table, amount);
                break;
            case 6:
                bubble_sort_source_table(arr_subscribers, amount);
                print_src_table(arr_subscribers, amount);
                break;
            case 7:
                create_key_table(arr_subscribers, amount, key_table);
                bubble_sort_key_table(key_table, amount);
                print_sorted_src_table(key_table, arr_subscribers, amount);
                break;
            case 8:
                //create_key_table(arr_subscribers, amount, key_table);
                printf("Bubble sort:\n");
                printf("┌──────────────┬─────────────────────────────────────┬──────────────────────────────────┐\n");
                printf("│   Parameter  │ Processing data in the source table │ Processing data in the key table │\n");
                printf("├──────────────┼─────────────────────────────────────┼──────────────────────────────────┤\n");
                printf("│%-14s│%-37lf│%-34lf│\n", "time (us)", time_src(arr_subscribers, amount),
                       time_key(key_table, amount));
                printf("├──────────────┼─────────────────────────────────────┼──────────────────────────────────┤\n");
                printf("│%-14s│%-37lld│%-34lld│\n", "memory (bytes)", sizeof (arr_subscribers),
                       sizeof arr_subscribers + sizeof key_table);
                printf("└──────────────┴─────────────────────────────────────┴──────────────────────────────────┘\n");
                break;
            case 9:
                //create_key_table(arr_subscribers, amount, key_table);
                printf("Key table:\n");
                printf("┌─────────────┬────────────┐\n");
                printf("│ Bubble sort │ Quick sort │\n");
                printf("├─────────────┼────────────┤\n");
                printf("│%-13lf│%-12lf│\n", time_key(key_table, amount),
                       time_quicksort_key(key_table, amount));
                printf("└─────────────┴────────────┘\n");
                printf("Source table:\n");
                printf("┌─────────────┬────────────┐\n");
                printf("│ Bubble sort │ Quick sort │\n");
                printf("├─────────────┼────────────┤\n");
                printf("│%-13lf│%-12lf│\n", time_src(arr_subscribers, amount),
                       time_quicksort_src(arr_subscribers, amount));
                printf("└─────────────┴────────────┘\n");
                break;
        }
    }
    return rc;
}
