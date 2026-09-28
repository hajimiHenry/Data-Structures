#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode
{
    int data;
    struct Lnode *next;
    struct Lnode *prior;
    int lengh;

} Lnode;

Lnode *Makenode(int data);
Lnode *ListInit(void);
void ListAppend(Lnode &Last, int data);
int GetTheOne(Lnode &last, int num);

int main(void)
{
    Lnode *head = ListInit();
    Lnode *cur = head;
    int K;

    scanf("%d", &K);
    do
    {
        int app;
        scanf("%d", &app);
        if (app < 0)
        {
            break;
        }

        ListAppend(*cur, app);
        cur = cur->next;

    } while (1);

    int output = GetTheOne(*cur, K);

    if (output == -1)
    {
        printf("NULL\n");
    }
    else
        printf("%d\n", output);

    return 0;
}

Lnode *Makenode(int data)
{
    Lnode *p = (Lnode *)malloc(sizeof(Lnode));
    if (p == NULL)
    {
        exit(0);
    }
    p->data = data;
    p->next = NULL;
    p->prior = NULL;
    p->lengh = 0;

    return p;
}

Lnode *ListInit(void)
{
    return Makenode(0);
}
// 因为只需要增加,所以只要在主函数当中维护
void ListAppend(Lnode &Last, int data)
{
    Lnode *p = Makenode(data);
    Last.next = p;
    p->prior = &Last;
    p->lengh = ++Last.lengh;
}

int GetTheOne(Lnode &last, int num)
{
    if (num > last.lengh)
    {
        return -1;
    }

    Lnode *cur = &last;
    for (int i = 0; i < num - 1; i++)
    {
        cur = cur->prior;
    }

    return cur->data;
}
