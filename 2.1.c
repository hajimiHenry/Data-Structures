#include <stdio.h>

void swap(int *a, int *b);
void double_it(int *p);
void set_null(int **pp);
void reverse(int *a, int n);
void bubble(int a[], int n);

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

    // int a, b;

    // scanf("%d", &a);
    // int *p = &a;

    // double_it(&a);
    // printf("%d\n", a);

    // set_null(&p);
    // printf("%p %d\n", p, a);

    int a[] = {3, 2, 7, 6, 4};

    bubble(a, 5);
    return 0;
}

void bubble(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1-i; j++)
        {
            printf("a[%d] == %d , a[%d]== %d \n",i ,a[i],j+1,a[j+1]);
            if (a[j] >= a[j+1])
            {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                
                /* code */
            }
            
            /* code */
        }

        /* code */
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
        /* code */
    }
}




void reverse(int *a, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
        /* code */
    }
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void double_it(int *p)
{
    *p *= 2;
}

void set_null(int **pp)
{
    *pp = NULL;
}