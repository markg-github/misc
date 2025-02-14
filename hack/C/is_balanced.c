
#include <stdio.h>
#include <stdlib.h>

#include "leet.h"

// is input binary tree balanced?
// balanced doesn't mean the number of leaf nodes
// is a power of 2, it means that all leaf nodes
// are within one level of each other

/**
 * Definition for a binary tree node.
 * treenode_t {
 *     int val;
 *     treenode_t *left;
 *     treenode_t *right;
 * };
 */

int Height(treenode_t *root);
int Height2(treenode_t *root);

unsigned IsBalanced(treenode_t *root)
{
    // Height Function will return -1, when it’s an unbalanced tree...
    if (Height(root) == -1)
    {
        return 0;
    }
    return 1;
}

unsigned IsBalanced2(treenode_t *root)
{
    // this function is wrong since it only considers the
    // first two subtrees so if either of them is unbalanced,
    // but have the same height, this function will give a false
    // positive

    // If the tree is empty, we can say it’s balanced...
    if (root == NULL)
        return 1;

    int rh = Height2(root->right);
    int lh = Height2(root->left);

    printf("left height = %d\n", lh);
    printf("right height = %d\n", rh);

    int diff;
    if (rh > lh)
    {
        diff = rh - lh;
    }
    else
    {
        diff = lh - rh;
    }
    if (diff < 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int Height2(treenode_t *root)
{
    int rh = 0, lh = 0;
    if (NULL == root)
    {
        return 0;
    }
    lh = Height2(root->left);
    rh = Height2(root->right);
    return max(lh, rh) + 1;
}

// Create a function to return the “height” of a current subtree using recursion...
int Height(treenode_t *root)
{
    // Base case...
    if (root == NULL)
        return 0;
    // Height of left subtree...
    int leftHeight = Height(root->left);
    // Height of height subtree...
    int rightHight = Height(root->right);
    // In case of left subtree or right subtree unbalanced or their heights differ by more than ‘1’, return -1...
    if (leftHeight == -1 || rightHight == -1 || abs(leftHeight - rightHight) > 1)
        return -1;
    // Otherwise, return the height of this subtree as max(leftHeight, rightHight) + 1...
    return max(leftHeight, rightHight) + 1;
}

/*
treenode_t* BuildTree1()
{
    treenode_t *node15 = BuildTreeNode(15, NULL, NULL);
    treenode_t *node7 = BuildTreeNode(7, NULL, NULL);

    treenode_t *node20 = BuildTreeNode(20, node15, node7);

    treenode_t *node9 = BuildTreeNode(9, NULL, NULL);

    treenode_t* node3 = BuildTreeNode(3, node9, node20);

    return node3;


}

treenode_t* BuildTree2()
{
    treenode_t *nodeA = BuildTreeNode(4, NULL, NULL);
    treenode_t *nodeB = BuildTreeNode(4, NULL, NULL);

    treenode_t *nodeC = BuildTreeNode(3, nodeA, nodeB);

    treenode_t *nodeD = BuildTreeNode(3, NULL, NULL);

    treenode_t* nodeE = BuildTreeNode(2, nodeC, nodeD);
    treenode_t* nodeF = BuildTreeNode(2, NULL, NULL);
    treenode_t* nodeG = BuildTreeNode(1, nodeE, nodeF);

    return nodeG;


}
 */

int main(int argc, char **argv)
{
    treenode_t *t1 = BuildTree1();
    treenode_t *t2 = BuildTree2();
    treenode_t *t3 = BuildTree3();
    treenode_t *t4 = BuildTree4();
    treenode_t *t5 = BuildTree5();

    unsigned bal = IsBalanced2(t1);
    printf("tree 1 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced2(t2);
    printf("tree 2 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced2(t3);
    printf("tree 3 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced2(t4);
    printf("tree 4 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced2(t5);
    printf("tree 5 balanced? %s\n", bal ? "yes" : "no");

    puts("Check");

    bal = IsBalanced(t1);
    printf("tree 1 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced(t2);
    printf("tree 2 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced(t3);
    printf("tree 3 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced(t4);
    printf("tree 4 balanced? %s\n", bal ? "yes" : "no");

    bal = IsBalanced(t5);
    printf("tree 5 balanced? %s\n", bal ? "yes" : "no");
}
