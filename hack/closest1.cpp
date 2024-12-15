
#include <iostream>
#include <cstdint>

// using namespace std;

int findClosest1ToMSBa(uint64_t n) {
    if (n == 0) return -1; // No bits are set

    int msbIndex = 63 - __builtin_clzll(n); // Find the index of the MSB
    return msbIndex;
}

int findClosest1ToMSBb(uint64_t n) {
    if (n == 0) return -1; // No bits are set

    int msbIndex = -1;
    while (n != 0) {
        n >>= 1;
        msbIndex++;
    }
    return msbIndex;
}

int setBitNumber(int n)
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
int main2() {

	int n = 0;
	// printf("%d \n",setBitNumber(n));
    std::cout << "setBitNumber: " << setBitNumber(n) << std::endl;
	n = ~(int)0; // test for possible overflow
	int ns = (unsigned int)setBitNumber(n);
    std::cout << "n: " << n << std::endl;
    std::cout << "setBitNumber: " << ns << std::endl;

	// printf("%d",ns);

	return 0;
}


int main() {
    uint64_t n = 0x8000000000000001; // Example number
    // n = 0x80000000001; // Example number
    // n = 1;
    int index = findClosest1ToMSBa(n);
    std::cout << "Index of closest 1 to MSB: " << index << std::endl;
    index = findClosest1ToMSBb(n);
    std::cout << "Index of closest 1 to MSB: " << index << std::endl;

    main2();
    return 0;
}
