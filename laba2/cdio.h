#ifndef CDIO_H
#define CDIO_H

void check_input(int rc);
int read_table(FILE *f, subscriber *subscribers, int *i);
void print_src_table(const subscriber *subscribers, int n);
void print_key_table(type_key_table *key_table, int n);
void print_sorted_src_table(type_key_table *key_table, subscriber *subscribers, int n);
void create_key_table(const subscriber *subscribers, int n, type_key_table *key_table);

#endif //CDIO_H
