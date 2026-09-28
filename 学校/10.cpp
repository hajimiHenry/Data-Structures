#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int ElemType;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// –––––线性表的动态分配顺序存储结构–––––
#define LIST_INIT_SIZE 30 // 线性表存储空间的初始分配
#define LISTINCREMENT 10  // 线性表存储空间的分配增量
typedef struct SqList
{
    ElemType *elem; // 存储空间基址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储容量(以sizeof(ElemType)为单位)
} SqList;

//--------------基本操作-----------------
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * (sizeof(ElemType)));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
} // InitList_Sq      算法2.3

int ListLength_Sq(SqList L)
{
    return L.length;
}

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
    if (i > L.length)
        return ERROR;
    e = L.elem[i];
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{ //  在顺序线性表L中第i个位置之前插入新的元素e,
  //  i的合法值为1≤i≤ListLength_Sq(L)+1
    ElemType *newbase, *p, *q;

    if (i < 1 || i > L.length + 1)
        return ERROR;           // i 值不合法
    if (L.length >= L.listsize) // 当前存储空间已满,增加分配
    {
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);          // 存储分配失败
        L.elem = newbase;            //  新基址
        L.listsize += LISTINCREMENT; //  增加存储容量
    }
    q = &(L.elem[i]); // q为插入位置
    if (L.length >= 1)
        for (p = &(L.elem[L.length - 1]); p >= q; --p)
            *(p + 1) = *p;
    *q = e; // 插入e
    L.length++;
    return OK;
} // ListInsert_Sq

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    int i;
    ElemType *p;
    i = 1;
    p = L.elem; // p的初值为第1个元素的存储位置
    while (i <= L.length && compare(e, *p++))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
} // LocateElem_Sq

// 已知顺序线性表La和Lb的元素按值非递减排列，合并La和Lb得到新的顺序线性表Lc,  Lc的元素也按值非递减排列。
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
    int i, j, k;
    int La_len, Lb_len;
    ElemType ai, bj;
    InitList_Sq(Lc);
    i = j = 1;
    k = 0;
    La_len = La.length;
    Lb_len = Lb.length;
    while (La_len > 0 && Lb_len > 0) // La和Lb均非空
    {
        GetElem_Sq(La, i, ai);
        GetElem_Sq(Lb, j, bj);
        if (ai <= bj)
        {
            ListInsert_Sq(Lc, k++, ai);
            ++i;
        }
        else
        {
            ListInsert_Sq(Lc, k++, bj);
            ++j;
        }
    }
    while (i <= La_len)
    {
        GetElem_Sq(La, i, ai);
        ListInsert_Sq(Lc, ++k, ai);
        ++i;
    }
    while (j <= Lb_len)
    {
        GetElem_Sq(Lb, i, bj);
        ListInsert_Sq(Lc, ++k, bj);
        ++j;
    }
}

// 已知顺序线性表La和Lb的元素按值非递减排列，合并La和Lb得到新的顺序线性表Lc,  Lc的元素也按值非递减排列。
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    pa = La.elem;
    pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
    if (!Lc.elem)
        exit(OVERFLOW); // 存储分配失败
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last) // 归并
    {
        if (*pa <= *pb)
            *pc++ = *pa++;

        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last)
        *pc++ = *pa++;
    while (pb <= pb_last)
        *pc++ = *pb++;
}