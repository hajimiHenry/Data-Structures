#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode
{
    int data;
    struct Lnode *next;
} Lnode;

Lnode *MakeNode(int data);
void AddNode(Lnode *head, int data);
void DeleteNode(Lnode *head, int Del_data);

int main(void)
{
    Lnode *head = MakeNode(0);

    int num;
    do
    {
        scanf("%d", &num);
        if (num != 0)
        {
            AddNode(head, num);
        }

    } while (num != 0);

    int k;
    scanf("%d", &k);

    DeleteNode(head, k);

    Lnode *cur = head->next;

    while (cur != NULL)
    {
        printf("%d", cur->data);
        cur = cur->next;
    }

    return 0;
}

Lnode *MakeNode(int data)
{
    Lnode *p = malloc(sizeof(Lnode));
    p->data = data;
    p->next = NULL;

    return p;
}

void AddNode(Lnode *head, int data)
{
    // 走到最后面
    Lnode *cur = head;

    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    // 创建要加入的节点
    Lnode *p = MakeNode(data);
    cur->next = p;
}

void DeleteNode(Lnode *head, int Del_data)
{
    // 把头节点设为光标的第一个节点
    Lnode *cur = head->next;
    Lnode *front = head;
    while (cur != NULL)
    {
        if (cur->data != Del_data)
        {
            front = cur;
            cur = cur->next;
        }
        else
        {
            front->next = cur->next;
            Lnode *tmp = cur;
            cur = tmp->next;
            free(tmp);
        }
    }
}
