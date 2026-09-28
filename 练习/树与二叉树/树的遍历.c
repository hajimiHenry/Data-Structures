#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//==========================================这个是二叉树的知识==========================
typedef struct TreeNode
{
    int data;
    struct TreeNode *right;
    struct TreeNode *left;

    /* data */
} TreeNode;

void PreOrder(TreeNode *p)
{
    if (p != NULL)
    {
        printf("%d", p->data);
        RootFirst(p->left);
        RootFirst(p->right);
    }
}

void InOrder(TreeNode *p)
{
    if (p != NULL)
    {
        RootMiddle(p->left);
        printf("%d", p->data);
        RootMiddle(p->right);
    }
}

void PostOrder(TreeNode *p)
{
    if (p != NULL)
    {
        RootEnd(p->left);
        RootEnd(p->right);
        printf("%d", p->data);
    }
}

//=============================================层序遍历========================================
// 准备工作,先把层序遍历会用到的队列制作好
// 虽然说是使用队列来存储一个数,但是这个链队列的节点存储的不是int 而是这个我要存储的树节点的地址,
// 这也是为什么王道教材里面一直让我elemtype

typedef struct LNode
{
    TreeNode *ptr;
    struct LNode *next;
    /* data */
} LNode;

typedef struct LQueue
{
    LNode *rear;
    /* data */
} LQueue;

LNode *MakeNode(TreeNode *p)
{
    LNode *n = malloc(sizeof(LNode));

    n->ptr = p;
    n->next = NULL;

    return n;
}
LNode *LqInit(void)
{
    return MakeNode(NULL);
}

void Enqueue(LNode **head, LNode **rear, TreeNode *p)
{
    LNode *n = MakeNode(p);

    (*rear)->next = n;
    *rear = n;
}

// 一个不够好的设计,这里写死了这个数据是打印,但其实也有别的用处
// bool Dequeue(LNode **head, LNode **rear)
// {
//     // 判空
//     if ((*head) == (*rear))
//     {
//         fprintf(stderr, "队列是空的，无法删除");
//         return false;
//         /* code */
//     }

//     printf("%d", (*head)->next->ptr->data); // 上一次错在没有写next

//     LNode *to_be_freed = (*head)->next;
//     if ((*rear) == to_be_freed)
//     {
//         (*rear) = *head;
//         /* code */
//     }
//     (*head)->next = (*head)->next->next;

//     free(to_be_freed);
//     return true;
// }

// 对于出队更好的设计
// 出队时应该直接把数据交给调用者,调用者自己决定怎么做
TreeNode *Dequeue(LNode **head, LNode **rear)
{
    // 判空
    if ((*head) == (*rear))
    {
        fprintf(stderr, "队列是空的，无法删除");
        return NULL;
        /* code */
    }

    TreeNode *result = (*head)->next->ptr;

    LNode *to_be_freed = (*head)->next;
    if ((*rear) == to_be_freed)
    {
        (*rear) = *head;
        /* code */
    }
    (*head)->next = (*head)->next->next;

    free(to_be_freed);
    return result;
}

bool isEmpty(LNode *head, LNode *rear)
{
    if ((head) == (rear))
    {
        return true;
        /* code */
    }
    else
        return false;
}

void LevelOrder(TreeNode *root)
{
    LNode *head = LqInit();
    LNode *rear = head;

    Enqueue(&head, &rear, root); // q.rear 没有写& 类型不匹配

    while (!isEmpty(head, rear))
    {
        TreeNode *cur = Dequeue(&head, &rear);
        printf("%d ", cur->data);

        if (cur->left != NULL)
            Enqueue(&head, &rear, cur->left);
        if (cur->right != NULL)
            Enqueue(&head, &rear, cur->right);

        /* code */
    }
}

int main(void)
{
    return 0;
}

// 线索二叉树的遍历
//
typedef struct ThreadNode
{
    int data;
    struct ThreadNode *right;
    struct ThreadNode *left;
    int ltag, rtag; // 用来记录
    /* data */
} ThreadNode;

ThreadNode *pre = NULL;

void Visit(ThreadNode *p)
{
    if (p->left == NULL)
    {
        p->left = pre;
        p->ltag = 1;
    }
    if (pre != NULL && pre->right == NULL)
    {
        pre->right = p;
        pre->rtag = 1;
    }
    pre = p;
}

void InThread(ThreadNode *p)
{
    if (p == NULL)
        return;
    InThread(p->left);
    Visit(p);
    InThread(p->right);
}

// =========================树本身的遍历===================================

// 这是核心逻辑
bool ThereIsNextTree(TreeNode *node)
{
}

void TreePreOrder(TreeNode *root)
{
    if (root != NULL)
    {
        Visit(root);
        while (ThereIsNextTree(root))
        {
            TreePreOrder(NextTree);
        }
    }
}

void TreePostOrder(TreeNode *root)
{
    if (root != NULL)
    {
        while (ThereIsNextTree(root))
        {
            TreePostOrder(NextTree);
        }
        Visit(root);
    }
}

// 但是实操上往往把树变成孩子兄弟二叉树,然后对着二叉树进行操作
// 但是如果在前面进行了转换,变成了孩子兄弟二叉树
// 那么直接变成遍历二叉树

typedef struct CSNode
{
    int data;
    struct CSNode *FirstChild;
    struct CSNode *NextSibling;
} CSNode;

void PreOrder(CSNode *p)
{
    if (p != NULL)
    {
        printf("%d", p->data);
        PreOrder(p->FirstChild);
        PreOrder(p->NextSibling);
    }
}

// 树的后序遍历的坑
// 在把树转化成孩子兄弟二叉树之后,利用它对树本身进行后序遍历,实际上应该是对于这个二叉树进行中序遍历

void MidOrder(CSNode *p)
{
    if (p != NULL)
    {
        MidOrder(p->FirstChild);
        printf("%d", p->data);
        MidOrder(p->NextSibling);
    }
}

// 层序遍历,同样依赖孩子兄弟法
// 原理是一样,但是形式上有所改变,为了把一层的内容按照相同的逻辑收进来,这里需要在这个孩子兄弟树当中,找到实质上同层的元素,也就是右边的兄弟
void LevelOrder(CSNode *root)
{
    LNode *head = LqInit();
    LNode *rear = head;

    Enqueue(&head, &rear, root);

    while (!isEmpty(head, rear))
    {
        CSNode *cur = Dequeue(&head, &rear);
        printf("%d ", cur->data);

        // 在孩子兄弟二叉树当中往右走,实质上等于对于这个进行同层对遍历
        CSNode *child = cur->FirstChild;
        while (child != NULL)
        {
            Enqueue(&head, &rear, child);
            child = child->NextSibling;
        }
    }
}
