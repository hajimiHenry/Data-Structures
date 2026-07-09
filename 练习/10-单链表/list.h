#ifndef LIST_H
#define LIST_H

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// —— 菜单区:只有声明(原型 + 分号),没有大括号 ——
// 本链表带头结点,结点从第 1 个开始编号,头结点不算、不计入 length
Node *list_init(void);
Node *make_node(int data);
void push_front(Node *head, int data);
void push_back(Node *head, int data);
void print_list(Node *head);
int length(Node *head);
void list_insert(Node *head, int seq, int data); // 插在第 seq 个之后,seq=0 即头插
void list_remove(Node *head, int seq);           // 删除第 seq 个
void list_clear(Node *head);                     // 清空数据结点,头结点保留可复用
void list_destroy(Node *head);                   // 连头结点一起释放,此后 head 不可再用

#endif
