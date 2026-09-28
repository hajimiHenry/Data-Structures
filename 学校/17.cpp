#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef int Status;

typedef struct
{             // 项的表示,多项式的项作为LinkList的数据元素
    int coef; // 系数COEFFICIENT
    int expn; // 指数EXPONENT
} term, ElemType;

typedef struct LNode // 结点类型
{
    ElemType data;
    struct LNode *next;
} *Link, *Position;
typedef struct // 链表类型
{
    Link head, tail; // 分别指向线性链表中的头结点和最后一个结点
    int len;         // 指向线性链表中数据元素的个数
} LinkList;
typedef LinkList polynomial; // 用带表头结点的有序链表表示多项式

/* 请在这里填写答案 */

void CreatePolyn(polynomial Pa, int m)
{
}

void AddPolyn(polynomial Pa, polynomial Pb)
{
}

LNode *GetHead(polynomial Pa)
{
}

LNode *NextPos(polynomial Pa, Position ha)
{
}

int main()
{
    polynomial Pa, Pb;
    int m, n;
    Position ha, hb, qa, qb;
    term a;
    scanf("%d", &m);
    CreatePolyn(Pa, m);
    scanf("%d", &n);
    CreatePolyn(Pb, n);
    AddPolyn(Pa, Pb);
    if (Pa.len == 0)
    {
        printf("0\n");
        return 0;
    }
    ha = GetHead(Pa); // ha和hb分别指向Pa和Pb的头结点
    qa = NextPos(Pa, ha);
    while (qa)
    {
        printf("%d,%d\n", qa->data.coef, qa->data.expn);
        ha = qa;
        qa = NextPos(Pa, ha);
    }
    return 0;
}