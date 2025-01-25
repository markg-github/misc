
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// input string needs 0 or more (s or )s removed to be balanced
// print this number and all the valid strings that can
// result when this number of (s or )s are removed
// example
// input: (a)())()
// output
// number: 1
// (a)()(), (a())()
void parens_test(const char *input)
{
    // outer loop to help determine "min remove count"?
    unsigned input_len = strlen(input);

    // go forward and remove surplus )s
    unsigned opens = 0, closes = 0, opens_removed = 0, closes_removed = 0;
    // unsigned index = 0;
    char helper[1000];
    // char index_array[1000];

    strcpy(helper, input);
    for (unsigned i = 0; i < input_len; i++) {
        if (helper[i] == '(') {
            opens++;
        }
        else if (helper[i] == ')') {
            closes++;
        }
        else {
            helper[i] = '_';
        }
        if (closes > opens) {
            helper[i] = 'c';
            closes--;
            closes_removed++;
        }
    }


    opens = closes = 0;
    // go backward and remove surplus (s
    for (unsigned i = 0; i < input_len; i++) {
        if (helper[input_len-1-i] == '(') {
            opens++;
        }
        else if (helper[input_len-1-i] == ')') {
            closes++;
        }
        if (opens > closes) {
            helper[input_len-1-i] = 'o';
            opens--;
            opens_removed++;
        }
    }


    puts("results");
    puts(input);
    puts(helper);
    printf("removed %d opening parens\n", opens_removed);
    printf("removed %d closing parens\n", closes_removed);
    return;





    // helper[0] = 0;
    // for (unsigned i = 0; i < input_len; i++) {
    //     if (input[i] == '(') {
    //         opens++;
    //     }
    //     else if (input[i] == ')') {
    //         closes++;
    //     }
    //     if (closes <= opens) {
    //         helper[index++] = input[i];
    //         helper[index] = 0;
    //     }
    //     else {
    //         closes--;
    //         index_array[removed++] = i;
    //     }
    // }

    
    // // go backward and remove surplus (s
    // // unsigned opens = 0, closes = 0, removed = 0, index = 0;
    // // const char *s = input;
    // // char helper[1000], index_array[1000];
    // // helper[0] = 0;
    // unsigned helper_len = strlen(helper);
    // opens = closes = index = 0;
    // char helper2[1000];
    // helper2[0] = 0;
    // for (unsigned i = 0; i < helper_len; i++) {
    //     if (helper[helper_len-1-i] == '(') {
    //         opens++;
    //     }
    //     else if (helper[helper_len-1-i] == ')') {
    //         closes++;
    //     }
    //     if (opens <= closes) {
    //         helper2[index++] = helper[helper_len-1-i];
    //         helper2[index] = 0;
    //     }
    //     else {
    //         opens--;
    //     }
    // }
    // // helper2 is reversed at this point
    // unsigned helper2_len = strlen(helper2);
    // unsigned half_helper2_len = helper2_len/2;
    // for (unsigned i = 0; i < half_helper2_len; i++) {
    //     char temp = helper2[i];
    //     helper2[i] = helper2[helper2_len-1-i];
    //     helper2[helper2_len-1-i] = temp;

    // }
    

    // puts("results");
    // puts(input);
    // puts(helper);
    // puts(helper2);
    // return;


}


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
    parens_test("(((()))");
    parens_test("(((((()))");
    parens_test("()))(((((");
    parens_test("()))((((()))))((((())");

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
