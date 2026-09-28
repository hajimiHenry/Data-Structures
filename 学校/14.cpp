#include <stdio.h>
#include <stdlib.h>

// 一个旅客 = 一个节点
typedef struct man
{
    int num;          // 编号（1..n）
    int m;            // 这个人的 m 值
    struct man *next;
} man;

man *makenode(int num, int m)
{
    man *p = (man *)malloc(sizeof(man));
    p->num = num;
    p->m = m;
    p->next = NULL;
    return p;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    // 1. 建一个不带头结点的循环链表：用 tail 记住尾巴，尾插 O(1)
    man *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++)
    {
        int m;
        scanf("%d", &m);
        man *p = makenode(i, m);
        if (head == NULL)
            head = tail = p;
        else
        {
            tail->next = p;
            tail = p;
        }
    }
    tail->next = head; // 首尾相接，成环

    // 2. 报数淘汰
    //    prev 永远指向"本轮第一个报数的人"的前一个，这样删除时手里就有前驱
    //    一开始从 1 号数起，所以 prev = 尾巴
    int m = head->m;   // m 初值由第一个人决定
    man *prev = tail;
    int remain = n;
    while (remain > n / 2) // 最多留下一半
    {
        // 报到 m 的人是从 prev 往后第 m 个；prev 先走 m-1 步停在他前面
        for (int step = 1; step < m; step++)
            prev = prev->next;

        man *victim = prev->next;
        m = victim->m;               // m 换成被扔的人的 m 值
        prev->next = victim->next;   // 摘链；下一轮从 victim 的下一个数起，prev 不动正好
        free(victim);
        remain--;
    }

    // 3. 输出：环上的顺序是编号递增的，但起点不一定是最小编号，先找最小的
    if (remain > 0)
    {
        man *start = prev;
        man *cur = prev;
        for (int i = 0; i < remain; i++)
        {
            if (cur->num < start->num)
                start = cur;
            cur = cur->next;
        }

        cur = start;
        for (int i = 0; i < remain; i++)
        {
            printf("%3d", cur->num);
            cur = cur->next;
        }
        printf("\n");

        // 释放剩下的节点
        cur = start;
        for (int i = 0; i < remain; i++)
        {
            man *nx = cur->next;
            free(cur);
            cur = nx;
        }
    }

    return 0;
}
