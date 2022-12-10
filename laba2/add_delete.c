#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "errors.h"
#include "constants_declarations.h"
#include "add_delete.h"

int add_record(FILE *f, subscriber *subscribers, int *n)
{
    if (*n == ARR_SIZE)
        return OVERFLOW_ARRAY;
    printf("Enter a new record:\nEnter last name (up to 20 characters, without spaces):\n");
    if (scanf("%20s", subscribers[*n].last_name) != 1)
        return INPUT_ERROR;
    if (!isspace(getchar()))
        return OVERFLOW_LASTNAME;
    fprintf(f, "\n");
    fprintf(f, "%s ", subscribers[*n].last_name);
    printf("Enter name (up to 20 characters, without spaces):\n");
    if (scanf("%20s", subscribers[*n].name) != 1)
        return INPUT_ERROR;
    if (!isspace(getchar()))
        return OVERFLOW_NAME;
    fprintf(f, "%s ", subscribers[*n].name);
    printf("Enter telephone (up to 15 characters, without spaces):\n");
    if (scanf("%15s", subscribers[*n].telephone) != 1)
        return INPUT_ERROR;
    if (!isspace(getchar()))
        return OVERFLOW_TEL;
    fprintf(f, "%s ", subscribers[*n].telephone);
    printf("Enter address (up to 30 characters, without spaces):\n");
    if (scanf("%30s", subscribers[*n].address) != 1)
        return INPUT_ERROR;
    if (!isspace(getchar()))
        return OVERFLOW_ADDRESS;
    fprintf(f, "%s ", subscribers[*n].address);
    printf("Select status kind (personal - 0 or service - 1):\n");
    int kind;
    if (scanf("%d", &kind) != 1)
        return INPUT_ERROR;
    subscribers[*n].kind = kind;
    if (subscribers[*n].kind == KIND_PERSONAL)
    {
        printf("Enter day of birth (an integer from 1 to 31):\n");
        if (scanf("%d", &subscribers[*n].status.personal.day) != 1)
            return INPUT_ERROR;
        if (subscribers[*n].status.personal.day < 1 || subscribers[*n].status.personal.day > 31)
            return INCORRECT_DAY;
        fprintf(f, "%d ", subscribers[*n].status.personal.day);
        printf("Enter month of birth (up to 9 characters, without spaces):\n");
        if (scanf("%9s", subscribers[*n].status.personal.month) != 1)
            return INPUT_ERROR;
        if (!isspace(getchar()))
            return OVERFLOW_MONTH;
        fprintf(f, "%s ", subscribers[*n].status.personal.month);
        printf("Enter year of birth (an integer from 1800 to 2021):\n");
        if (scanf("%d", &subscribers[*n].status.personal.year) != 1)
            return INPUT_ERROR;
        if (!isspace(getchar()) || subscribers[*n].status.personal.year > 2021
            || subscribers[*n].status.personal.year < 1800)
            return INCORRECT_YEAR;
        fprintf(f, "%d", subscribers[*n].status.personal.year);
    }
    else if (subscribers[*n].kind == KIND_SERVICE)
    {
        printf("Enter a position in the company (up to 15 characters, without spaces):\n");
        if (scanf("%15s", subscribers[*n].status.service.position) != 1)
            return INPUT_ERROR;
        if (!isspace(getchar()))
            return OVERFLOW_POSITION;
        fprintf(f, "%s ", subscribers[*n].status.service.position);
        printf("Enter company (up to 30 characters, without spaces):\n");
        if (scanf("%30s", subscribers[*n].status.service.company) != 1)
            return INPUT_ERROR;
        if (!isspace(getchar()))
            return OVERFLOW_COMPANY;
        fprintf(f, "%s", subscribers[*n].status.service.company);
    }
    else
        return INPUT_ERROR;
    ++(*n);
    return OK;
}


void delete_record(subscriber *subscribers, int *n, const char *filename)
{
    printf("Select a field from the list to delete:\n1 - last name\n2 - name\n3 - telephone\n4 - address\n"
           "5 - day of birth\n6 - month of birth\n7 - year of birth\n8 - position\n9 - company\nChoice: ");
    int src_n = *n;
    int choice;
    scanf("%d", &choice);
    char value_c[SIZE_COMPANY + 1];
    int value_i;
    switch(choice)
    {
        case 1:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].last_name, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 2:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].name, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 3:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].telephone, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 4:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].address, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 5:
            printf("Enter value of this field:\n");
            scanf("%d", &value_i);
            for (int i = 0; i < *n; ++i)
                if(subscribers[i].status.personal.day == value_i)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 6:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].status.personal.month, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 7:
            printf("Enter value of this field:\n");
            scanf("%d", &value_i);
            for (int i = 0; i < *n; ++i)
                if(subscribers[i].status.personal.year == value_i)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 8:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].status.service.position, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        case 9:
            printf("Enter value of this field:\n");
            scanf("%s", value_c);
            for (int i = 0; i < *n; ++i)
                if(strcmp(subscribers[i].status.service.company, value_c) == 0)
                {
                    for (int j = i; j < *n - 1; ++j)
                        subscribers[j] = subscribers[j + 1];
                    --(*n);
                }
            break;
        default:
            printf("Incorrect choice.\n");
            break;
    }
    if (*n == src_n)
        printf("Such record doesn't exist.\n");
    else
    {
        FILE *f;
        f = fopen(filename, "w");
        for (int i = 0; i < *n; ++i)
        {
            fprintf(f, "%s %s %s %s ", subscribers[i].last_name,
                    subscribers[i].name, subscribers[i].telephone, subscribers[i].address);
            if (subscribers[i].kind == KIND_PERSONAL)
                fprintf(f, "%d %s %d", subscribers[i].status.personal.day,
                        subscribers[i].status.personal.month, subscribers[i].status.personal.year);
            else
                fprintf(f, "%s %s", subscribers[i].status.service.position,
                        subscribers[i].status.service.company);
            fprintf(f, "\n");
        }
        fclose(f);
    }
}