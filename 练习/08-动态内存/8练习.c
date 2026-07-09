#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL)
    {
        printf("memory not enough");
        exit(1);
        /* code */
    }
    *p = 42;
    free(p);
    p = NULL;

    int n;

    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int)); // 申请 n 个 int，运行时才知道 n
    if (a == NULL)
        exit(1);

    printf("%p", a);

    for (int i = 0; i < n; i++)
        a[i] = i; // 当数组用，a[i] 完全合法
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);

    free(a);
    a = NULL;

    // 动态数组：读 n，申请 n 个 int，读入，输出最大值，释放。
    int x;
    scanf("%d", &x);

    int *q = (int *)malloc(x * sizeof(int));
    if (q == NULL)
    {
        exit(1);
        /* code */
    }

    for (size_t i = 0; i < x; i++)
    {
        scanf("%d", &q[i]);
    }

    int max = q[0];

    for (size_t i = 0; i < x; i++)
    {
        if (q[i] >= max)
        {
            max = q[i];
            /* code */
        }
    }

    printf("%d\n", max);

    free(q);
    q = NULL;

    return 0;
}

int dynamic_array(int n)
{
    int *p = (int *)calloc(n, sizeof(int));
    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
        /* code */
    }

    int max = p[0];

    for (size_t i = 0; i < n; i++)
    {
        if (p[i] >= max)
        {
            max = p[i];
            /* code */
        }
        /* code */
    }
    return max;
}