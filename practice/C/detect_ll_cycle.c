
#include <stdio.h>

#include "leet.h"

typedef enum
{
    false = 0,
    true
} bool;

bool detect_ll_cycle(ll_node_t *head)
{
    if (NULL == head || NULL == head->next)
    {
        return false;
    }
    // two pointers traversing the list at different "speeds",
    // say one vs. two nodes at a time. if current (or next?)
    // nodes are ever equal, then cycle
    ll_node_t *pslow = head->next;
    ll_node_t *pfast = head->next->next;
    bool is_cycle = false;
    while (pslow != NULL && pfast != NULL)
    {
        if (pslow == pfast)
        {
            is_cycle = true;
            break;
        }
        pslow = pslow->next;
        pfast = pfast->next;
        if (NULL == pfast)
        {
            break;
        }
        pfast = pfast->next;
    }

    return is_cycle;
}

void main()
{

    ll_node_t *get_test_list(unsigned which_list);

    unsigned listid = 1;
    ll_node_t *mylist = get_test_list(listid);
    bool is_cycle = detect_ll_cycle(mylist);
    printf("cycle in list %u: %s\n", listid, is_cycle ? "true" : "false");

    listid = 2;
    mylist = get_test_list(listid);
    is_cycle = detect_ll_cycle(mylist);
    printf("cycle in list %u: %s\n", listid, is_cycle ? "true" : "false");

    listid = 3;
    mylist = get_test_list(listid);
    is_cycle = detect_ll_cycle(mylist);
    printf("cycle in list %u: %s\n", listid, is_cycle ? "true" : "false");

    listid = 4;
    mylist = get_test_list(listid);
    is_cycle = detect_ll_cycle(mylist);
    printf("cycle in list %u: %s\n", listid, is_cycle ? "true" : "false");
}
