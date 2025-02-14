#include <stdio.h>
#include <limits.h>

int setBitNumber(int n)
{
    // Below steps set bits after
    // MSB (including MSB)

    // Suppose n is 273 (binary
    // is 100010001). It does following
    // 100010001 | 010001000 = 110011001
    n |= n >> 1;

    // This makes sure 4 bits
    // (From MSB and including MSB)
    // are set. It does following
    // 110011001 | 001100110 = 111111111
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    // The naive approach would increment n by 1,
    // so only the MSB+1 bit will be set,
    // So now n theoretically becomes 1000000000.
    // All the would remain is a single bit right shift:
    //    n = n + 1;
    //    return (n >> 1);
    //
    // ... however, this could overflow the type.
    // To avoid overflow, we must retain the value
    // of the bit that could overflow:
    //     n & (1 << ((sizeof(n) * CHAR_BIT)-1))
    // and OR its value with the naive approach:
    //     ((n + 1) >> 1)
    n = ((n + 1) >> 1);
    return n;
}

int setBitNumberOr(int n)
{
    // Below steps set bits after
    // MSB (including MSB)

    // Suppose n is 273 (binary
    // is 100010001). It does following
    // 100010001 | 010001000 = 110011001
    n |= n >> 1;

    // This makes sure 4 bits
    // (From MSB and including MSB)
    // are set. It does following
    // 110011001 | 001100110 = 111111111
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    // The naive approach would increment n by 1,
    // so only the MSB+1 bit will be set,
    // So now n theoretically becomes 1000000000.
    // All the would remain is a single bit right shift:
    //    n = n + 1;
    //    return (n >> 1);
    //
    // ... however, this could overflow the type.
    // To avoid overflow, we must retain the value
    // of the bit that could overflow:
    //     n & (1 << ((sizeof(n) * CHAR_BIT)-1))
    // and OR its value with the naive approach:
    //     ((n + 1) >> 1)
    n = ((n + 1) >> 1) |
        (n & (1 << ((sizeof(n) * CHAR_BIT) - 1)));
    return n;
}

int setBitNumberDivide(int n)
{
	if (n == 0)
		return 0;

	int msb = 0;
	n = n / 2;
	while (n != 0) {
		n = n / 2;
		msb++;
	}

	return (1 << msb);
}


int main()
{
    int n = 273;
    printf("\n%d\n", n);
    printf("%d\n", setBitNumber(n));
    printf("%d\n", setBitNumberOr(n));
    printf("%d\n", setBitNumberDivide(n));
    
    n = -273;
    printf("\n%d\n", n);
    printf("%d\n", setBitNumber(n));
    printf("%d\n", setBitNumberOr(n));
    printf("%d\n", setBitNumberDivide(n));
    
    n = 0;
    printf("\n%d\n", n);
    printf("%d\n", setBitNumber(n));
    printf("%d\n", setBitNumberOr(n));
    printf("%d\n", setBitNumberDivide(n));
    
    n = ~(int)0;
    printf("\n%d\n", n);
    printf("%d\n", setBitNumber(n));
    printf("%d\n", setBitNumberOr(n));
    printf("%d\n", setBitNumberDivide(n));
    
    return 0;
}