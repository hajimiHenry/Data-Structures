#ifndef DLIST_H
#define DLIST_H

typedef struct DNode
{
    int data;
    struct DNode *prev, *next;
    /* data */
} DNode;

DNode *dlist_init(void);                 // 造哨兵,自己咬自己
void insert_after(DNode *p, int data);   // 在结点 p 后插 —— 4 根箭头的主战场
void insert_before(DNode *p, int data);  // 想想:能不能一行调用 insert_after 搞定?
void push_front(DNode *head, int data);  // = insert_after(head, ...) 一行
void push_back(DNode *head, int data);   // = insert_before(head, ...) 一行,O(1)!
void remove_node(DNode *p, DNode *head); // 摘掉 p 本人(不许传哨兵,想想怎么防)
void print_list(DNode *head);            // 正序
void print_reverse(DNode *head);         // 倒序 —— 双链表的招牌菜
int length(DNode *head);
void dlist_clear(DNode *head);    // 清空,哨兵可复用
void dlist_destroy(DNode **head); // 全拆

#endif