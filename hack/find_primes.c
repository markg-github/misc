

#include <stdio.h>
#include <stdlib.h>

void Test(unsigned n, unsigned d)
{
    if (1 == d)
    {
        printf("%d\n", n);
    }
    else if (n % d == 0)
    {
        return;
    }
    else
    {
        Test(n, d - 1);
    }
}

typedef struct
{
    // unsigned val;
    unsigned alive;
} sievesquare_t;


void SieveUpdate(sievesquare_t *board, unsigned boardsize, unsigned current_index)
{
    if (current_index == boardsize)
    {
        return;
    }
    if (board[current_index].alive)
    {
        unsigned square = current_index * current_index;
        unsigned limit = boardsize / current_index + 1;

        for (unsigned j = 2; j < limit; j++)
        {
            unsigned temp = current_index * j;
            if (temp < boardsize && temp >= square)
            {
                board[temp].alive = 0;
            }
        }
    }
    SieveUpdate(board, boardsize, current_index + 1);
}

int main(int argc, char **argv)
{
    unsigned thresh = 1050;

    puts("naive");
    for (unsigned i = 2; i <= thresh; i++)
    {
        // if (i <= 2)
        // {
        //     printf("%d\n", i);
        // }
        unsigned delta = i / 2;
        Test(i, i - delta);
    }

    puts("sieve");
    unsigned boardsize = thresh+1;
    sievesquare_t *sieveboard = (sievesquare_t *)malloc(boardsize * sizeof(sievesquare_t));

    for (unsigned i = 2; i < boardsize; i++)
    {
        // sieveboard[i].val = i;
        sieveboard[i].alive = 1;
    }
    SieveUpdate(sieveboard, boardsize, 2);
    for (unsigned i = 2; i < boardsize; i++)
    {
        if (sieveboard[i].alive)
        {
            printf("%d\n", i);
        }
    }
}