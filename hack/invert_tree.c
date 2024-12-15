#include <stdio.h>
#include <stdlib.h>

#include "leet.h"

// typedef struct TreeNode
// {
//     int val;
//     struct TreeNode *left;
//     struct TreeNode *right;
// } treenode_t;

treenode_t *InvertTree(treenode_t *root)
{

    unsigned special_case = 0;
    if (NULL == root)
    {
        // return root;
    }
    // else if (NULL == root->left && NULL == root->right)
    // {
    //     // return root;
    // }
    // else if (NULL == root->left)
    // {
    //     root->left = InvertTree(root->right);
    //     root->right = NULL;
    // }
    // else if (NULL == root->right)
    // {
    //     root->right = InvertTree(root->left);
    //     root->left = NULL;
    // }
    else
    {
        treenode_t *temp = InvertTree(root->left);
        root->left = InvertTree(root->right);
        root->right = temp;
    }
    return root;

    /*
    else
    {
        InvertTree(root->left);
        InvertTree(root->right);
        return;
    }
    if (() && (NULL == root->right))
        unsigned bottom = (NULL == root->left->left);
    bottom && = (NULL == root->left->right);
    bottom && = (NULL == root->right->left);
    bottom && = (NULL == root->right->right);
    treenode_t *temp;
    if (bottom)
    {
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    else
    {
        InvertTree(root->left);
        InvertTree(root->right);
    }
        */
}

int main(int argc, char **argv)
{
    treenode_t *t1 = BuildTree1();

    // order_t order = eInorder;
    // order_t order = ePreorder;
    order_t order = eInorder;

    // puts("tree 1");
    // puts("pre 1");
    // Traverse(t1, ePreorder);

    // puts("in 1");

    // Traverse(t1, eInorder);

    // puts("post 1");

    // Traverse(t1, ePostorder);

    puts("============================\n=======================");

    treenode_t* temp = t1;

    Traverse(temp, order);

    treenode_t *result = InvertTree(temp);

    puts("tree inverted - result");
    Traverse(result, order);
    puts("tree inverted");
    Traverse(temp, order);

    puts("============================\n=======================");

    treenode_t *t2 = BuildTree2();

    temp = t2;

    Traverse(temp, order);

    result = InvertTree(temp);

    puts("tree inverted - result");
    Traverse(result, order);
    puts("tree inverted");
    Traverse(temp, order);

    puts("============================\n=======================");

    treenode_t *t3 = BuildTree3();

    temp = t3;

    Traverse(temp, order);

    result = InvertTree(temp);

    puts("tree inverted - result");
    Traverse(result, order);
    puts("tree inverted");
    Traverse(temp, order);

    puts("============================\n=======================");

    treenode_t *t4 = BuildTree4();

    temp = t4;

    Traverse(temp, order);

    result = InvertTree(temp);

    puts("tree inverted - result");
    Traverse(result, order);
    puts("tree inverted");
    Traverse(temp, order);

    puts("============================\n=======================");

    treenode_t *t5 = BuildTree5();

    temp = t5;

    Traverse(temp, order);

    result = InvertTree(temp);

    puts("tree inverted - result");
    Traverse(result, order);
    puts("tree inverted");
    Traverse(temp, order);

}
