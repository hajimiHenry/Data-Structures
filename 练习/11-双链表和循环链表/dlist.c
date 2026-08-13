#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
// 创建头结点
DNode *dlist_init(void)
{
    DNode *head = (DNode *)malloc(sizeof(DNode));
    if (head == NULL)
    {
        fprintf(stderr, "双链表头结点创建失败");
        exit(1);
        /* code */
    }
    head->prev = head;
    head->next = head;
    head->data = 0;

    return head;
}

// 创建节点,返回的是这个节点的地址
DNode *make_node(int data)
{
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (n == NULL)
    {
        fprintf(stderr, "双链表头结点创建失败");
        exit(1);
        /* code */
    }
    n->prev = NULL;
    n->next = NULL;
    n->data = data;

    return n;
}

// 在结点 p 后插
void insert_after(DNode *p, int data)
{
    DNode *x = make_node(data);
    x->next = p->next;
    p->next->prev = x;
    p->next = x;
    x->prev = p;
}
// 往前面移动一格，变成从p前面的那个节点进行前插
void insert_before(DNode *p, int data)
{
    insert_after(p->prev, data);
}

void push_front(DNode *head, int data)
{
    insert_after(head, data);
}

void push_back(DNode *head, int data)
{
    insert_before(head, data);
}
void remove_node(DNode *p, DNode *head)
{
    if (p == head)
    {
        printf("不允许移除头节点的");
        return;
        /* code */
    }
    else
    { // 中间（移除的）节点，前节点 指向后节点
      // p的前节点 p->prev 后节点p->next. 前节点的next 指向后节点
      // ，后节点的prev指向前节点
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }
}

void print_list(DNode *head)
{
    if (head == NULL)
    {
        fprintf(stderr,"此时head是null\n");
        return;
        /* code */
    }

    DNode *p = head->next;
    while (p != head)
    {
        printf("%d\n", p->data);
        p = p->next;
        /* code */
    }
    printf("====================================\n");
}

void print_reverse(DNode *head)
{
    DNode *p = head->prev;
    while (p != head)
    {
        printf("%d\n", p->data);
        p = p->prev;
        /* code */
    }
}

int length(DNode *head)
{
    DNode *p = head->prev;
    int count = 0;
    while (p != head)
    {
        count++;
        p = p->prev;
        /* code */
    }

    return count;
}

void dlist_clear(DNode *head)
{
    DNode *p = head->next;
    DNode *tmp = NULL;
    while (p != head)
    {
        tmp = p->next;
        remove_node(p, head);
        p = tmp;
        /* code */
    }
}

void dlist_destroy(DNode **head)
{
    dlist_clear(*head);
    free(*head);
    *head = NULL;
}
