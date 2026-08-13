#include <stdio.h>
#include <stdlib.h>
#include "Lstack.h"

int main(void)
{
    Lstack s;
    init_lstack(&s);

    if (!is_empty(&s) == 0)
    {
        printf("lstack empty\n");
        /* code */
    }

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("top:%d\n", peek(&s));

    int take_top = 0;
    pull(&s, &take_top);
    printf("takentop:%d\n", take_top);

    print_list(s.head);

    printf("top:%d\n", peek(&s));

    destroy_lstack(&s);

    // if (is_empty(&s) != 0)
    // {
    //     printf("lstack is empty\n");
    //     /* code */
    // }

    return 0;
}