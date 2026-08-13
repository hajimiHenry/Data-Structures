#include <stdio.h>
#include <stdlib.h>

int factorial(int n);

int main(void)
{
    int n = 5;

    printf("%d\n", factorial(n));
}

int factorial(int n)
{
    if (n == 1)
        return 1;
    return n * factorial(n - 1);
}
