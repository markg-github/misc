// How many 0's will you write when writing all numbers from 1 to 1000?

#include <stdio.h>
#include <string.h>

unsigned CountZeros(unsigned N)
{
    unsigned zero_count = 0; 
    for (unsigned i = 1; i <= N; i++)
    {
        char num_string[100];
        snprintf(num_string, sizeof(num_string), "%u", i);
        puts(num_string);
        char *temp_num_string = num_string;
        while (1)
        {
            puts(temp_num_string);
            temp_num_string = strchr(temp_num_string, '0');
            if (NULL == temp_num_string)
            {
                break;
            }
            else
            {
                zero_count++;
                temp_num_string++;
                printf("count = %u\n", zero_count);
            }
        }
    }
    return zero_count;
}

int main(int argc, char** argv)
{
    unsigned zero_count = CountZeros(1000);
    printf("%u zeros\n", zero_count);
}