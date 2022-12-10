#include <stdlib.h>

#include "avl_tree.h"
#include "bin_tree.h"
#include "comparison.h"
#include "hash_table.h"
#include "errors.h"
#include "utils.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    if (argc != 2)
    {
        puts("Key error.");
        return KEY_ERROR;
    }

    FILE *f_in = fopen(argv[1], "r");
    if (!f_in)
    {
        puts("File error.");
        return FILE_ERROR;
    }

    bin_tree_node_t *bin_tree = NULL;
    avl_tree_node_t *avl_tree = NULL;

    FILE *f_out_bin = NULL;

    FILE *f_out_avl = NULL;

    hash_table_t *hash_table = NULL;

    int rc = OK;

    int choice = 0;
    do {
        puts("1 - Output binary search tree\n"
             "2 - Output AVL\n"
             "3 - Output hash table\n"
             "4 - Item search\n"
             "5 - Restruct hash table\n"
             "6 - Comparison of efficiency in time, memory and number "
                "of comparisons of different data structures\n"
             "0 - Exit");

	puts("Enter a choice:");

        if (scanf("%d", &choice) != 1)
        {
            puts("Incorrect choice");
            break;
        }
        switch (choice)
        {
            case 1:
            {
                rewind(f_in);
                bin_tree = create_bin_tree_from_file(f_in);
                if(!bin_tree)
                {
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                f_out_bin = fopen("bin_tree.gv", "w");
                if (!f_out_bin)
                {
                    puts("File error.");
                    return FILE_ERROR;
                }
                print_bin_tree(f_out_bin, bin_tree);
                puts("Result in bin_tree.gv.");
                puts("To convert to png format use the command: \"dot -T png bin_tree.gv -o bin_tree.png\".");
                fclose(f_out_bin);
                break;
            }
            case 2:
            {
                rewind(f_in);
                avl_tree = create_avl_tree_from_file(f_in);
                if(!avl_tree)
                {
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                avl_tree = balance_tree(avl_tree);
                f_out_avl = fopen("avl_tree.gv", "w");
                if (!f_out_avl)
                {
                    puts("File error.");
                    return FILE_ERROR;
                }
                print_avl_tree(f_out_avl, avl_tree);
                puts("Result in avl_tree.gv.");
                puts("To convert to png format use the command: \"dot -T png avl_tree.gv -o avl_tree.png\".");
                fclose(f_out_avl);
                break;
            }
            case 3:
            {
                rewind(f_in);
                hash_table = create_table(f_in);
                if(!hash_table)
                {
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                print_table(hash_table);
                break;
            }
            case 4:
            {
                char *word = NULL;
                puts("Enter you search word:");
                if (scanf("%ms", &word) != 1)
                {
                    puts("Input error.");
                    return INPUT_ERROR;
                }
                int comp_bin_tree = 0;
                int comp_avl_tree = 0;
                int comp_hash_table = 0;
                int comp_file = 0;

                if (find_bin_tree(bin_tree, word, &comp_bin_tree))
                    puts("Element was found in binary tree.");
                else
                    puts("Element wasn't found in binary tree.");

                if (find_avl_tree(avl_tree, word, &comp_avl_tree))
                    puts("Element was found in avl tree.");
                else
                    puts("Element wasn't found in avl tree.");

                if (find_hash_table(hash_table, word, &comp_hash_table))
                    puts("Element was found in hash table.");
                else
                    puts("Element wasn't found in hash table.");

                rewind(f_in);

                if (find_file(f_in, word, &comp_file) != -1)
                    puts("Element was found in file.");
                else
                    puts("Element wasn't found in file.");

                print_comparisons(comp_bin_tree, comp_avl_tree, comp_hash_table, comp_file);

                free(word);
                break;
            }
            case 5:
            {
                double avg_comp = count_comparisons(hash_table);
                printf("Current average number of comparisons: %lf\n", avg_comp);

                double max_comp = 0;
                puts("Enter the maximum average number of comparisons:");
                if (scanf("%lf", &max_comp) != 1 || max_comp <= 0)
                {
                    puts("Input error.");
                    return INPUT_ERROR;
                }

                if (avg_comp > max_comp)
                {
                    hash_table = restruct_hash_table(hash_table, max_comp);
                    if (hash_table)
                    {
                        puts("Average number of comparisons in hash table more than maximum average number of comparisons.\n"
                             "Hash table was restruct.");
                        print_table(hash_table);
                    }
                }
                break;
            }
            case 6:
            {
                rc = compare();
                if (rc)
                    choice = 0;
                break;
            }
        }
    } while(choice != 0);

    if (bin_tree)
        free_bin_tree(bin_tree);

    if (avl_tree)
        free_avl_tree(avl_tree);

    if (hash_table)
        free_table(hash_table);

    fclose(f_in);

    return rc;
}
