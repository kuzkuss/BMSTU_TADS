#include <string.h>
#include "matrix.h"

#define TRUE 1
#define FALSE 0

static int search_path(int index, char *path, weight_t matrix[][N], vertex_t *vertex, int *count, int amount_v)
{
    for (int i = 0; i < amount_v; ++i)
    {
        if (vertex[index].name != vertex[i].name && vertex[index].weight - matrix[i][index].length - matrix[i][index].duty == vertex[i].weight)
        {
            if (vertex[i].name == 'A')
            {
                path[(*count)++] = vertex[i].name;
                return TRUE;
            }
            if (!search_path(i, path, matrix, vertex, count, amount_v))
                continue;
            else
            {
                path[(*count)++] = vertex[i].name;
                return TRUE;
            }
        }
    }
    return FALSE;
}

int Dijkstra_alg(vertex_t *vertex, weight_t matrix[][N], char *path, int amount_v)
{
    vertex[0].weight = 0;
    for (int i = 0; i < amount_v; ++i)
    {
        for (int j = 0; j < amount_v; ++j)
        {
            if (matrix[i][j].length != 0)
            {
                if (matrix[i][j].length + matrix[i][j].duty + vertex[i].weight < vertex[j].weight)
                {
                    vertex[j].weight = matrix[i][j].length + matrix[i][j].duty + vertex[i].weight;
                }
            }
        }
    }

    int weight_path = 0;
    for (int i = 0; i < amount_v; ++i)
    {
        if (vertex[i].name == 'B')
        {
            weight_path = vertex[i].weight;
            printf("%d\n", weight_path);
            int count = 0;
            search_path(i, path, matrix, vertex, &count, amount_v);
            path[count++] = 'B';
            break;
        }
    }
    return weight_path;
}
