#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
    /* data */
} Node;

Node *make_node(int data);
Node *push_front(Node *head, int data);
Node *push_back(Node *head, int data);
void print_list(Node *head);
int length(Node *head);
void free_all(Node *head);
void push_back2(Node **head, int data);
void push_front2(Node **head, int data);
void list_insert(Node **head, int seq, int data);
void list_remove(Node **head, int seq);

int main(void)
{
    Node *head = NULL;
    head = push_front(head, 1);
    head = push_front(head, 2);
    head = push_front(head, 3);
    push_front2(&head, 5);

    head = push_back(head, 1);
    head = push_back(head, 2);
    head = push_back(head, 3);
    push_back2(&head, 6);

    print_list(head);

    list_insert(&head, 3, 100);
    list_insert(&head, 0, 200);
    list_insert(&head, 200, 300);
    list_insert(&head, -1, 400);

    print_list(head);

    list_remove(&head, -1);
    list_remove(&head, 200);
    list_remove(&head, 0);
    list_remove(&head, 1);
    list_remove(&head, 5);

    print_list(head);

    printf("len:%d\n", length(head));
    free_all(head);

    return 0;
}

Node *push_front(Node *head, int data)
{
    Node *n = make_node(data);
    n->next = head;

    return n;
}

void push_front2(Node **head, int data)
{
    Node *n = make_node(data);
    n->next = *head;
    *head = n;
}

Node *make_node(int data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
    {
        fprintf(stderr, "malloc failed");
        exit(1);
        /* code */
    }
    p->data = data;
    p->next = NULL;

    return p;
}

Node *push_back(Node *head, int data)
{
    Node *n = make_node(data);
    if (head == NULL)
    {
        return n;
        /* code */
    }

    Node *cur = head;
    Node *tmp = NULL;
    while ((cur != NULL))
    {
        tmp = cur;
        cur = cur->next;
        /* code */
    }
    tmp->next = n;
    return head;
}

void push_back2(Node **head, int data)
{
    Node *n = make_node(data);
    if (*head == NULL)
    {
        *head = n;
        return; // void 类型直接return不要有返回值
        /* code */
    }

    Node *cur = *head;
    Node *tmp = cur;
    while (cur != NULL)
    {
        tmp = cur;
        cur = cur->next;
        /* code */
    }
    tmp->next = n;
}

void print_list(Node *head)
{
    Node *cur = head;
    if (cur == NULL)
    {
        fprintf(stderr, "list not built");
        /* code */
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

    Node *cur = head;
    while (cur != NULL)
    {
        len++;
        cur = cur->next;
        /* code */
    }
    return len;
}

void free_all(Node *head)
{

    Node *cur = head;
    Node *tmp = NULL;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;

        /* code */
    }
}

// 计算方式是从第1个开始算，写0也就是在不存在-1后面插节点，也就是头插节点   插入是从seq之后插
void list_insert(Node **head, int seq, int data)
{
    if (seq > length(*head) || seq < 0)
    {
        printf("越界了，来自list_insert,想添加的次序是%d\n", seq);
        return;
        /* code */
    }

    // 插入在开头
    if (seq == 0)
    {
        push_front2(head, data);
        /* code */
    }
    else
    {
        // 插入在中间
        Node *cur = *head;
        for (int i = 0; i < seq - 1; i++)
        {
            cur = cur->next;
            /* code */
        }

        Node *bak = cur->next;

        Node *n = make_node(data);
        cur->next = n;
        n->next = bak;
    }
}

void list_remove(Node **head, int seq)
{
    if (seq > length(*head) || seq <= 0)
    {
        printf("越界了,来自list_remove,想删除的次序是%d\n", seq);
        return;
        /* code */
    }
    else if (seq == 1)
    {
        Node *cur = *head;
        *head = cur->next;
        free(cur);
        /* code */
    }
    else
    {
        Node *cur = *head;
        Node *bef = NULL;
        for (int i = 0; i < seq - 1; i++)
        {
            bef = cur;
            cur = cur->next;

            /* code */
        }
        bef->next = cur->next;
        free(cur);
        /* code */
    }
}
