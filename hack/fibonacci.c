
// this started out as 2048-bonacci game - see either HackerRank or CodedPad
// now, it's just fibonacci w/ some additional unused code

// create array of unsigneds where each element is part of the fibonacci sequence and
// max element is <= 2*16

// we know fib(n+2)/fib(n) > 2. this can tell us how big our array needs to be.
// if fib(n+1)/fib(n) = 2, then we'd need array with 16 elements
// in reality since fib(n+1)/fib(n) < 2 but fib(n+2)/fib(n) > 2, we can double this.
// quick test
// max < 8 --> 6
// 1,1,2,3,5,8
// max < 16 --> 8
// 1,1,2,3,5,8,13,21
// max < 32 --> 10

#include <stdio.h>
#include <string.h>

// const unsigned fib_num_count = 32;
#define FIB_NUM_COUNT 32
#define BOARD_SIZE 4

enum square_state
{
    INITIALIZED,
    FUSED
};
enum game_direction
{
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_ERROR
};
struct game_square
{
    unsigned value;
    enum square_state state;
};

unsigned fibonacci_array[FIB_NUM_COUNT]; // see above for sizing
struct game_square game_board[BOARD_SIZE][BOARD_SIZE];

/* enum square_state game_direction(char direction_string[])
{
    if (0 == strcmpi(direction_string, "left"))
    {
        return DIRECTION_LEFT;
    }
    else if (0 == strcmpi(direction_string, "right"))
    {
        return DIRECTION_RIGHT;
    }
    if (0 == strcmpi(direction_string, "up"))
    {
        return DIRECTION_UP;
    }
    if (0 == strcmpi(direction_string, "down"))
    {
        return DIRECTION_DOWN;
    }
    else return DIRECTION_ERROR;
}
 */

unsigned nthFibonacci_recur(unsigned n)
{
    if (n <= 1)
    {
        return 1;
    }
    return nthFibonacci_recur(n - 1) + nthFibonacci_recur(n - 2);
}

unsigned nthFibonacci_iter(unsigned n)
{
    if (n <= 1)
    {
        return 1;
    }
    unsigned fib1=1, fib2=1, result;
    for (unsigned i = 1; i < n; i++)
    {
        result = fib1 + fib2;
        fib2 = fib1;
        fib1 = result;
    }
    return result;
}

void initialize()
{
    for (unsigned i = 0; i < FIB_NUM_COUNT; i++)
    {
        fibonacci_array[i] = nthFibonacci_iter(i);
        // printf("Fibonacci number %u = %u\n", i, fib_array[i]);
    }
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
            game_board[i][j].value = 0;
            game_board[i][j].state = INITIALIZED;
        }
    }
    game_board[0][0].value = 2;
    game_board[3][0].value = 5;
    game_board[1][2].value = 13;
}

int main(int argc, char **argv)
{
    // initialize();

    /*     char input_s[100];
        while (1) {
            char* temp_ret = gets_s(input_s, sizeof(input_s));
            if (NULL != temp_ret)
            {
                switch(direction(input_s))
                {
                    case DIRECTION_LEFT:
                    break;
                    case DIRECTION_RIGHT:
                    break;
                    case DIRECTION_UP:
                    break;
                    case DIRECTION_DOWN:
                    break;
                }
            }
            else
            {
                return -1;
            }
        }
     */

    unsigned max = 19;

    for (unsigned i = 0; i < max; i++)
    {
        printf("Fibonacci number %u = %u\n", i, nthFibonacci_recur(i));
    }
}
