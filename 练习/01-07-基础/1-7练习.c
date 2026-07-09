#include <stdio.h>
#include <string.h>

/* ===== 类型定义 ===== */
typedef struct
{
    int h, m, s;
} Time;

/* ===== 函数声明 ===== */
void   swap(int *a, int *b);
void   double_it(int *p);
void   set_null(int **pp);
int    total(int *p, int sum);
void   reverse(int *a, int n);
void   bubble(int a[], int n);
void   add_one_second(Time *t);
size_t my_strlen(const char *s);
void   reverse_char(char *p, int len);

/* ===== 03 函数 ===== */
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

/* ===== 04 数组 ===== */
int total(int *p, int sum)
{
    for (int i = 0; i < 5; i++, p++)
        sum += *p;
    return sum;
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
        printf("%d\n", a[i]);
}

void bubble(int a[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] >= a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);
}

/* ===== 06 结构体 ===== */
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
                t->h = 0;
        }
    }
    else
    {
        t->s += 1;
    }
}

/* ===== 07 字符串 ===== */
size_t my_strlen(const char *s)
{
    int len = 0, i = 0;
    while (*(s + i) != '\0')
    {
        len++;
        i++;
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

/* ===== main：每个函数留一行活演示 ===== */
int main(void)
{
    /* 03 函数 */
    int x = 5, y = 9;
    swap(&x, &y);
    printf("swap: %d %d\n", x, y);               /* 9 5 */

    int z = 7;
    double_it(&z);
    printf("double_it: %d\n", z);                /* 14 */

    int v = 10;
    int *ptr = &v;
    set_null(&ptr);
    printf("set_null: %p\n", ptr);               /* (nil) */

    /* 04 数组 */
    int ta[5] = {10, 20, 30, 40, 50};
    printf("total: %d\n", total(ta, 0));         /* 150 */

    int ra[5] = {1, 2, 3, 4, 5};
    printf("reverse:\n");
    reverse(ra, 5);                              /* 5 4 3 2 1 */

    int ba[5] = {3, 2, 7, 6, 4};
    printf("bubble:\n");
    bubble(ba, 5);                               /* 2 3 4 6 7 */

    /* 06 结构体 */
    Time t = {23, 59, 59};
    add_one_second(&t);
    printf("time: %d:%d:%d\n", t.h, t.m, t.s);   /* 0:0:0 */

    /* 07 字符串 */
    printf("my_strlen: %zu\n", my_strlen("hello")); /* 5 */

    char str[] = "abc";
    reverse_char(str, my_strlen(str));
    printf("reverse_char: %s\n", str);           /* cba */

    char name[20];
    strcpy(name, "Alice");
    strcat(name, "!!");
    printf("strcpy+strcat: %s\n", name);         /* Alice!! */

    return 0;
}
