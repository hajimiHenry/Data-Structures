#include <stdio.h>

void swap(int *a, int *b);


int main(void)
{
    /*int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int tmp = (a < b) ? a : b;
    int min = (tmp < c) ? tmp : c;
    printf("%d\n", min);*/

    // int a, b;
    // scanf("%d %d", &a, &b);

    // swap(&a, &b);
    // printf("%d %d", a, b);



    

    return 0;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void double_it(int *p){
    
}