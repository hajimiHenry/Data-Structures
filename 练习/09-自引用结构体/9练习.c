#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    /* data */
} Node;

Node *make_node(int data);
void free_list(Node *head);

int main(void)
{
    Node *a = make_node(1);
    Node *b = make_node(2);
    Node *c = make_node(3);

    a->next = b;
    b->next = c;
    c->next = NULL;

    Node *head = a;
    Node *cur = head;

    int counter = 0;

    while (cur != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->next;
        counter++;
    }

    printf("%d\n", counter);

    free_list(head);

    return 0;
}

Node *make_node(int data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
    {
        fprintf(stderr,"malloc failed\n");
        exit(1);
        /* code */
    }
    
    p->data = data;
    p->next = NULL;
    return p;
}

void free_list(Node *head)
{

    while (head != NULL)
    {
        Node *tmp = head;
        head = head->next;
        free(tmp);
        /* code */
    }
}