#include "input_output.h"
#include <string.h>
#include <ctype.h>

int read_numbers(char *num1, char *num2, int *len1, int *len2)
{
    printf("Multipluing a real number by an integer:\n");
    printf("Enter a real number:\n");
    printf("|                              |\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    if (scanf("%s", num1) != 1)
        return INPUT_ERROR;
    if (getchar() != '\n')
        return INPUT_ERROR;
    *len1 = strlen(num1);
    if (*len1 > SIZE_NUM1 - 1)
        return OVERFLOW_MANTISSA;

    printf("Enter an integer:\n");
    printf("|                              |\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    if (scanf("%s", num2) != 1)
        return INPUT_ERROR;
    if (getchar() != '\n')
        return INPUT_ERROR;
    *len2 = strlen(num2);
    if ((*len2 > SIZE_NUM2 - 1) || (*len2 == SIZE_NUM2 - 1 && num2[0] != '+' && num2[0] != '-'))
        return OVERFLOW_INT;
    return OK;
}

void print_to_normal(const char *num1, const char *num2, const int *res, int start, int exp)
{
    if ((num1[0] == '-') ^ (num2[0] == '-'))
        printf("-");
    else
        printf("+");
    printf("0.");
    int i;
    for (i = RES_SIZE - 1; i >= start; --i)
        if (res[i] != 0)
            break;
    int end = i + 1;
    int j;
    for (j = start; j < end; ++j)
        printf("%d", res[j]);
    if (j == start)
        printf("0");
    if (exp < 0)
    {
        printf("E");
        printf("%d", exp);
    }
    else
    {
        printf("E+");
        printf("%d", exp);
    }
}

