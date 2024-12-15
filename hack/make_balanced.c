
// Hello Aditi here
/*
Given a string s that contains parentheses and letters,
remove the minimum number of invalid parentheses to make the input string valid.

Return a list of unique strings that are valid with the minimum number of removals.
You may return the answer in any order.


Input: s = "()())()"
()())() >> ()()()
()())() >> (())()
Output: ["(())()","()()()"]

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]

Input: s = ")("
Output: [""]

*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

const unsigned debug = 4;

void debug_puts(const char *s)
{
    if (debug > 3)
    {
        puts(s);
    }
}

int _is_valid(char *s)
{
    unsigned opening = 0, closing = 0;
    while (*s)
    {
        if (*s == '(')
            opening++;
        else if (*s == ')')
            closing++;
        if (closing > opening)
            return 0;
        s++;
    }
    if (opening == closing && opening > 0)
        return 1;
    else
        return 0;
}

unsigned removed_all[MAX_LEN];
unsigned removed_any[MAX_LEN];

unsigned is_valid(const char *input_s)
{
    const char *p = input_s;
    unsigned valid = 0;
    static unsigned static_level = 0;

    // from here to the else is the code for removing one character
    // if removing one character is successful, then done, else recurse
    for (unsigned i = 0; i < strlen(input_s); i++)
    {
        // use strcpy just because I remember its prototype
        char s_before[MAX_LEN];
        char s_current[MAX_LEN];
        strcpy(s_before, input_s);
        // If we know the input isn't balanced, then the following is fine
        // even though it may remove/overwrite a character other than '('
        // or ')'. This is true since we can only CORRECT the input by
        // removing '(' or ')', that is, if we remove something else the
        // input will still be unbalanced.
        //
        // If the input may already be balanced, then we need to make sure
        // we're only removing '(' or ')', by conditioning.
        // s_before[i] = 0;
        if ('(' == s_before[i] || ')' == s_before[i])
        {
            s_before[i] = 0;
        }
        else
        {
            continue;
        }
        strcpy(s_current, s_before);
        strcpy(s_current + i, input_s + i + 1);
        debug_puts(s_current);
        if (_is_valid(s_current))
        {
            // if (debug > 3) printf("%d position removed, valid result: %s\n", static_level + i, s_current);
            if (debug > 3)
                printf("%d position removed, valid result: %s\n", i, s_current);
            // removed_any[static_level+i] = 1;
            valid = 1;
        }
    }
    if (valid)
    {
        return 1;
    }
    else
    {
        unsigned level = static_level++;

        for (unsigned i = 0; i < strlen(input_s); i++)
        {
            char s_before[MAX_LEN];
            char s_current[MAX_LEN];
            strcpy(s_before, input_s);
            // s_before[i] = 0;
            if ('(' == s_before[i] || ')' == s_before[i])
            {
                s_before[i] = 0;
            }
            else
            {
                continue;
            }

            strcpy(s_current, s_before);
            strcpy(s_current + i, input_s + i + 1);
            // printf("%d position removed, invalid result: %s\n", i+level, s_current);
            debug_puts("recurse");
            printf("s_current: %s\n", s_current);
            if (is_valid(s_current))
            {
                // if (debug > 3) printf("%d position removed (%s)\n", i + level, s_current);
                if (debug > 3)
                    printf("%d position removed\n", i);
                if (debug > 3)
                    printf("%s\n", s_current);
                // removed_all[level+i] = 1;

                break;
            }
        }
    }
    return 0;
}

void results(const char *input_s_)
{
    char input_s[100];
    strcpy(input_s, input_s_);

    printf("%s results\n", input_s);
    for (unsigned i = 0; i < strlen(input_s); i++)
    {
        input_s[i] = removed_all[i] ? 'x' : input_s[i];
    }
    for (unsigned i = 0; i < strlen(input_s); i++)
    {
        char temp_s[100];
        strcpy(temp_s, input_s);
        temp_s[i] = removed_any[i] ? '.' : temp_s[i];
        if (removed_any[i])
        {
            puts(temp_s);
        }
    }
    puts("");
}

void reset()
{
    for (unsigned i = 0; i < MAX_LEN; i++)
    {
        removed_all[i] = removed_any[i] = 0;
    }
}

void try_something_new(const char *input_s);

void parens_test(const char *input_s)
{
    printf("parens_test: %s\n", input_s);
    // is_valid(input_s);
    // results(input_s);
    // reset();
    try_something_new(input_s);
}

// To execute C++, please define "int main()"
int main()
{

    // char* input_s = "()())()";

    parens_test("()())()");
    parens_test("(a)())()");
    parens_test("(");
    parens_test(")");
    parens_test("))))()())()");
    parens_test("))))()())())))");
    parens_test("))))()())())((()))))");
    parens_test("(())))");
    parens_test("()))))");
    parens_test("()))");

    /*     puts("test");
        is_valid(input_s);
        results(input_s);
        reset();

        puts("test");
        input_s = ("(a)())()");
        is_valid(input_s);
        results(input_s);
        reset();

        puts("test");
        is_valid("(");
            results(input_s);
        reset();

        puts("test");
        is_valid(")");
        results(input_s);
        reset();

        puts("test");
        is_valid("))))()())()");
        results(input_s);
        reset();
     */
    return 0;
}

unsigned char remove_flags[100];

void try_something_new(const char *input_s)
{
    char temp_s[MAX_LEN];
    char result_s[MAX_LEN];
    unsigned temp_index = 0;
    unsigned opening = 0, closing = 0;

    // strcpy(temp_s, input_s);
    for (unsigned i = 0; i < strlen(input_s); i++)
    {
        switch (input_s[i])
        {
        case '(':
            opening++;
            break;
        case ')':
            if (closing == opening)
            {
                remove_flags[i] = 1;
                continue;
            }
            else
            {
                closing++;
            }

            break;
        }
        temp_s[temp_index++] = input_s[i];
    }
    temp_s[temp_index] = 0;
    puts(temp_s);
    // need to count the 1s in remove array
    temp_index = 0;
    for (int i = strlen(temp_s) - 1; i >= 0; i--)
    {
        switch (temp_s[i])
        {
        case '(':
            if (opening-- > closing)
            {
                continue;
            }
            break;
        }
        result_s[temp_index++] = temp_s[i];
    }
    result_s[temp_index] = 0;
    puts(result_s);
    // reverse string
    unsigned temp_len = strlen(result_s);
    for (unsigned i = 0; i < temp_len/2; i++)
    {
        char temp_c = result_s[i];
        result_s[i] = result_s[temp_len-i-1];
        result_s[temp_len-i-1] = temp_c;
    }
    puts(result_s);
}
