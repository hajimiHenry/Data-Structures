#include <stdio.h>
#include <string.h>

void swap(int *a, int *b);
void double_it(int *p);
void set_null(int **pp);
void reverse(int *a, int n);
void bubble(int a[], int n);
int total(int *p, int sum);

int total(int *p, int sum)
{
    for (int i = 0; i < 5; i++, p++)
    {
        sum += *p;
        /* code */
    }
    return sum;
}

void bubble(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            printf("a[%d] == %d , a[%d]== %d \n", i, a[i], j + 1, a[j + 1]);
            if (a[j] >= a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;

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

typedef struct
{
    int h, m, s;
    /* data */
} Time;

void add_one_second(Time *t)
{

    if (t->s + 1 >= 60)
    {
        t->s = 0;
        t->m += 1;
        if (t->m == 60)
        {
            t->m = 0;
            t->h += 1;
            if (t->h == 24)
            {
                t->h = 0;
                /* code */
            }

            /* code */
        }

        /* code */
    }
    else
    {
        t->s += 1;
    }
}

size_t my_strlen(const char *s)
{
    int len = 0, i = 0;
    while (*(s + i) != '\0')
    {
        len++;
        i++;
        /* code */
    }

    return len;
}

void reverse_char(char *p, int len)
{
    for (size_t i = 0; i < len / 2; i++)
    {
        char tmp = p[i];
        p[i] = p[len - 1 - i];
        p[len - 1 - i] = tmp;
    }
}

int main(void)
{
    char name[220];
    char test[] = "abcsakjflajfl";

    strcpy(name, "alice");
    strcat(name, "!!");

    printf("%s", name);

    // int len = my_strlen(test);

    // reverse_char(test, len);

    // printf("%s\n",test);

    // Time now = {5, 12, 59};
    // Time now1 = {4, 59, 59};
    // Time now2 = {23, 59, 59};

    // add_one_second(&now);
    // add_one_second(&now1);
    // add_one_second(&now2);

    // printf("%d %d %d \n", now.h, now.m, now.s);
    // printf("%d %d %d \n", now1.h, now1.m, now1.s);
    // printf("%d %d %d \n", now2.h, now2.m, now2.s);

    // printf("%zu\n", my_strlen("abc"));   // 期望 3
    // printf("%zu\n", my_strlen(""));      // 期望 0（空串）
    // printf("%zu\n", my_strlen("hello")); // 期望 5

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

    // int a[] = {3, 2, 7, 6, 4};

    // bubble(a, 5);

    // int a[5] = {10, 20, 30, 40, 50};
    // int sum = 0;

    // int result = total(a, sum);

    // printf("%d", result);

    return 0;
}
