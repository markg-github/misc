
#if !defined(LEET_H)

#define LEET_H

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} treenode_t;

typedef enum
{
    eInorder,
    ePreorder,
    ePostorder
} order_t;

void Traverse(treenode_t *root, order_t order);

treenode_t *BuildTreeNode(int val_, treenode_t *left_, treenode_t *right_);

treenode_t *BuildTree1(void);
treenode_t *BuildTree2(void);
treenode_t *BuildTree3(void);
treenode_t *BuildTree4(void);
treenode_t *BuildTree5(void);

#endif

