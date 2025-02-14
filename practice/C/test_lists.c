// #include <stddef.h>

#include <stdlib.h>

#include "leet.h"

ll_node_t *get_test_list(unsigned which_list)
{
    ll_node_t *head = NULL;
    ll_node_t *p1 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p2 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p3 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p4 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p5 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p6 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p7 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p8 = (ll_node_t *)malloc(sizeof(ll_node_t));

    p1->val = 1;
    p2->val = 2;
    p3->val = 3;
    p4->val = 4;
    p5->val = 5;
    p6->val = 6;
    p7->val = 7;
    p8->val = 8;

    switch (which_list)
    {
    case 1:
        head = p1;
        p1->next = p2;
        p2->next = p3;
        p3->next = p4;
        break;
    case 2:
        head = p1;
        p1->next = p2;
        p2->next = p3;
        p3->next = p2;
        break;
    case 3:
        head = p1;
        p1->next = p2;
        p2->next = p3;
        p3->next = p4;
        p4->next = p5;
        p5->next = p6;
        p6->next = p7;
        break;
    case 4:
        head = p1;
        p1->next = p2;
        p2->next = p3;
        p3->next = p4;
        p4->next = p5;
        p5->next = p6;
        p6->next = p7;
        p7->next = p8;
        p8->next = p7;
        break;
    }

    return head;
}

ll_node_t *s_get_test_list(unsigned which_list)
{
    ll_node_t *head = NULL;
    ll_node_t *p1 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p2 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p3 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p4 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p5 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p6 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p7 = (ll_node_t *)malloc(sizeof(ll_node_t));
    ll_node_t *p8 = (ll_node_t *)malloc(sizeof(ll_node_t));

    static ll_node_t n1 = {1, NULL};
    static ll_node_t n2 = {2, NULL};
    static ll_node_t n3 = {3, NULL};
    static ll_node_t n4 = {4, NULL};
    static ll_node_t n5 = {5, NULL};
    static ll_node_t n6 = {6, NULL};
    static ll_node_t n7 = {7, NULL};
    static ll_node_t n8 = {8, NULL};

    static ll_node_t n9 = {9, NULL};
    static ll_node_t n10 = {10, NULL};
    static ll_node_t n11 = {11, NULL};
    static ll_node_t n12 = {12, NULL};
    static ll_node_t n13 = {13, NULL};
    static ll_node_t n14 = {14, NULL};
    static ll_node_t n15 = {15, NULL};
    static ll_node_t n16 = {16, NULL};

    // n1.val = 1;
    // n2.val = 2;
    // n3.val = 3;
    // n4.val = 4;
    // n5.val = 5;
    // n6.val = 6;
    // n7.val = 7;
    // n8.val = 8;

    // n9.val = 9;
    // n10.val = 10;
    // n11.val = 11;
    // n12.val = 12;
    // n13.val = 13;
    // n14.val = 14;
    // n15.val = 15;
    // n16.val = 16;

    // n1.next = NULL;
    // n2.next = NULL;
    // n3.next = NULL;
    // n4.next = NULL;
    // n5.next = NULL;
    // n6.next = NULL;
    // n7.next = NULL;
    // n8.next = NULL;

    // n9.next = NULL;
    // n10.next = NULL;
    // n11.next = NULL;
    // n12.next = NULL;
    // n13.next = NULL;
    // n14.next = NULL;
    // n15.next = NULL;
    // n16.next = NULL;

    switch (which_list)
    {
    case 1:
        head = &n13;
        n13.next = &n14;
        n14.next = &n15;
        n15.next = &n16;
        break;
    case 2:
        head = &n9;
        n9.next = &n10;
        n10.next = &n11;
        n11.next = &n12;
        break;
    case 3:
        head = &n5;
        n5.next = &n6;
        n6.next = &n7;
        n7.next = &n8;
        n8.next = &n9;
        break;
    case 4:
        head = &n1;
        n1.next = &n2;
        n2.next = &n3;
        n3.next = &n7;
        break;
    }

    return head;
}

/*

    # struct ll_node *p3 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p6 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p9 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p10 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p15 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p30 = (struct ll_node *)malloc(sizeof(struct ll_node));

    # p3->value = 3;
    # p3->next = p6;

    # p6->value = 6;
    # p6->next = p9;

    # p9->value = 9;
    # p9->next = p15;

    # p10->value = 10;
    # p10->next = p15;

    # p15->value = 15;
    # p15->next = p30;

    # p30->value = 30;
    # p30->next = NULL;



    # // Create two linked lists
    # // 1st list: 10 -> 15 -> 30
    # // 2nd list: 3 -> 6 -> 9 -> 15 -> 30
    # // 15 is the intersection point

    # // creation of first list
    #   Node *head1 = new Node(10);
    # head1->next = new Node(15);
    # head1->next->next = new Node(30);

    # // creation of second list
    #   Node *head2 = new Node(3);
    #   head2->next = new Node(6);
    # head2->next->next = new Node(9);
    # head2->next->next->next = head1->next;


    # struct ll_node *p3 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p6 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p9 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p10 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p15 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p30 = (struct ll_node *)malloc(sizeof(struct ll_node));

    # p3->value = 3;
    # p3->next = p6;

    # p6->value = 6;
    # p6->next = p9;

    # p9->value = 9;
    # p9->next = p15;

    # p10->value = 10;
    # p10->next = p15;

    # p15->value = 15;
    # p15->next = p30;

    # p30->value = 30;
    # p30->next = NULL;

 */