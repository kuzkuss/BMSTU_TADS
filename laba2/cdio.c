#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "constants_declarations.h"
#include "cdio.h"

void check_input(int rc)
{
    if (rc == OVERFLOW_ARRAY)
        printf("Overflow array.\n");
    if (rc == INPUT_ERROR)
        printf("Input error.\n");
    if (rc == OVERFLOW_LASTNAME)
        printf("Overflow last name.\n");
    if (rc == OVERFLOW_NAME)
        printf("Overflow name.\n");
    if (rc == OVERFLOW_TEL)
        printf("Overflow telephone.\n");
    if (rc == OVERFLOW_ADDRESS)
        printf("Overflow address.\n");
    if (rc == OVERFLOW_POSITION)
        printf("Overflow position.\n");
    if (rc == OVERFLOW_COMPANY)
        printf("Overflow company.\n");
    if (rc == OVERFLOW_MONTH)
        printf("Overflow month.\n");
    if (rc == INCORRECT_DAY)
        printf("Incorrect day of birth.\n");
    if (rc == INCORRECT_YEAR)
        printf("Incorrect year of birth.\n");
}

int read_table(FILE *f, subscriber *subscribers, int *i)
{
    while (!feof(f))
    {
        if (*i >= ARR_SIZE)
            return OVERFLOW_ARRAY;
        if (fscanf(f, "%20s", subscribers[*i].last_name) != 1)
            return INPUT_ERROR;
        if (!isspace(fgetc(f)))
            return OVERFLOW_LASTNAME;
        if (fscanf(f, "%20s", subscribers[*i].name) != 1)
            return INPUT_ERROR;
        if (!isspace(fgetc(f)))
            return OVERFLOW_NAME;
        if (fscanf(f, "%15s", subscribers[*i].telephone) != 1)
            return INPUT_ERROR;
        if (!isspace(fgetc(f)))
            return OVERFLOW_TEL;
        if (fscanf(f, "%30s", subscribers[*i].address) != 1)
            return INPUT_ERROR;
        if (!isspace(fgetc(f)))
            return OVERFLOW_ADDRESS;
        char str[SIZE_POS];
        if (fscanf(f, "%15s", str) != 1)
            return INPUT_ERROR;
        int d;
        d = atoi(str);
        if ((!d) && strcmp(str, "0"))
        {
            if (!isspace(fgetc(f)))
                return OVERFLOW_POSITION;
            subscribers[*i].kind = KIND_SERVICE;
            strcpy(subscribers[*i].status.service.position, str);
            if (fscanf(f, "%30s", subscribers[*i].status.service.company) != 1)
                return INPUT_ERROR;
            char ch = fgetc(f);
            if (ch == EOF)
            {
                ++(*i);
                break;
            }
            if (!isspace(ch))
                return OVERFLOW_COMPANY;
        }
        else
        {
            if (d < 1 || d > 31)
                return INCORRECT_DAY;
            subscribers[*i].kind = KIND_PERSONAL;
            subscribers[*i].status.personal.day = d;
            if (fscanf(f, "%10s", subscribers[*i].status.personal.month) != 1)
                return INPUT_ERROR;
            if (!isspace(fgetc(f)))
                return OVERFLOW_MONTH;
            if (fscanf(f, "%d", &subscribers[*i].status.personal.year) != 1)
                return INPUT_ERROR;
            char ch = fgetc(f);
            if (ch == EOF)
            {
                ++(*i);
                break;
            }
            if (!isspace(ch) || subscribers[*i].status.personal.year > 2021
                || subscribers[*i].status.personal.year < 1800)
                return INCORRECT_YEAR;
        }
        ++(*i);
    }
    return OK;
}

