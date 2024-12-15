
// C program to check if given
// number is power of 2 or not

#include <stdio.h>

#define TRUE 1
#define FALSE 0

unsigned IsPowerOfTwo(int n)
{
    if (n == 0)
        return FALSE;
    while (n != 1)
    {
        if (n % 2 != 0)
            return FALSE;
        n /= 2;
    }

    return TRUE;
}

unsigned IsPowerOfTwoa(int n)
{
    if (n == 0)
        return FALSE;

    int test = n & (n - 1);
    if (test)
        return FALSE;
    else
        return TRUE;
}

int main(int argc, char **argv)
{
    int testnum = 31;
    unsigned result = IsPowerOfTwo(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");
    result = IsPowerOfTwoa(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");

    testnum = -31;
    result = IsPowerOfTwo(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");
    result = IsPowerOfTwoa(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");

    testnum = 64;
    result = IsPowerOfTwo(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");
    result = IsPowerOfTwoa(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");

    testnum = -64;
    result = IsPowerOfTwo(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");
    result = IsPowerOfTwoa(testnum);
    printf("%d is %s power of 2\n", testnum, result ? "" : "not");
}
