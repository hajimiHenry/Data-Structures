#include <stdio.h>
#include <stdlib.h>

typedef struct team
{
    int length;
    man *head;
} team;

typedef struct man
{
    int num;
    int m;
    struct man *next;
} man;

man *makenode(int num, int m)
{
    man *p = (man *)malloc(sizeof(man));
    p->m = m;
    p->num = num;
    p->next = NULL;

    return p;
}

void ListAppend(int num, int m, team *all)
{
    man *cur = all->head;
    while (cur != NULL)
    {
        cur = cur->next;
    }
    man *p = (man *)malloc(sizeof(man));
    cur->next = p;

    all->length++;
}

void ListRemove(int num, team *all)
{
    man *cur = all->head;
    man *tmp = NULL;
    while (cur->num != num)
    {
        tmp = cur;
        cur = cur->next;
    }
    tmp->next = cur->next;
    free(tmp);
}

int main(void)
{
    team *team;

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int m;
        scanf("%d", m);
        ListAppend(++i, m, team);
    }
}