
// Write a function to get the
// intersection point of two Linked Lists

#include <stdio.h>
#include <stdlib.h>

struct ll_node
{
    int value;
    struct ll_node *next;
};

struct ll_node *FindIntersection(struct ll_node *list1, struct ll_node *list2)
{
    struct ll_node *p1 = list1, *p2;
    while (NULL != p1)
    {
        p2 = list2;
        while (NULL != p2)
        {
            if (p1 == p2)
            {
                return p1;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return NULL;
}

struct ll_node *FindIntersection2(struct ll_node *list1, struct ll_node *list2)
{
    struct ll_node *p1 = list1, *p2;
    unsigned count1 = 0, count2 = 0;

    while (NULL != p1)
    {
        p1 = p1->next;
        count1++;
    }

    p2 = list2;
    while (NULL != p2)
    {
        p2 = p2->next;
        count2++;
    }

    unsigned diff;
    if (count1 >= count2)
    {
        diff = count1 - count2;
        p1 = list1;
        for (unsigned i = 0; i < diff; i++)
        {
            p1 = p1->next;
        }
        p2 = list2;
    }
    else
    {
        diff = count2 - count1;
        p2 = list2;
        for (unsigned i = 0; i < diff; i++)
        {
            p2 = p2->next;
        }
        p1 = list1;
    }
    while (NULL != p1)
    {
        if (p1 == p2)
        {
            return p1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return NULL;
}

struct ll_node *FindIntersection3(struct ll_node *list1, struct ll_node *list2)
{
    if (NULL == list1 || NULL == list2)
    {
        return NULL;

    }

    struct ll_node *p1 = list1, *p2 = list2;
    while (1)
    {
        if (p1 == p2)
        {
            return p1;
        }
        p1 = p1->next;
        if (NULL == p1)
        {
            p1 = list2;
        }
        p2 = p2->next;
        if (NULL == p2)
        {
            p2 = list1;
        }
    }
}

struct ll_node* sortedInsert(struct ll_node* curr, struct ll_node* sorted)
{
    if (sorted==NULL || sorted->val >= curr->val)
    {
        curr->next = sorted;
        sorted=curr;
    }
    else
    {
        struct ll_node* curr2 = sorted;
        while (curr2->next != NULL && curr2->next->val < curr->val)
        {
            curr2 = curr2->next;
        }
        curr->next=curr2->next;
        curr2->next = curr;
    }
    return sorted;
}

void ll_sort(struct ll_node* root, unsigned order)
{

    struct ll_node* sorted = NULL;
    struct ll_node* curr = root;
    if (order)
    {
    while (curr != NULL)
    {
        struct ll_node* next=curr->next;
        sorted=sortedInsert(curr, sorted);
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
    struct ll_node *p3 = (struct ll_node *)malloc(sizeof(struct ll_node));
    struct ll_node *p6 = (struct ll_node *)malloc(sizeof(struct ll_node));
    struct ll_node *p9 = (struct ll_node *)malloc(sizeof(struct ll_node));
    struct ll_node *p10 = (struct ll_node *)malloc(sizeof(struct ll_node));
    struct ll_node *p15 = (struct ll_node *)malloc(sizeof(struct ll_node));
    struct ll_node *p30 = (struct ll_node *)malloc(sizeof(struct ll_node));

    p3->value = 3;
    p3->next = p6;

    p6->value = 6;
    p6->next = p9;

    p9->value = 9;
    p9->next = p15;

    p10->value = 10;
    p10->next = p15;

    p15->value = 15;
    p15->next = p30;

    p30->value = 30;
    p30->next = NULL;

    // struct ll_node *list1=p10, *list2=p6;
    struct ll_node *list1=NULL, *list2=NULL;

    struct ll_node *intersection;

    intersection = FindIntersection(list1, list2);
    if (NULL != intersection) printf("value at intersection = %d\n", intersection->value);

    intersection = FindIntersection2(list1, list2);
    if (NULL != intersection) printf("value at intersection = %d\n", intersection->value);

    intersection = FindIntersection3(list1, list2);
    if (NULL != intersection) printf("value at intersection = %d\n", intersection->value);
}
