#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *right;
    struct TreeNode *left;

    /* data */
} TreeNode;

void RootFirst(TreeNode *p)
{
    if (p != NULL)
    {
        printf("%d", p->data);
        RootFirst(p->left);
        RootFirst(p->right);
    }
}

void RootMiddle(TreeNode *p)
{
    if (p != NULL)
    {
        RootMiddle(p->left);
        printf("%d", p->data);
        RootMiddle(p->right);
    }
}

void RootEnd(TreeNode *p)
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