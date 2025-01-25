
#include <stdio.h>

#include "leet.h"

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

ll_node_t *find_intersection(ll_node_t *l1, ll_node_t *l2)
{
    if (NULL == l1 || NULL == l2)
    {
        return NULL;
    }
    if (detect_ll_cycle(l1) || detect_ll_cycle(l2))
    {
        puts("cycle detected");
        return NULL;
    }
    // determine the length of each list, say, N and M.
    // if they intersect, then the last node in each list
    // will be the same, which means the longer list will
    // have at least |N-M| nodes before the intersection
    // get to node N-M (first node is node 0) in the longer
    // list, compare it to node 0 in shorter list, then
    // compare N-M+1 to 1 and so on - O(N) (of the longer list)
    unsigned len1 = 1, len2 = 1;
    ll_node_t *t1 = l1, *t2 = l2;
    bool end1 = false, end2 = false;
    while (true)
    {
        t1 = t1->next;
        if (NULL == t1)
        {
            break;
        }
        else
        {
            len1++;
        }
    }
    while (true)
    {
        t2 = t2->next;
        if (NULL == t2)
        {
            break;
        }
        else
        {
            len2++;
        }
    }

    printf("len1 = %u, len2 = %u\n", len1, len2);

    unsigned delta;
    ll_node_t *shorter, *longer;

    if (len1 > len2)
    {
        longer = l1;
        shorter = l2;
        delta = len1 - len2;
    }
    else
    {
        longer = l2;
        shorter = l1;
        delta = len2 - len1;
    }
    while (longer->next)
    {
        if (delta != 0)
        {
            delta--;
            longer = longer->next;
        }
        else
        {
            if (longer == shorter)
            {
                return longer;
            }
            longer = longer->next;
            shorter = shorter->next;
        }
    }

    return NULL;

}

void main()
{

    ll_node_t *s_get_test_list(unsigned which_list);

    unsigned listid = 1;
    ll_node_t *mylist1 = s_get_test_list(listid);

    listid = 2;
    ll_node_t *mylist2 = s_get_test_list(listid);

    listid = 3;
    ll_node_t *mylist3 = s_get_test_list(listid);

    listid = 4;
    ll_node_t *mylist4 = s_get_test_list(listid);

    ll_node_t *intersect = find_intersection(mylist1, mylist1);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    
    intersect = find_intersection(mylist1, mylist2);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist1, mylist3);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist1, mylist4);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist2, mylist2);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist2, mylist3);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist2, mylist4);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist3, mylist3);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist3, mylist4);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
    intersect = find_intersection(mylist4, mylist4);
    if (intersect != NULL)
    {
        printf("intersect = %p, value = %d\n", intersect, intersect->val);
    }
    else
    {
        puts("intersect = NULL");
    }
    
}
