#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *right;
    struct TreeNode *left;

    /* data */
} TreeNode;

int main(void)
{
}

TreeNode *create_node(int val)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// 输入序列比如 "124##5##3##"
// '#' 表示这里是 NULL
TreeNode *build_tree(void)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
        return NULL;
    TreeNode *node = create_node(ch - '0');
    node->left = build_tree();  // 递归建左子树
    node->right = build_tree(); // 递归建右子树
    return node;
}
