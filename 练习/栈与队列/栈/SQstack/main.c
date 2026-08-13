#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void)
{
    sqstack sqstack;
    initstack(&sqstack);

    push(&sqstack, 1);

    printf("top:%d\n", sqstack.top);
    printf("当前栈顶是%d \n", check_stack_top(&sqstack));

    push(&sqstack, 2);
    push(&sqstack, 3);

    printf("当前栈顶是：%d \n", check_stack_top(&sqstack));

    int take;
    pull(&sqstack, &take);
    printf("弹出的栈顶是：%d\n", take);

    printf("top:%d\n", sqstack.top);
    printf("当前栈顶是%d \n", check_stack_top(&sqstack));

    int take2;
    pull(&sqstack, &take2);
    printf("%d\n", take2);

    return 0;
}
