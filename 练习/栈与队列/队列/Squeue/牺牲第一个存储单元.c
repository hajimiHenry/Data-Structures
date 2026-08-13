#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxsize 10

typedef struct queue
{
    int data[maxsize];
    int front, rear;
    /* data */
} queue;

void InitQueue(queue *qptr);
bool EmptyQueue(queue *qptr);
bool FullQueue(queue *qptr);
void EnQueue(queue *qptr, int data);
void DeQueue(queue *qptr, int *takeout);
void GetHead(queue *qptr, int *takeout);

int main(void)
{
    queue q;

    return 0;
}

void InitQueue(queue *qptr)
{
    qptr->front = 0;
    qptr->rear = 0;
}

bool EmptyQueue(queue *qptr)
{

    if (qptr->front == qptr->rear)
    {
        return true;
        /* code */
    }
    else
        return false;
}

bool FullQueue(queue *qptr)
{
    if (((qptr->rear + 1) % maxsize) == qptr->front)
    {
        return true;
        /* code */
    }
    else
        return false;
}

void EnQueue(queue *qptr, int data)
{
    if (FullQueue(qptr))
    {
        fprintf(stderr, "队列已满");
        exit(1);
        /* code */
    }
    qptr->data[qptr->rear] = data;
    qptr->rear = (qptr->rear + 1) % maxsize;
}

void DeQueue(queue *qptr, int *takeout)
{
    if (EmptyQueue(qptr))
    {
        fprintf(stderr, "队列是空的");
        exit(1);
        /* code */
    }

    *takeout = qptr->data[qptr->front];
    qptr->front = (qptr->front + 1) % maxsize;
}

void GetHead(queue *qptr, int *takeout)
{
    if (EmptyQueue(qptr))
    {
        fprintf(stderr, "队列是空的");
        exit(1);
        /* code */
    }
    *takeout = qptr->data[qptr->front];
}