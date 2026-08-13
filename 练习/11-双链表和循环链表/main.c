#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

int main(void)
{
    DNode *head = dlist_init();
    insert_after(head, 1);
    insert_after(head, 2);
    insert_after(head, 3);

    print_list(head);

    insert_before(head, 4);
    insert_before(head, 5);
    insert_before(head, 6);

    print_list(head);

    push_front(head, 7);
    push_front(head, 8);
    push_front(head, 9);

    print_list(head);

    push_back(head, 10);
    push_back(head, 11);
    push_back(head, 12);

    printf("==========当前长度为：%d============\n", length(head));

    print_list(head);
    print_reverse(head);

    DNode *rmv = head;
    for (int i = 0; i < 3; i++)
    {
        rmv = rmv->next;
        /* code */
    }

    remove_node(rmv, head);
    print_list(head);

    dlist_clear(head);

    print_list(head);

    dlist_destroy(&head);

    print_list(head);

    return 0;
}
