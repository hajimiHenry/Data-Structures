#include <stdio.h>  // 实现里用了 fprintf
#include <stdlib.h> // 实现里用了 malloc / exit
#include "list.h"   // 贴进菜单,本文件才认识 Node

Node *make_node(int data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
    {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    p->data = data;
    p->next = NULL;

    return p;
}

Node *list_init(void)
{
    return make_node(0);
}

void push_front(Node *head, int data)
{
    Node *n = make_node(data);
    n->next = head->next;
    head->next = n;
}

void push_back(Node *head, int data)
{
    Node *n = make_node(data);
    Node *cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = n;
}

void print_list(Node *head)
{
    Node *cur = head->next;
    if (cur == NULL)
    {
        fprintf(stderr, "list not built\n");
    }

    while (cur != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}

int length(Node *head)
{
    int len = 0;

    Node *cur = head->next;
    while (cur != NULL)
    {
        len++;
        cur = cur->next;
    }
    return len;
}

// 计算方式是从第1个开始算，写0也就是在不存在的第0个后面插节点，也就是头插节点   插入是从seq之后插
void list_insert(Node *head, int seq, int data)
{
    if (seq > length(head) || seq < 0)
    {
        printf("越界了,来自list_insert,想添加的次序是%d\n", seq);
        return;
    }
    else
    {
        Node *cur = head;
        for (int i = 0; i < seq; i++)
        {
            cur = cur->next;
        }

        Node *bak = cur->next;

        Node *n = make_node(data);
        cur->next = n;
        n->next = bak;
    }
}

void list_remove(Node *head, int seq)
{
    if (seq > length(head) || seq <= 0)
    {
        printf("越界了,来自list_remove,想删除的次序是%d\n", seq);
        return;
    }
    else
    {
        Node *cur = head;
        Node *bef = NULL;
        for (int i = 0; i < seq; i++)
        {
            bef = cur;
            cur = cur->next;
        }
        bef->next = cur->next;
        free(cur);
    }
}

void list_clear(Node *head)
{
    Node *cur = head->next;
    Node *tmp = NULL;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }

    head->next = NULL;
}

void list_destroy(Node *head)
{
    Node *cur = head;
    Node *tmp = NULL;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}
