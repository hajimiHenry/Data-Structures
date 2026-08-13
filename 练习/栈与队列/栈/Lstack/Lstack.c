#include <stdio.h>
#include <stdlib.h>
#include "Lstack.h"

void init_lstack(Lstack *s)
{
    s->head = list_init();
}

void push(Lstack *s, int data)
{
    push_front(s->head, data);
} // 压栈 → 头插
int pull(Lstack *s, int *take)
{
    if (s->head->next == NULL)
    {
        return -1; /* code */
    }
    else
    {
        *take = s->head->next->data;
        list_remove(s->head, 1);
        return 0;
    }

} // 弹栈 → 头删，通过 take 输出。返回 0=成功，-1=空栈
int peek(Lstack *s)
{
    return s->head->next->data;
}

// 看栈顶（不弹）
int is_empty(Lstack *s)
{
    if (s->head->next == NULL)
    {
        return 1; // 是空的
        /* code */
    }
    else
        return 0; // 不是空的

} // 判空
void destroy_lstack(Lstack *s)
{
    list_destroy(s->head);
} // 销毁整条链
