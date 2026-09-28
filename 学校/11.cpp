#include <stdio.h>
#include <stdlib.h>

// 用带头结点的单链表表示字符集合，用基本操作实现字符集合的交集（以第二个集合为主）。请先实现单链表的基本操作。

typedef char ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/* 你的程序将嵌在这里 */

void InitList(LinkList &L);
void ListInsert(LinkList &L, int a, ElemType e);
void jiaoji(LinkList &La, LinkList &Lb, LinkList &Lc);
int ListLength(LinkList &L);
void GetElem(LinkList &Lc, int i, ElemType &e);
void DestroyList(LinkList &La);
LNode *MakeNode(ElemType a);

int main(void)
{
    int i, j, len;
    ElemType e;
    LinkList La, Lb, Lc;
    int m, n; // 分别存放两个集合初始长度
    scanf("%d%d", &m, &n);
    getchar();
    InitList(La);
    InitList(Lb);            // 建立两个空集
    for (i = 1; i <= m; i++) // 建立第一个集合
    {
        scanf("%c", &e);
        ListInsert(La, i, e);
    }
    getchar();
    for (i = 1; i <= n; i++) // 建立第二个集合
    {
        scanf("%c", &e);
        ListInsert(Lb, i, e);
    }
    jiaoji(La, Lb, Lc); // 计算集合 La、Lb 的交集 Lc
    // 输出结果
    len = ListLength(Lc);
    for (i = 1; i <= len; i++)
    {
        GetElem(Lc, i, e);
        printf("%c", e);
    }
    DestroyList(La);
    DestroyList(Lb);
    DestroyList(Lc); // 销毁 3 个集合
    return 0;
}

void InitList(LinkList &L)
{
    // 创建一个头节点
    L = MakeNode(0);
}

int ListLength(LinkList &L)
{
    int length = 0;
    LNode *cur = L; // 头节点
    while (cur->next != NULL)
    {
        cur = cur->next;
        length++;
    }

    return length;
}

LNode *MakeNode(ElemType a)
{
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->data = a;
    p->next = NULL;

    return p;
}

void ListInsert(LinkList &L, int a, ElemType e)
{
    // 验证这个a是否超过了 链表的长度
    LNode *L_test = L;
    int test = 0;
    while (L_test->next != NULL)
    {
        L_test = L_test->next;
        test++;
    }
    // 题目约定：a 是插入后新元素的位序，合法范围 1 ~ len+1（len+1 即插在末尾）
    if (a < 1 || a > test + 1)
    {
        exit(1);
    }

    LNode *p = MakeNode(e);
    // 走到第 a-1 个节点（头结点算第 0 个），新节点挂在它后面
    LNode *cur = L;
    for (int i = 0; i < a - 1; i++)
    {
        cur = cur->next;
    }
    LNode *front = cur->next;
    cur->next = p;
    p->next = front;
}

void DestroyList(LinkList &La)
{
    LNode *cur = La;
    LNode *tmp = NULL;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

void GetElem(LinkList &L, int a, ElemType &e)
{
    // 走到第a个真实节点
    LNode *cur = L;
    for (int i = 0; i < a; i++)
    {
        cur = cur->next;
    }

    e = cur->data;
}

void jiaoji(LinkList &La, LinkList &Lb, LinkList &Lc)
{

    InitList(Lc);
    // 两个光标都是从第一个实际节点开始
    LNode *cur_a = La->next;
    LNode *cur_b = Lb->next;

    int LcCount = 1; // 下一个要插入 Lc 的位序，按题目约定从 1 开始
    while (cur_b != NULL)
    {
        while (cur_a != NULL)
        {
            if (cur_a->data == cur_b->data)
            {
                ListInsert(Lc, LcCount, cur_b->data);
                LcCount++;
                break;
            }
            cur_a = cur_a->next;
        }
        cur_a = La->next;
        cur_b = cur_b->next;
    }
}