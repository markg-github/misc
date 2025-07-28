
// Write a function to get the
// intersection point of two Linked Lists

#include <stdio.h>
#include <stdlib.h>

typedef struct _ll_node
{
    int val;
    struct _ll_node *next;
} ll_node_t;

// insertion sort
ll_node_t *sortedInsert(ll_node_t *curr, ll_node_t *sorted)
{
    // need to handle the case where curr needs to be at the beginning here 
    // so that we can look ahead below
    if (sorted == NULL || sorted->val >= curr->val)
    {
        printf("insert %d at beginning\n", curr->val);
        curr->next = sorted;
        sorted = curr;
    }
    else
    {
        ll_node_t *sorted_curr = sorted;

        // you need to look ahead here so you can change the pointer that
        // needs to point at curr
        while (sorted_curr->next != NULL && sorted_curr->next->val < curr->val)
        {
            sorted_curr = sorted_curr->next;
        }
        if (sorted_curr->next == NULL) {
            printf("insert %d at end\n", curr->val);
        }
        else {
            printf("insert %d in middle\n", curr->val);
        }
        // now we know we're at the end (sorted_curr->next == NULL) or
        // sorted_cur->val < curr->val and sorted_cur->next->val >= curr->val
        curr->next = sorted_curr->next;
        sorted_curr->next = curr;
    }
    return sorted;
}

ll_node_t* ll_sort(ll_node_t *root, unsigned order)
{

    ll_node_t *sorted = NULL;
    ll_node_t *curr = root;
    if (order)
    {
        while (curr != NULL)
        {
            ll_node_t *next = curr->next;
            sorted = sortedInsert(curr, sorted);
            curr = next;
        }
    }
    else
    {
    }
    return sorted;
}

int main(int argc, char **argv)
{
    ll_node_t *p1 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p2 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p3 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p4 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p5 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p6 = (ll_node_t *)malloc(sizeof(ll_node_t));

    p1->val = 123;
    p1->next = p2;

    p2->val = 119;
    p2->next = p3;

    p3->val = 96;
    p3->next = p4;

    p4->val = 90;
    p4->next = p5;

    p5->val = 10;
    p5->next = p6;

    p6->val = 7;
    p6->next = NULL;

    void print_list(ll_node_t*);

    print_list(p1);
    ll_node_t *sorted = ll_sort(p1, 1);
    print_list(sorted);

}

void print_list(ll_node_t *list)
{
    while (list != NULL) {
        printf("value = %d\n", list->val);
        list = list->next;
    }
}
