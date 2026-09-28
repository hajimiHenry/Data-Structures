#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType[20];

/* 你的程序将嵌在这里 */
#define LIST_INIT_SIZE 30 // 存储空间的初始分配
#define LISTINCREMENT 10  // 存储空间的分配增量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct SqList
{
    ElemType *data; // 存储空间基址，每个槽是一个 char[20]
    int listlength; // 当前长度
    int listsize;   // 当前容量（单位：sizeof(ElemType)）
} SqList;

void InitList_Sq(SqList &L);
void DestroyList_Sq(SqList &L);
int ListLength_Sq(SqList &L);
void GetElem_Sq(SqList &Lc, int i, ElemType &e);
void ListInsert_Sq(SqList &L, int i, ElemType e);
void DeleteList(SqList &L, int i);

// 计算集合 La、Lb 的差集 Lc
void chaji_Sq(SqList &La, SqList &Lb, SqList &Lc);

int ListLength_Sq(SqList &L)
{
    return L.listlength;
}

void InitList_Sq(SqList &L)
{
    L.data = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (L.data == NULL)
    {
        exit(OVERFLOW);
    }

    L.listlength = 0;
    L.listsize = LIST_INIT_SIZE;
}
void ListInsert_Sq(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.listlength + 1)
    {
        exit(OVERFLOW);
    }
    // 顺序表不够长，先扩容
    if (L.listlength == L.listsize)
    {
        ElemType *tmp = (ElemType *)realloc(
            L.data, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (tmp == NULL)
        {
            exit(OVERFLOW);
        }
        L.data = tmp;
        L.listsize += LISTINCREMENT;
    }
    // 从表尾往插入位置倒着搬，空出第 i 个位置
    int start = i - 1;
    for (int end = L.listlength - 1; end >= start; end--)
    {
        strcpy(L.data[end + 1], L.data[end]);
    }
    strcpy(L.data[start], e);
    L.listlength++;
}

void DestroyList_Sq(SqList &L)
{
    free(L.data);
    L.data = NULL;
    L.listlength = 0;
    L.listsize = 0;
}

void GetElem_Sq(SqList &Lc, int i, ElemType &e)
{
    strcpy(e, Lc.data[i - 1]);
}

// 从顺序表中删除第 i 个（位序）元素
void DeleteList(SqList &L, int i)
{
    // 要删的元素下标是 i-1，第一个要往前搬的是下标 i
    int end = L.listlength - 1;
    for (int start = i; start <= end; start++)
    {
        strcpy(L.data[start - 1], L.data[start]);
    }
    L.listlength--;
}

// C = A - B：先把 La 整体拷进 Lc，再把 Lb 里出现过的删掉
void chaji_Sq(SqList &La, SqList &Lb, SqList &Lc)
{
    InitList_Sq(Lc);
    // 用 La 把 Lc 填满
    for (int i = 0; i < La.listlength; i++)
    {
        ListInsert_Sq(Lc, i + 1, La.data[i]);
    }
    // 逐个看 Lc 中是否存在 Lb 的元素
    for (int i = 0; i < Lb.listlength; i++)
    {
        for (int j = 0; j < Lc.listlength; j++)
        {
            if (strcmp(Lc.data[j], Lb.data[i]) == 0)
            {
                DeleteList(Lc, j + 1);
            }
        }
    }
}

int main()
{
    int i, j, len;
    ElemType e;
    SqList La, Lb, Lc;
    int m, n; // 分别存放两个集合初始长度
    printf("input the length of two set:\n");
    scanf("%d%d", &m, &n);
    InitList_Sq(La);
    InitList_Sq(Lb); // 建立两个空集
    printf("input the first set:\n ");
    for (i = 0; i < m; i++) // 建立第一个集合
    {
        scanf(" %s", e);
        ListInsert_Sq(La, i + 1, e);
    } // 注意有空格
    printf("input the second set:\n ");
    for (i = 1; i <= n; i++) // 建立第二个集合
    {
        scanf(" %s", e);
        ListInsert_Sq(Lb, i, e);
    } // 注意有空格
    chaji_Sq(La, Lb, Lc); // 计算集合La、Lb的差集Lc
    printf("the chaji set is:\n");
    len = ListLength_Sq(Lc);
    for (i = 1; i <= len; i++)
    {
        GetElem_Sq(Lc, i, e);
        printf("%s\n", e);
    }
    DestroyList_Sq(La);
    DestroyList_Sq(Lb);
    DestroyList_Sq(Lc); // 销毁3个集合（顺序表）
    return 0;
}
