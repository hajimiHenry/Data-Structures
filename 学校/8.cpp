#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
#define LIST_INIT_SIZE 30 // 线性表存储空间的初始分配
#define LISTINCREMENT 10  // 线性表存储空间的分配增量
typedef struct
{
    ElemType *elem; // 存储空间基址
    int length;     // 当前长度
    int listsize;   // 当前容量（单位：sizeof(ElemType)）
} SqList;

/* 你的程序将嵌在这里 */
typedef int Status;

Status InitList_Sq(SqList &L);
int ListLength_Sq(SqList L);
Status ListInsert_Sq(SqList &L, int i, ElemType e);

// i 是位序，e 接收取出的元素
Status GetElem_Sq(SqList L, int i, ElemType &e);

// 比较 x 与 y 是否相等
int equal(ElemType x, ElemType y);

// 在 L 中按 compare 查找 e，返回位序，找不到返回 FALSE
int LocateElem_Sq(SqList L, ElemType e,
                  Status (*compare)(ElemType, ElemType));

// La、Lb 分别表示集合 A、B，求 C = A ∪ B
void union_Sq(SqList La, SqList Lb, SqList &Lc);

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (L.elem == NULL)
    {
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

int ListLength_Sq(SqList L)
{
    return L.length;
}

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
    if (i > L.length || i < 1)
    {
        return OVERFLOW;
    }
    else
    {
        e = L.elem[i - 1];
    }

    return OK;
}

int equal(ElemType x, ElemType y)
{
    if (x == y)
        return TRUE;
    else
        return FALSE;
}

int LocateElem_Sq(SqList L, ElemType e,
                  Status (*compare)(ElemType, ElemType))
{
    int i = 0;
    while (i < L.length && !compare(e, L.elem[i]))
    {
        i++;
    }
    if (i >= L.length)
    {
        return FALSE;
    }

    return ++i;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    ElemType *tmp;

    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length == L.listsize)
    {
        tmp = (ElemType *)realloc(
            L.elem, (LISTINCREMENT + L.listsize) * sizeof(ElemType));
        if (tmp == NULL)
        {
            exit(OVERFLOW);
        }
        else
        {
            L.elem = tmp;
            L.listsize += LISTINCREMENT;
        }
    }

    // 从表尾往插入位置倒着搬，正着搬会覆盖后面的数据
    int start = i - 1;
    for (int end = L.length - 1; end >= start; end--)
    {
        L.elem[end + 1] = L.elem[end];
    }

    L.elem[i - 1] = e;
    L.length++;

    return OK;
}

// C = A ∪ B：先整体拷入 La，再把 Lb 中 Lc 没有的元素追加到末尾
void union_Sq(SqList La, SqList Lb, SqList &Lc)
{
    InitList_Sq(Lc);
    for (int i = 0; i < La.length; i++)
    {
        ListInsert_Sq(Lc, i + 1, La.elem[i]);
    }

    for (int j = 0; j < Lb.length; j++)
    {
        if (LocateElem_Sq(Lc, Lb.elem[j], equal) == FALSE)
        {
            ListInsert_Sq(Lc, Lc.length + 1, Lb.elem[j]);
        }
    }
}

int main()
{
    int i, j, len;
    int m, n; // 分别存放两个集合初始长度
    ElemType e;
    SqList La, Lb, Lc;
    scanf("%d%d", &m, &n);
    InitList_Sq(La);
    InitList_Sq(Lb);         // 建立两个空集
    for (i = 1; i <= m; i++) // 建立第一个集合
    {
        scanf("%d", &e);
        ListInsert_Sq(La, i, e);
    }
    for (i = 1; i <= n; i++) // 建立第二个集合
    {
        scanf("%d", &e);
        ListInsert_Sq(Lb, i, e);
    }
    union_Sq(La, Lb, Lc); // 计算集合La、Lb的并集Lc
    len = ListLength_Sq(Lc);
    for (i = 1; i <= len; i++) // 输出
    {
        GetElem_Sq(Lc, i, e);
        printf("%4d", e);
    }
    return 0;
}
