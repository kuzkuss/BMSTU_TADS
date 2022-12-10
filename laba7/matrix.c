#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "matrix.h"

static int index(char *str, vertex_t *vertex, int amount)
{
    for (int i = 0; i < amount; ++i)
    {
        if (vertex[i].name == str[0])
            return i;
    }
    return NOT_FOUND;
}

int input(char *filename, vertex_t *vertex, weight_t matrix[][N], int *amount_vertex)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        puts("File error");
        return FILE_ERROR;
    }
    while (!feof(f) && *amount_vertex < 100)
    {
        char cur_str[LEN_STR + 2];
        if (!fgets(cur_str, LEN_STR + 2, f))
        {
            if (ftell(f) == 0)
            {
                fclose(f);
                puts("File error");
                return FILE_ERROR;
            }
            fclose(f);
            puts("Input error");
            return INPUT_ERROR;
        }

        int len = strlen(cur_str);

        if (cur_str[len - 1] == '\n')
        {
            cur_str[len - 1] = '\0';
            len--;
        }

        if (len == 0)
        {
            fclose(f);
            puts("Empty string");
            return EMPTY_STRING;
        }

        if (len > LEN_STR)
        {
            fclose(f);
            puts("Overflow string");
            return OVERFLOW_STRING;
        }

        char *words[SIZE_WORDS + 1] = {};

        int i = 0;
        words[i] = strtok(cur_str, DELIMS);

        while (words[i])
        {
            i++;
            words[i] = strtok(NULL, DELIMS);
        }

        if (words[0][1] == '-')
        {
            words[0][1] = '\0';
        }
        else
        {
            fclose(f);
            puts("Input error");
            return INPUT_ERROR;
        }

        if (i == SIZE_WORDS)
        {
            int ind_first_v = index(words[0], vertex, *amount_vertex);
            if (ind_first_v == NOT_FOUND)
            {
                vertex[*amount_vertex].name = words[0][0];
                vertex[*amount_vertex].weight = INT_MAX;
                ind_first_v = *amount_vertex;
                (*amount_vertex)++;
            }
            int ind_second_v = index(words[1], vertex, *amount_vertex);
            if (ind_second_v == NOT_FOUND)
            {
                vertex[*amount_vertex].name = words[1][0];
                vertex[*amount_vertex].weight = INT_MAX;
                ind_second_v = *amount_vertex;
                (*amount_vertex)++;
            }
            if(strcmp(words[0], words[1]) == 0)
            {
                fclose(f);
                puts("Input error");
                return INPUT_ERROR;
            }
            matrix[ind_first_v][ind_second_v].duty = atoi(words[2]);
            if (matrix[ind_first_v][ind_second_v].duty <= 0)
            {
                fclose(f);
                puts("Input error");
                return INPUT_ERROR;
            }
            matrix[ind_first_v][ind_second_v].length = atoi(words[3]);
            if (matrix[ind_first_v][ind_second_v].length <= 0)
            {
                fclose(f);
                puts("Input error");
                return INPUT_ERROR;
            }
        }
        else
        {
            fclose(f);
            puts("Input error");
            return INPUT_ERROR;
        }

    }
    if (!feof(f))
    {
        fclose(f);
        puts("Input error");
        return INPUT_ERROR;
    }
    fclose(f);
    return OK;
}

void export_to_dot(FILE *f_out, const char *graph_name, weight_t matrix[][N], vertex_t *vertex, int n)
{
    fprintf(f_out, "digraph %s {\n", graph_name);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j].length != 0)
            {
                char weight[50] = {};
                sprintf(weight, "%d, %d", matrix[i][j].duty, matrix[i][j].length);
                fprintf(f_out, "%c -> %c [ label = \"%s\" ];\n", vertex[i].name, vertex[j].name, weight);
            }
        }

    fprintf(f_out, "}\n");
}

