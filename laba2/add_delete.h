#ifndef ADD_DELETE_H
#define ADD_DELETE_H

int add_record(FILE *f, subscriber *subscribers, int *n);
void delete_record(subscriber *subscribers, int *n, const char *filename);


#endif //ADD_DELETE_H
