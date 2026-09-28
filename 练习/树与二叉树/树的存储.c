#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
// 双亲表示法
typedef struct PTNode
{
    int parent;
    int date;
    /* data */
} PTNode;

typedef struct PTree
{
    PTNode nodes[MAXSIZE];
    int n;
    /* data */
};

// 孩子表示法

typedef struct CTnode
{
    int data;
    struct CTnode *next;
    /* data */
} CTnode;

typedef struct CTBox
{
    int data;
    int order;
    CTnode *FirstChild;
    /* data */
} CTBox;

typedef struct CTree
{
    CTBox Tree[MAXSIZE];
    int n, r; // 其中n是当前数组占用的数量, r是根节点在数组当中的位置
    /* data */
};

// 孩子兄弟表示法

typedef struct CSNode
{
    int daata;
    struct CSNode *FirstChild;
    struct CSNode *NextSibling;
} CSNode;
