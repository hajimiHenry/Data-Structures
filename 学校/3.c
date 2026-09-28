#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LnodeStu
{
    int grade;            // 成绩
    char name[50], id[6]; // 姓名、学号（学号最多 5 字符 + '\0'）
    struct LnodeStu *next;
} LnodeStu;

LnodeStu *MakeNode(int grade, char name[], char id[]);
void AddNode(LnodeStu *head, int grade, char name[], char id[]);
void InputSource(int N, LnodeStu *head);

int main(void)
{
    int N; // 学生数量
    char id_check[6];
    scanf("%d", &N);

    LnodeStu *head = MakeNode(0, "head", "111");

    InputSource(N, head);

    scanf("%s", id_check);

    // 从第一个真实结点开始找，strcmp 返回 0 才是命中
    LnodeStu *cur = head->next;
    while (cur != NULL && strcmp(cur->id, id_check) != 0)
    {
        cur = cur->next;
    }

    if (cur == NULL) // 走到表尾还没命中
        printf("not found!");
    else
        printf("%d", cur->grade);

    return 0;
}

LnodeStu *MakeNode(int grade, char name[], char id[])
{
    LnodeStu *p = malloc(sizeof(LnodeStu));
    if (p == NULL)
    {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    p->grade = grade;
    strcpy(p->id, id);
    strcpy(p->name, name);
    p->next = NULL;

    return p;
}

void AddNode(LnodeStu *head, int grade, char name[], char id[])
{
    // 走到最后一个结点
    LnodeStu *cur = head;
    while (cur->next != NULL)
        cur = cur->next;

    // 创建新结点，挂到表尾
    LnodeStu *p = MakeNode(grade, name, id);
    cur->next = p;
}

void InputSource(int N, LnodeStu *head)
{
    for (int i = 0; i < N; i++)
    {
        char name[50], id[6];
        int grade;
        scanf("%s %s %d", id, name, &grade);
        AddNode(head, grade, name, id);
    }
}
