
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <errno.h>


void sleep_ms(long milliseconds);
int random_int_in_range(int min, int max);

unsigned g_merge_calls;

void merge(int itemslr[], unsigned left, unsigned mid, unsigned right)
{
    printf("%s\n", __FUNCTION__);
    g_merge_calls++;

    // temp arrays so we can put merge back in (shared) input
    unsigned nl = mid-left+1;
    unsigned nr = right-mid;
    int *itemsl = (int *) malloc((nl) * sizeof(int));
    int *itemsr = (int *) malloc((nr) * sizeof(int));

    // fill temp arrays
    for (unsigned i = 0; i < nl; i++) {
        itemsl[i] = itemslr[left+i];
    }

    for (unsigned i = 0; i < nr; i++) {
        itemsr[i] = itemslr[i+mid+1];
    }

    // merge them
    unsigned li, ri, mi;
    li = ri = 0;
    // we're doing everything in-place as much as possible,
    // from left to right of the input, that is, start at left, not 0
    mi = left;
    while ((li < nl) && (ri < nr)) {
        if (itemsl[li] < itemsr[ri]) {
            itemslr[mi] = itemsl[li];
            li++;
        }
        else {
            itemslr[mi] = itemsr[ri];
            ri++;

        }
        mi++;

    }

    // remaining items
    while (li < nl) {
        itemslr[mi++] = itemsl[li++];
    }
    while (ri < nr) {
        itemslr[mi++] = itemsr[ri++];
    }
    
    free(itemsl);
    free(itemsr);
}

void merge_sort(int items[], unsigned left, unsigned right)
{
    // printf("%s\n", __FUNCTION__);
    // printf("left = %u, right = %u\n", left, right);
    // sleep_ms(100);

    if (left < right) {
        unsigned mid = (right+left)/2;
        // sort left half
        merge_sort(items, left, mid);
        // sort right half
        merge_sort(items, mid+1, right);
        // merge
        merge(items, left, mid, right);
    }
}

int main()
{
    int input1[] = {12, 11, 13, 5, 6, 7};
    void print_array(int x[], unsigned);

    unsigned n1 = sizeof(input1)/sizeof(input1[0]);
    print_array(input1, n1);
    g_merge_calls = 0;
    merge_sort(input1, 0, n1-1);
    print_array(input1, n1);
    printf("size = %u, merge calls = %u\n\n", n1, g_merge_calls);

    int lower_bound = -100, upper_bound = 100;
    unsigned input2_size = 8;
    int *input2 = (int*) malloc(input2_size * sizeof(int));

    for (unsigned i = 0; i < input2_size; i++) {
        input2[i] = random_int_in_range(lower_bound, upper_bound);
    }

    print_array(input2, input2_size);
    g_merge_calls = 0;
    merge_sort(input2, 0, input2_size-1);
    print_array(input2, input2_size);
    printf("size = %u, merge calls = %u\n\n", input2_size, g_merge_calls);

    free(input2);

    int clutter = 1;
    if (clutter) {
        int lower_bound = -100, upper_bound = 100;
        unsigned input3_size = 250;
        int *input3 = (int*) malloc(input3_size * sizeof(int));
    
        for (unsigned i = 0; i < input3_size; i++) {
            input3[i] = random_int_in_range(lower_bound, upper_bound);
        }
    
        print_array(input3, input3_size);
        g_merge_calls = 0;
        merge_sort(input3, 0, input3_size-1);
        print_array(input3, input3_size);
        printf("size = %u, merge calls = %u\n\n", input3_size, g_merge_calls);
    
        free(input3);
    
    
    }

    return 0;

}

void print_array(int array_[], unsigned len_)
{
    puts("array");
    for (unsigned i = 0; i < len_; i++) {
        printf("%d  ", array_[i]);
    }
    puts("");
}


void sleep_ms(long milliseconds) {
    struct timespec req;
    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000;

    // nanosleep might be interrupted by signals.  We handle that.
    while (nanosleep(&req, &req) == -1 && errno == EINTR); 
}


int random_int_in_range(int min, int max) {
    // 1. Seed the random number generator (only once per program)
    static int seeded = 0; // Ensure seeding happens only once
    if (!seeded) {
        srand(time(NULL)); // Use current time as seed
        seeded = 1;
    }

    // 2. Generate a random number within the desired range
    int range = max - min + 1; // Calculate the size of the range
    int random_number = rand() % range + min; // Generates number between min and max

    return random_number;
}