void print_src_table(const subscriber *subscribers, int n)
{
    printf("Source table:\n");
    printf("┌───────┬────────────────────┬────────────────────┬"
           "───────────────┬──────────────────────────────┬─────┬───────────┬──────┬───────────────┬"
           "──────────────────────────────┐\n");
    printf("│ index │     last name      │        name        │"
           "   telephone   │            address           │ day │   month   │ year │   position    │"
           "            company           │\n");
    for (int i = 0; i < n; ++i)
    {
        printf("├───────┼────────────────────┼────────────────────┼"
               "───────────────┼──────────────────────────────┼─────┼───────────┼──────┼───────────────┼"
               "──────────────────────────────┤\n");
        printf("│%-7d│%-20s│%-20s│%-15s│%-30s│", i + 1, subscribers[i].last_name,
               subscribers[i].name, subscribers[i].telephone, subscribers[i].address);
        if (subscribers[i].kind == KIND_PERSONAL)
            printf("%-5d│%-11s│%-6d│%-15s│%-30s│\n", subscribers[i].status.personal.day,
                   subscribers[i].status.personal.month, subscribers[i].status.personal.year, "-", "-");
        else
            printf("%-5s│%-11s│%-6s│%-15s│%-30s│\n", "-", "-", "-",
                   subscribers[i].status.service.position, subscribers[i].status.service.company);
    }
    printf("└───────┴────────────────────┴────────────────────┴───────────────┴"
           "──────────────────────────────┴─────┴───────────┴──────┴───────────────┴"
           "──────────────────────────────┘\n");
}
void print_key_table(type_key_table *key_table, int n)
{
    printf("Key table:\n");
    printf("┌──────────────┬───────────┬────────────────────┐\n");
    printf("│ Source index │ New index │     last name      │\n");
    for (int i = 0; i < n; ++i)
    {
        printf("├──────────────┼───────────┼────────────────────┤\n");
        printf("│%-14d│%-11d│%-20s│\n", i + 1, key_table[i].index + 1, key_table[i].last_name);
    }
    printf("└──────────────┴───────────┴────────────────────┘\n");
}

void print_sorted_src_table(type_key_table *key_table, subscriber *subscribers, int n)
{
    printf("Sorted sorce table:\n");
    printf("┌───────┬────────────────────┬────────────────────┬"
           "───────────────┬──────────────────────────────┬─────┬───────────┬──────┬───────────────┬"
           "──────────────────────────────┐\n");
    printf("│ index │     last name      │        name        │"
           "   telephone   │            address           │ day │   month   │ year │   position    │"
           "            company           │\n");
    for (int i = 0; i < n; ++i)
    {
        printf("├───────┼────────────────────┼────────────────────┼"
               "───────────────┼──────────────────────────────┼─────┼───────────┼──────┼───────────────┼"
               "──────────────────────────────┤\n");
        printf("│%-7d│%-20s│%-20s│%-15s│%-30s│", key_table[i].index + 1, subscribers[key_table[i].index].last_name,
               subscribers[key_table[i].index].name,
               subscribers[key_table[i].index].telephone, subscribers[key_table[i].index].address);
        if (subscribers[key_table[i].index].kind == KIND_PERSONAL)
            printf("%-5d│%-11s│%-6d│%-15s│%-30s│\n", subscribers[key_table[i].index].status.personal.day,
                   subscribers[key_table[i].index].status.personal.month,
                   subscribers[key_table[i].index].status.personal.year, "-", "-");
        else
            printf("%-5s│%-11s│%-6s│%-15s│%-30s│\n", "-", "-", "-",
                   subscribers[key_table[i].index].status.service.position,
                   subscribers[key_table[i].index].status.service.company);
    }
    printf("└───────┴────────────────────┴────────────────────┴───────────────┴"
           "──────────────────────────────┴─────┴───────────┴──────┴───────────────┴"
           "──────────────────────────────┘\n");
}
void create_key_table(const subscriber *subscribers, int n, type_key_table *key_table)
{
    for (int i = 0; i < n; ++i)
    {
        key_table[i].index = i;
        strcpy(key_table[i].last_name, subscribers[i].last_name);
    }
}
