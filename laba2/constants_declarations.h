#ifndef CONSTANTS_DECLARATIONS_H
#define CONSTANTS_DECLARATIONS_H

#define SIZE_LASTNAME 20
#define SIZE_NAME 20
#define SIZE_TEL 15
#define SIZE_ADDRESS 30

#define SIZE_MONTH 10

#define SIZE_POS 15
#define SIZE_COMPANY 30

#define ARR_SIZE 100

struct personal_status
{
    int day;
    char month[SIZE_MONTH];
    int year;
};

struct service_status
{
    char position[SIZE_POS + 1];
    char company[SIZE_COMPANY + 1];
};

union sub_status
{
    struct personal_status personal;
    struct service_status service;
};

typedef enum{KIND_PERSONAL, KIND_SERVICE} kind_status;

typedef struct
{
    char last_name[SIZE_LASTNAME + 1];
    char name[SIZE_NAME + 1];
    char telephone[SIZE_TEL + 1];
    char address[SIZE_ADDRESS + 1];
    union sub_status status;
    kind_status kind;
} subscriber;

typedef struct
{
    int index;
    char last_name[SIZE_LASTNAME];
} type_key_table;

#endif //CONSTANTS_DECLARATIONS_H
