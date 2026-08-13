#ifndef STACK_H
#define STACK_H
#define maxsize 10

typedef struct sqstack
{
    int stack[maxsize];
    int top;
    /* data */
} sqstack;

void initstack(sqstack *sqstack);
void push(sqstack *sqstack, int data);
void pull(sqstack *sqstack, int *take);
int check_stack_top(sqstack *sqstack);
void print_stack(sqstack *sqstack);

#endif
