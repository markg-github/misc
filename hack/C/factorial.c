
#include <stdio.h>
#include <stdlib.h>

unsigned long factorial_recur(unsigned n)
{
    if (2 > n)
    {
        return 1;
    }
    return n * factorial_recur(n - 1);
}

unsigned long factorial_iter(unsigned n)
{
    if (2 > n)
    {
        return 1;
    }
    unsigned long result = n;
    while (1 < --n)
    {
        result *= n;
    }
    return result;
}

int main(int argc, char **argv)
{
    unsigned n = 5;

    printf("%u factorial = %lu\n", n, factorial_iter(n));

    n = 6;
    printf("%u factorial = %lu\n", n, factorial_iter(n));
    
    n = 7;
    printf("%u factorial = %lu\n", n, factorial_iter(n));
    
    n = 8;
    printf("%u factorial = %lu\n", n, factorial_iter(n));
    
}