
#include <stdio.h>
#include <stdlib.h>

long *diagonal_sum(long matrix[][4], unsigned size)
{
    long *sums = (long *)malloc(2 * size * sizeof(long));
    for (unsigned r = 0; r < 2 * size; r++)
    {
        sums[r] = 0;
    }
    for (unsigned r = 0; r < size; r++)
    {
        for (unsigned c = 0; c < size; c++)
        {
            if (r >= c)
            {
                sums[r - c] += matrix[r][c];
            }
            else
            {
                sums[size + c - r] += matrix[r][c];
            }
        }
    }
    return sums;
}

long *diagonal_sum2(long matrix[][4], unsigned size)
{
    long *sums = (long *)malloc(2 * size * sizeof(long));
    for (unsigned r = 0; r < 2 * size; r++)
    {
        sums[r] = 0;
    }
    for (unsigned r = 0; r < size; r++)
    {
        // primary
        sums[0] += matrix[r][r];
        // secondary
        sums[1] += matrix[r][size-1-r];
    }
    return sums;
}

int main(int argc, char **argv)
{

    /*
1 2 3 4
4 3 2 1
7 8 9 6
6 5 4 3

    */
    long matrix[][4] = {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4}
        };

    // long matrix[][4] = {
    //     {1,2,3,4},
    //     {4,3,2,1},
    //     {7,8,9,6},
    //     {6,5,4,3}
    //     };

    // long matrix[][4] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8}};

    unsigned size = 4;
    long *sums = diagonal_sum(matrix, size);
    for (unsigned i = 0; i < 2 * size; i++)
    {
        if (!i) puts("primary");
        printf("sum %u = %ld\n", i, sums[i]);
    }

    for (unsigned r = 0; r < size; r++)
    {
        for (unsigned c = 0; c < size / 2; c++)
        {
            long temp = matrix[r][c];
            matrix[r][c] = matrix[r][size - 1 - c];
            matrix[r][size - 1 - c] = temp;
        }
    }

    sums = diagonal_sum(matrix, size);
    for (unsigned i = 0; i < 2 * size; i++)
    {
        if (!i) puts("secondary");
        printf("sum %u = %ld\n", i, sums[i]);
    }

    sums = diagonal_sum2(matrix, size);
    printf("primary: %ld\n", sums[0]);
    printf("secondary: %ld\n", sums[1]);
}
