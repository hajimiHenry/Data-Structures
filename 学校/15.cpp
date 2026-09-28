typedef int Status;
typedef int ElemType;

// –––––线性表的链式存储结构–––––
typedef struct LNode
{
    ElemType data;
    @ @next;
} LNode, *LinkList;

//--------------基本操作-----------------
Status InitList_L(LinkList &L)
{            // 建立一个空的链表，L为带头结点的单链表的头指针.
    L = @ @; // 生成头结点
    if (!L)
        return ERROR;
    L->next = @ @;
    return OK;
} // InitList_L

Status ListInsert_L(LinkList &L, int i, ElemType e)
{ // 在带头结点的单线性链表L中第i个位置之前插入元素e
    LinkList p, s;
    int j;
    p = L;
    j = 0;
    while (p && j < i - 1)
    {
        @ @
    } // 寻找第i-1个结点
    if (!p || j > i - 1)
        return ERROR;                    // i 小于1或者大于表长
    s = (LinkList)malloc(sizeof(LNode)); // 生成新结点
    s->data = e;
    s->next = @ @; // 插入L中
    @ @;
    return OK;
} // ListInsert_L

int LocateElem_L(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{ // 在线性链表L中查找第1个值与e满足compare()的元素的位序
  // 若找到,则返回其在L中的位序,否则返回0
    int i;
    LinkList p;
    i = 1;   // i的初值为第1个元素的位序
    p = @ @; // p的初值为第1个元素的存储位置
    while (@ @)
    {
        ++i;
        p = p->next;
    }
    if (p)
        @ @;
    else
        @ @;
} // LocateElem_Sq

Status GetElem_L(LinkList L, int i, ElemType &e)
{ // L为带头结点的单链表的头指针.
  // 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
    LinkList p;
    int j;
    @ @;
    @ @;
    while (p && j < i)
    { // 顺指针向后查找,直到p指向第i个元素或p为空
        @ @
    }
    if (!p || j > i)
        return ERROR; // 第i个元素不存在
    e = @ @;          // 取第i个元素
    return OK;
} // GetElem_L

int ListEmpty_L(LinkList L)
{
    if (@ @)
        return TRUE;
    else
        return FALSE;
}

int ListLength_L(LinkList L)
{
    LinkList p;
    int len = 0;
    p = @ @;
    while (p)
    {
        @ @
    }
    return len;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e)
{ // 在带头结点的单链线性表L中,删除第i个元素,并由e返回其值
    int j;
    LinkList p, q;
    p = L;
    j = 0;
    while (@ @)
    {
        p = p->next;
        ++j;
    } // 寻找第i个元素,并令p指向其前驱
    if (!(p->next) || j > i - 1)
        return ERROR; // 删除位置不合理
    q = @ @;
    @ @; // 删除并释放结点
    e = @ @;
    free(q);
    return OK;
}