// Given an array arr[] of n integers and a target value,
// the task is to find whether there is a pair of elements
// in the array whose sum is equal to target.

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

unsigned FindSum(int target, int input_array[], unsigned input_array_size)
{
    for (unsigned i = 0; i < input_array_size; i++)
    {
        for (unsigned j = i + 1; j < input_array_size; j++)
        {
            int twosum = input_array[i] + input_array[j];
            if (twosum == target)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

unsigned BinarySearch(int arr[], unsigned left, unsigned right, int target)
{
    while (left <= right)
    {
        unsigned mid = (left + right + 1) / 2;
        if (arr[mid] == target)
        {
            return TRUE;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return FALSE;
}

unsigned FindSum2(int target, int input_array[], unsigned input_array_size)
{
    qsort(input_array, input_array_size, sizeof(int), Compare);

    for (unsigned i = 0; i < input_array_size; i++)
    {
        int complement = target - input_array[i];
        unsigned found = BinarySearch(input_array, i + 1, input_array_size - 1, complement);
        return found;
    }
}

unsigned FindSum3(int target, int input_array[], unsigned input_array_size)
{
    qsort(input_array, input_array_size, sizeof(int), Compare);

    unsigned left_index = 0;
    unsigned right_index = input_array_size - 1;
    while (left_index < right_index)
    {
        int tempsum = input_array[left_index] + input_array[right_index];
        if (tempsum == target)
        {
            return TRUE;
        }
        else if (tempsum > target)
        {
            right_index--;
        }
        else
        {
            left_index++;
        }
    }
    return FALSE;
}

int main(int argc, char **argv)
{
    int test_array1[] = {0, -1, 2, -3, 1};
    int target1 = -2;

    puts("brute force");

    unsigned sum_exists = FindSum(target1, test_array1, sizeof(test_array1) / sizeof(test_array1[0]));
    printf("test 1: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    int test_array2[] = {1, -2, 1, 0, 5};
    int target2 = 0;

    sum_exists = FindSum(target2, test_array2, sizeof(test_array2) / sizeof(test_array2[0]));
    printf("test 2: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    puts("sort first");

    sum_exists = FindSum2(target1, test_array1, sizeof(test_array1) / sizeof(test_array1[0]));
    printf("test 1: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    sum_exists = FindSum2(target2, test_array2, sizeof(test_array2) / sizeof(test_array2[0]));
    printf("test 2: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    puts("sort and two pointers");

    sum_exists = FindSum3(target1, test_array1, sizeof(test_array1) / sizeof(test_array1[0]));
    printf("test 1: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    sum_exists = FindSum3(target2, test_array2, sizeof(test_array2) / sizeof(test_array2[0]));
    printf("test 2: sum %s\n", sum_exists ? "exists" : "doesn't exist");

    return 0;
}