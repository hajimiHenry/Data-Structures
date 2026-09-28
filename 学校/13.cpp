#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    int next;

} LNode;

void ListAppend(int data, int addr, int next, LNode arr[])
{

    arr[addr].data = data;
    arr[addr].next = next;
}

// 要放进来的这个节点,是要移动的那个节点的前一个节点
void LNodeMov(int addr, LNode from[], LNode to[], int *tail, int *head_D)
{
    int addr_next = from[addr].next;

    // 第一步是把上一个节点的next指向当前要改动的节点
    if (*tail != -2)
    {
        to[*tail].next = addr_next;
    }
    else
        *head_D = addr_next;

    // 把要移动的这个节点放进后一个链表
    to[addr_next].data = from[addr_next].data;
    to[addr_next].next = -1; // 暂时把它的后继做成null,因为不知道下一个节点的地址是什么
    // 从原链表当中删除这个元素
    from[addr].next = from[addr_next].next;
    // 维护一个当前的 尾巴的数值,
    *tail = addr_next;
}

int main(void)
{
    LNode arr[100000];
    int addr0, num;
    scanf("%d%d", &addr0, &num);
    for (int i = 0; i < num; i++)
    {
        int addr, data, next;
        scanf("%d%d%d", &addr, &data, &next);
        ListAppend(data, addr, next, arr);
    }

    int tail = -2; //-2是初始的数值
    int head_D = -1;

    LNode arr_D[100000] = {0};

    int seen[100000] = {0};
    int cur = addr0;
    int tmp_prior;
    while (cur != -1)
    {
        seen[abs(arr[cur].data)] += 1;

        if (seen[abs(arr[cur].data)] > 1)
        {

            LNodeMov(tmp_prior, arr, arr_D, &tail, &head_D);
        }
        else
            tmp_prior = cur;

        cur = arr[cur].next;
    }

    int cur_o = addr0;
    while (cur_o != -1)
    {
        if (arr[cur_o].next != -1)
        {
            printf("%05d %d %05d\n", cur_o, arr[cur_o].data, arr[cur_o].next);
        }
        else
            printf("%05d %d %d\n", cur_o, arr[cur_o].data, arr[cur_o].next);

        cur_o = arr[cur_o].next;
    }
    int cur_D_o = head_D;
    while (cur_D_o != -1)
    {
        if (arr_D[cur_D_o].next != -1)
        {
            printf("%05d %d %05d\n", cur_D_o, arr_D[cur_D_o].data, arr_D[cur_D_o].next);
        }

        else
            printf("%05d %d %d\n", cur_D_o, arr_D[cur_D_o].data, arr_D[cur_D_o].next);

        cur_D_o = arr_D[cur_D_o].next;
    }

    return 0;
}
