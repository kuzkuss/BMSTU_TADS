#include "multiplication.h"
#include <ctype.h>
#include <stdlib.h>

int search_exp_point(char *num, int *len, int *count_exp, int *count_point, int *index_exp, int *index_point)
{
    for (int i = 0; i < *len; ++i)
    {
        if (num[i] == 'e' || num[i] == 'E')
        {
            if (++(*count_exp) > 1)
                return INPUT_ERROR;
            (*index_exp) = i;
        }
        else if (num[i] == '.')
        {
            if (++(*count_point) > 1)
                return INPUT_ERROR;
            (*index_point) = i;
        }
    }
    if (*index_exp == 0)
    {
        if (*len >= SIZE_NUM1 - 1)
            return INPUT_ERROR;
        for (int i = *len; i >= 0; --i)
            num[i] = num[i - 1];
        num[0] = '1';
        ++(*len);
        ++(*index_exp);
        num[*len] = '\0';
    }
    return OK;
}

int multiplication(int *res, const char *num1, const char *num2, int len2, int start)
{
    int index_res = RES_SIZE - 1;
    int count_digits = 0;
    for (int i = start; i >= 0; --i)
    {
        if (isdigit(num1[i]))
        {
            if (++count_digits >= SIZE_NUM2 - 1)
                return OVERFLOW_MANTISSA;
            int current_index = index_res;
            for (int j = len2 - 1; j >= 0; --j)
            {
                if (isdigit(num2[j]))
                {
                    int cur_num = res[index_res] + (num1[i] - '0') * (num2[j] - '0');
                    res[index_res] = cur_num % 10;
                    res[index_res - 1] += cur_num / 10;
                    --index_res;
                }
                else if ((num2[j] != '+' && num2[j] != '-') || (j != 0))
                    return INPUT_ERROR;
            }
            if (index_res == RES_SIZE - 1)
                return EMPTY_INT;
            index_res = current_index - 1;
        }
        else if (num1[i] !='.' && ((num1[i] != '+' && num1[i] != '-') || (i != 0)))
            return INPUT_ERROR;
    }
    if (count_digits == 0)
        return EMPTY_MANTISSA;
    return OK;
}

int search_start_and_exp(int *res, const char *num1, int len1, int count_e, int count_point, int *start, int *exp, int index_e, int index_point)
{
    for (int i = 0; i < RES_SIZE && res[i] == 0; ++i)
        *start = i;
    ++(*start);
    if (res[0] != 0)
        *start = 0;
    if (count_e)
    {
        char c_exp[SIZE_EXP];
        int j = 0;
        if (len1 - index_e > 7)
            return OVERFLOW_EXP;
        for (int i = index_e + 1; i < len1; ++i, ++j)
        {
            if (!isdigit(num1[i]) && ((num1[i] != '+' && num1[i] != '-') || i != index_e + 1))
                return INPUT_ERROR;
            c_exp[j] = num1[i];
        }
        if (j == 0)
            return EMPTY_EXP;
        c_exp[j] = '\0';
        *exp = atoi(c_exp);
        if (*exp > 99999)
            return OVERFLOW_EXP;
    }
    if (count_point)
    {
        if (count_e)
            *exp += RES_SIZE + 1 - index_e + index_point - *start;
        else
            *exp += RES_SIZE + 1 - len1 + index_point - *start;
    }
    else
        *exp += RES_SIZE - *start;
    return OK;
}
