#include <stdio.h>
#include <string.h>
#include "constants_declarations.h"
#include "search.h"

void search_birthdays(const subscriber *subscribers, int n)
{
    printf("Enter month of the next week:\n");
    char month[SIZE_MONTH + 1];
    scanf("%s", month);
    printf("Enter the first day of the week:\n");
    int first_day;
    scanf("%d", &first_day);
    int last_day = first_day + 6;
    int count = 0;
    printf("┌────────────────────┬────────────────────┬"
           "───────────────┬──────────────────────────────┬─────┬───────────┬──────┐\n");
    printf("│     last name      │        name        │"
           "   telephone   │            address           │ day │   month   │ year │\n");
    for (int i = 0; i < n; ++i)
        if (subscribers[i].kind == KIND_PERSONAL &&
            strcmp(subscribers[i].status.personal.month, month) == 0
            && first_day <= subscribers[i].status.personal.day
            && subscribers[i].status.personal.day <= last_day)
        {
            printf("├────────────────────┼────────────────────┼───────────────"
                   "┼──────────────────────────────┼─────┼───────────┼──────┤\n");
            printf("│%-20s│%-20s│%-15s│%-30s│%-5d│%-11s│%-6d│\n", subscribers[i].last_name,
                   subscribers[i].name, subscribers[i].telephone, subscribers[i].address,
                   subscribers[i].status.personal.day, subscribers[i].status.personal.month,
                   subscribers[i].status.personal.year);
            ++count;
        }
    if (!count)
    {
        printf("└────────────────────┴────────────────────┴───────────────┴"
               "──────────────────────────────┴─────┴───────────┴──────┘\n");
        printf("No birthdays in the next week.\n");
    }
    else
        printf("└────────────────────┴────────────────────┴───────────────┴"
               "──────────────────────────────┴─────┴───────────┴──────┘\n");

}
