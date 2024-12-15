#include <stdio.h>
#include <stdlib.h>

#include "leet.h"

void Traverse(treenode_t *root, order_t order)
{
    if (NULL == root)
    {
        return;
    }
    switch (order)
    {
    case eInorder:
        Traverse(root->left, order);
        printf("%d\n", root->val);
        Traverse(root->right, order);
        break;
    case ePreorder:
        printf("%d\n", root->val);
        Traverse(root->left, order);
        Traverse(root->right, order);
        break;
    case ePostorder:
        Traverse(root->left, order);
        Traverse(root->right, order);
        printf("%d\n", root->val);
        break;
    }
}

// treenode_t *BuildTreeNode(int val_, treenode_t *left_, treenode_t *right_);
// treenode_t *BuildTree1(void);
// treenode_t *BuildTree2(void);
// treenode_t *BuildTree3(void);
// treenode_t *BuildTree4(void);
// treenode_t *BuildTree5(void);

/*
int tree_traversal_main(int argc, char **argv)
{

    // order_t order = eInorder;
    // order_t order = ePreorder;
    order_t order = ePostorder;

    // puts("tree 3");
    // treenode_t *t3 = BuildTree3();
    // Traverse(t3, order);

    // puts("tree 1");
    // treenode_t *t1 = BuildTree1();
    // Traverse(t1, order);

    // puts("tree 2");
    // treenode_t *t2 = BuildTree2();
    // Traverse(t2, order);

    // puts("tree 4");
    // treenode_t *t4 = BuildTree4();
    // Traverse(t4, order);

    puts("tree 5");
    treenode_t *t5 = BuildTree5();
    Traverse(t5, order);
}


*/

treenode_t *BuildTreeNode(int val_, treenode_t *left_, treenode_t *right_)
{
    treenode_t *node = (treenode_t *)malloc(sizeof(treenode_t));
    node->val = val_;
    node->left = left_;
    node->right = right_;

    return node;
}
treenode_t *BuildTree1()
{
    treenode_t *node15 = BuildTreeNode(15, NULL, NULL);
    treenode_t *node7 = BuildTreeNode(7, NULL, NULL);

    treenode_t *node20 = BuildTreeNode(20, node15, node7);

    treenode_t *node9 = BuildTreeNode(9, NULL, NULL);

    treenode_t *node3 = BuildTreeNode(3, node9, node20);

    puts("tree 1 built");
    puts("3\n9 20\nnull null 15 7");

    return node3;
}

treenode_t *BuildTree2()
{
    treenode_t *nodeA = BuildTreeNode(4, NULL, NULL);
    treenode_t *nodeB = BuildTreeNode(4, NULL, NULL);

    treenode_t *nodeC = BuildTreeNode(3, nodeA, nodeB);

    treenode_t *nodeD = BuildTreeNode(3, NULL, NULL);

    treenode_t *nodeE = BuildTreeNode(2, nodeC, nodeD);
    treenode_t *nodeF = BuildTreeNode(2, NULL, NULL);
    treenode_t *nodeG = BuildTreeNode(1, nodeE, nodeF);

    puts("tree 2 built");
    puts("1\n2 2\n3 3 null null\n4 4 null null");

    return nodeG;
}

treenode_t *BuildTree3()
{
    treenode_t *node1 = BuildTreeNode(1, NULL, NULL);
    treenode_t *node3 = BuildTreeNode(3, NULL, NULL);

    treenode_t *node6 = BuildTreeNode(6, NULL, NULL);

    treenode_t *node9 = BuildTreeNode(9, NULL, NULL);

    treenode_t *node2 = BuildTreeNode(2, node1, node3);
    treenode_t *node7 = BuildTreeNode(7, node6, node9);
    treenode_t *node4 = BuildTreeNode(4, node2, node7);

    puts("tree 3 built");
    puts("4\n2 7\n1 3 6 9");

    return node4;
}

treenode_t *BuildTree4()
{
    treenode_t *node3 = BuildTreeNode(3, NULL, NULL);
    treenode_t *node2 = BuildTreeNode(2, node3, NULL);

    treenode_t *node1 = BuildTreeNode(1, NULL, node2);

    puts("tree 4 built");
    puts("1\nnull 2\n3 null");

    return node1;
}

treenode_t *BuildTree5()
{
    treenode_t *node9 = BuildTreeNode(9, NULL, NULL);
    treenode_t *node7 = BuildTreeNode(7, NULL, NULL);

    treenode_t *node6 = BuildTreeNode(6, NULL, NULL);

    treenode_t *node8 = BuildTreeNode(8, node9, NULL);
    treenode_t *node5 = BuildTreeNode(5, node6, node7);

    treenode_t *node4 = BuildTreeNode(4, NULL, NULL);

    treenode_t *node3 = BuildTreeNode(3, NULL, node8);
    treenode_t *node2 = BuildTreeNode(2, node4, node5);

    treenode_t *node1 = BuildTreeNode(1, node2, node3);

    puts("tree 5 built");
    puts("1\n2 3\n4 5 null 8\nnull null 6 7 9 null");

    return node1;
}


