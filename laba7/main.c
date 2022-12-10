#include "matrix.h"
#include "alg_Dijkstra.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if(argc != 3)
    {
        puts("Key error");
        return KEY_ERROR;
    }

    puts("Finding a path in a graph from A to B");

    weight_t matrix[N][N] = { 0 };
    vertex_t vertex[N] = { 0 };

    int amount_v = 0;

    int rc = input(argv[1], vertex, matrix, &amount_v);
    if (rc)
        return rc;

    int choice = 0;
    do {
        puts("1 - Output graph\n"
             "2 - Output shortest path from A to B\n"
             "0 - Exit");

        puts("Enter a choice:");

        if (scanf("%d", &choice) != 1)
        {
            puts("Incorrect choice");
            break;
        }
        switch (choice)
        {
            case 0:
                break;
            case 1:
            {
                FILE *f_out = fopen(argv[2], "w");
                if (!f_out)
                {
                    puts("File error.");
                    return FILE_ERROR;
                }
                export_to_dot(f_out, "roads", matrix, vertex, amount_v);
                printf("Result in %s\n", argv[2]);
                printf("To convert to png format use the command: \"dot -T png %s -o filename.png\".\n", argv[2]);
                fclose(f_out);
                break;
            }
            case 2:
            {
                char shortest_path[N] = { 0 };
                int val_path = Dijkstra_alg(vertex, matrix, shortest_path, amount_v);
                printf("Shortest path: %s\nValue: %d\n", shortest_path, val_path);
            }
        }
    } while(choice != 0);
}
