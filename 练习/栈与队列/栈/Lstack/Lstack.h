#ifndef LSTACK_H
#define LSTACK_H

#include "list.h"

typedef struct Lstack
{
    Node *head;
    /* data */
} Lstack;

void init_lstack(Lstack *s);    // new 一个哨兵链表
void push(Lstack *s, int data); // 压栈 → 头插
int pull(Lstack *s, int *take); // 弹栈 → 头删，通过 take 输出。返回 0=成功，-1=空栈
int peek(Lstack *s);            // 看栈顶（不弹）
int is_empty(Lstack *s);        // 判空，return1 是空的 return0不是空的
void destroy_lstack(Lstack *s); // 销毁整条链

#endif