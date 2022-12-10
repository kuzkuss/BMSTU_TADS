#include "rounding.h"

void rounding(int *res, int *start, int *exp)
{

    int end = RES_SIZE / 2 - *start;
    for (int i = 0; i < end; ++i)
    {
        if (res[RES_SIZE - 1] >= 5)
        {
            if (!(res[RES_SIZE - 2] = (res[RES_SIZE - 2] + 1) % 10))
            {
                res[RES_SIZE - 3] += 1;
                int j = RES_SIZE - 3;
                while (res[j] == 10)
                {
                    res[j] = 0;
                    res[j - 1] += 1;
                    --j;
                }
                if (j == *start - 1)
                {
                    *exp += 1;
                    rounding(res, &j, exp);
                    *start += end - i;
                    break;
                }
            }
        }
        for (int j = RES_SIZE - 1; j >= *start; --j)
            res[j] = res[j - 1];
        res[*start] = 0;
        ++(*start);
    }
}
