#include "input_output.h"
#include "multiplication.h"
#include "rounding.h"

int main(void)
{
    setbuf(stdout, NULL);
    char num1[SIZE_NUM1 + 1];
    char num2[SIZE_NUM2 + 1];
    int len1;
    int len2;
    int rc = read_numbers(num1, num2, &len1, &len2);
    if (rc == INPUT_ERROR)
    {
        printf("Input error.\n");
        return INPUT_ERROR;
    }
    else if (rc == OVERFLOW_MANTISSA)
    {
        printf("Overflow mantissa.\n");
        return OVERFLOW_MANTISSA;
    }
    else if (rc == OVERFLOW_INT)
    {
        printf("Overflow integer.\n");
        return OVERFLOW_INT;
    }
    int count_e = 0;
    int count_point = 0;
    int index_e = -1;
    int index_point = -1;

    if (search_exp_point(num1, &len1, &count_e, &count_point, &index_e, &index_point) != OK)
    {
        printf("Input error.\n");
        return INPUT_ERROR;
    }
    int result[RES_SIZE] = {0};
    if (count_e)
    {
        rc = multiplication(result, num1, num2, len2, index_e - 1);
        if (rc == INPUT_ERROR)
        {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        else if (rc == EMPTY_INT)
        {
            printf("Empty integer.\n");
            return EMPTY_INT;
        }
        else if (rc == EMPTY_MANTISSA)
        {
            printf("Empty mantissa.\n");
            return EMPTY_MANTISSA;
        }
        else if (rc == OVERFLOW_MANTISSA)
        {
            printf("Overflow mantissa.\n");
            return OVERFLOW_MANTISSA;
        }
    }
    else
    {
        rc = multiplication(result, num1, num2, len2, len1 - 1);
        if (rc == INPUT_ERROR)
        {
            printf("Input error.\n");
            return INPUT_ERROR;
        }
        else if (rc == EMPTY_INT)
        {
            printf("Empty integer.\n");
            return EMPTY_INT;
        }
        else if (rc == EMPTY_MANTISSA)
        {
            printf("Empty mantissa.\n");
            return EMPTY_MANTISSA;
        }
        else if (rc == OVERFLOW_MANTISSA)
        {
            printf("Overflow mantissa.\n");
            return OVERFLOW_MANTISSA;
        }
    }
    int start_index = 0;
    int exponent = 0;
    rc = search_start_and_exp(result, num1, len1, count_e, count_point, &start_index, &exponent, index_e, index_point);
    if (rc == OVERFLOW_EXP)
    {
        printf("Overflow exponent.\n");
        return OVERFLOW_EXP;
    }
    else if (rc == INPUT_ERROR)
    {
        printf("Input error.\n");
        return INPUT_ERROR;
    }
    else if (rc == EMPTY_EXP)
    {
        printf("Empty exponent.\n");
        return EMPTY_EXP;
    }
    if (start_index < RES_SIZE / 2)
        rounding(result, &start_index, &exponent);
    printf("Result:\n");
    if (exponent > 99999 || exponent < -99999)
    {
        printf("Overflow exponent.\n");
        return OVERFLOW_EXP;
    }
    print_to_normal(num1, num2, result, start_index, exponent);
    return OK;
}

