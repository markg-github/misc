

#include <assert.h>
#include <string.h>
// #include <sys/types.h>
// #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false = 0,
    true
} bool;

typedef struct _malloc_metadata
{
    unsigned size;
    bool isfree;
    struct _malloc_metadata *next;
} malloc_metadata_t;

unsigned char myheap[10000];

malloc_metadata_t *head = (malloc_metadata_t *)NULL;

void print_list(void);

#define QUEUE_SIZE 50
static char *string_queue[QUEUE_SIZE];
// equal means empty
unsigned qhead = 0, qtail = 0;

void read_from_queue(unsigned count)
{
    printf("read_from_queue: count=%u\n", count);
    for (unsigned i = 0; i < count; i++)
    {
        if (qhead == qtail)
        {
            puts("empty queue");
            return;
        }
        char *temp = string_queue[qhead];
        puts(temp);
        free(temp);
        qhead = (qhead + 1) % QUEUE_SIZE;
    }
}

void add_to_queue(const char *input_string, unsigned size)
{
    char *entry = (char *)malloc(size);
    strcpy(entry, input_string);
    if ((qtail + 1) % QUEUE_SIZE == qhead)
    {
        puts("full queue");
        // prefer to lose old entries than ignore new ones
        free(string_queue[head]);
        qhead = (qhead + 1) % QUEUE_SIZE;
    }
    string_queue[qtail] = entry;
    qtail = (qtail + 1) % QUEUE_SIZE;
}

void *mysbrk(unsigned increment)
{
    char s[100];
    sprintf(s, "mysbrk: increment=%u\n", increment);
    add_to_queue(s, 100);

    static unsigned char *top_of_heap = myheap;
    void *temp = top_of_heap;
    top_of_heap += increment; // check overflow
    print_list();
    if (top_of_heap >= myheap + sizeof(myheap))
    {
        return NULL;
    }
    return temp;
}

void *mymalloc(unsigned requested_size)
{
    char s[100];
    sprintf(s, "mymalloc: requested_size=%u\n", requested_size);
    add_to_queue(s, 100);

    print_list();
    if (requested_size <= 0)
    {
        return NULL;
    }
    // see if there are any free blocks big enough
    malloc_metadata_t *current = head;
    while (current != NULL)
    {
        if (current->isfree && current->size >= requested_size)
        {
            puts("mymalloc: using free block");
            current->isfree = false;
            return current + 1;
        }
        current = current->next;
    }
    if (head == NULL)
    {
        // first time
        head = (malloc_metadata_t *)mysbrk(requested_size + sizeof(malloc_metadata_t));
        if (NULL == head)
        {
            return NULL;
        }
        puts("mymalloc: adding first block");
        head->isfree = false;
        head->size = requested_size;
        head->next = NULL;
        return head + 1;
    }
    // no free blocks big enough and not first time
    // add new block to end of list
    malloc_metadata_t *block = NULL;
    current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    block = (malloc_metadata_t *)mysbrk(requested_size + sizeof(malloc_metadata_t));
    if (NULL == block)
    {
        return NULL;
    }
    puts("mymalloc: adding block");
    block->isfree = false;
    block->size = requested_size;
    block->next = NULL;
    current->next = block;
    return block + 1;
}

struct block_meta *myfind_free_block(struct block_meta **last, size_t size)
{
}

struct block_meta *myrequest_space(struct block_meta *last, size_t size)
{
}

void myfree(void *ptr)
{
    char s[100];
    sprintf(s, "myfree: ptr=%p\n", ptr);
    add_to_queue(s, 100);

    print_list();
    if (NULL == ptr)
    {
        return;
    }
    malloc_metadata_t *current = head;
    while (NULL != current)
    {
        if (ptr == current + 1)
        {
            puts("myfree: found block");
            assert(!current->isfree);
            current->isfree = true;
            return;
        }
        current = current->next;
    }
    assert(false);
}

void print_list()
{
    malloc_metadata_t *current = head;
    unsigned char blocknum = 0;
    while (NULL != current)
    {
        printf("%u: size=%u, %s\n", blocknum, current->size, current->isfree ? "is free" : "is not free");
        printf("%u: head=%p, current=%p\n", blocknum, head, current);
        current = current->next;
        blocknum++;
    }
}

void *myrealloc(void *ptr, size_t size)
{
}

void *mycalloc(size_t nelem, size_t elsize)
{
}

int main(int argc, char **argv)
{
    void *p1 = mymalloc(200);
    void *p2 = mymalloc(300);
    myfree(p2);

    void *p3 = mymalloc(400);
    void *p4 = mymalloc(250);
    myfree(p3);
    void *p5 = mymalloc(350);
    void *p6 = mymalloc(20);
    void *p7 = mymalloc(20);

    read_from_queue(5);
    read_from_queue(5);
    read_from_queue(5);
    read_from_queue(5);
    read_from_queue(5);
    read_from_queue(5);
}