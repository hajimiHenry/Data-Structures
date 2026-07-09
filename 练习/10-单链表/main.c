#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    Node *head = list_init();

    print_list(head);
    printf("len = %d\n", length(head));
   
    push_front(head, 1);
    push_front(head, 2);
    push_front(head, 3);
    push_front(head, 4);
    push_front(head, 5);

    push_back(head, 6);
    push_back(head, 7);
    push_back(head, 8);
    push_back(head, 9);
    push_back(head, 10);

    print_list(head);
    printf("len = %d\n", length(head));

    list_insert(head, -1, 100);
    list_insert(head, 0, 200);
    list_insert(head, 1, 300);
    list_insert(head, 2, 400);
    list_insert(head, 3, 500);
    list_insert(head, 100, 500);

    print_list(head);
    printf("len = %d\n", length(head));

    list_remove(head, -1);
    list_remove(head, 0);
    list_remove(head, 1);
    list_remove(head, 2);
    list_remove(head, 3);
    list_remove(head, length(head)+1);


    print_list(head);
    printf("len = %d\n", length(head));

    list_clear(head);

    print_list(head);
    printf("len = %d\n", length(head));

    list_insert(head, -1, 100);
    list_insert(head, 0, 200);
    list_insert(head, 1, 300);
    list_insert(head, 2, 400);
    list_insert(head, 3, 500);
    list_insert(head, 100, 500);

    print_list(head);
    printf("len = %d\n", length(head));

    list_destroy(head);
    
    return 0;
}
