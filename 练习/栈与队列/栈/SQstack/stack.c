#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void initstack(sqstack *sqstack)
{
    sqstack->top = -1;
}
// 入栈
void push(sqstack *sqstack, int data)
{
    // 判满
    if (sqstack->top == (maxsize - 1))
    {
        fprintf(stderr, "栈已满");
        exit(1);
        /* code */
    }
    // 入栈逻辑
    sqstack->top++;
    sqstack->stack[sqstack->top] = data;
}

// 出栈,第二个参数是用来承接出栈的那个数的
void pull(sqstack *sqstack, int *take)
{
    // 判空
    if (sqstack->top == -1)
    {
        fprintf(stderr, "栈是空的");
        exit(1);
        /* code */
    }
    // 出栈逻辑
    int o = sqstack->stack[sqstack->top];
    sqstack->top--;

    *take = o;
}
// 返回栈顶
int check_stack_top(sqstack *sqstack)
{
    if (sqstack->top == -1)
    {
        fprintf(stderr, "栈是空的");
        exit(1);
        /* code */
    }

    return sqstack->stack[sqstack->top];
}

void print_stack(sqstack *sqstack)
{
    for (int i = 0; i < maxsize; i++)
    {
        printf("%d\n", sqstack->stack[i]);
        /* code */
    }
}