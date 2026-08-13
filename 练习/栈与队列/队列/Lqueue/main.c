#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
    /* data */
} LNode;

typedef struct LQueue
{
    LNode *rear;
    /* data */
} LQueue;

LNode *MakeNode(int data);
LNode *LqInit(void);
void Enqueue(LNode **head, LNode **rear, int data);
bool Dequeue(LNode **head, LNode **rear, int *takeout);

int main(void)
{
    LNode *head = LqInit();
    LQueue q;

    q.rear = head;

    Enqueue(&head, &q.rear, 1);
    Enqueue(&head, &q.rear, 2);
    Enqueue(&head, &q.rear, 3);

    int takeout;
    int takeout2;
    int takeout3;

    Dequeue(&head, &q.rear, &takeout);
    Dequeue(&head, &q.rear, &takeout2);
    Dequeue(&head, &q.rear, &takeout3);

    printf("%p\n", q.rear);

    printf("%d\n", takeout);
    printf("%d\n", takeout2);
    printf("%d\n", takeout3);

    Enqueue(&head, &q.rear, 4);
    Enqueue(&head, &q.rear, 5);
    Enqueue(&head, &q.rear, 6);

    Dequeue(&head, &q.rear, &takeout);
    Dequeue(&head, &q.rear, &takeout2);
    Dequeue(&head, &q.rear, &takeout3);

    printf("%d\n", takeout);
    printf("%d\n", takeout2);
    printf("%d\n", takeout3);

    return 0;
}
// 初始化队列，与创建头节点

LNode *MakeNode(int data)
{
    LNode *n = malloc(sizeof(LNode));

    n->data = data;
    n->next = NULL;

    return n;
}

LNode *LqInit(void)
{

    return MakeNode(0);
}

void Enqueue(LNode **head, LNode **rear, int data)
{
    LNode *n = MakeNode(data);

    (*rear)->next = n;
    *rear = n;
}

bool Dequeue(LNode **head, LNode **rear, int *takeout)
{
    // 判空
    if ((*head) == (*rear))
    {
        fprintf(stderr, "队列是空的，无法删除");
        return false;
        /* code */
    }
    *takeout = (*head)->next->data;
    LNode *to_be_freed = (*head)->next;
    if ((*rear) == to_be_freed)
    {
        (*rear) = *head;
        /* code */
    }
    (*head)->next = (*head)->next->next;

    free(to_be_freed);
    return true;
}
