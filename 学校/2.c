#include <stdio.h>
struct fushu
{
    float shibu;
    float xubu;
};
/* 你的程序将放在这里 */

int main()
{
    struct fushu a, b, c, d;
    scanf("%f%fi", &a.shibu, &a.xubu); // 输入第一个复数
    scanf("%f%fi", &b.shibu, &b.xubu); // 输入第二个复数
    add(a, b);                         // 计算a=a+b
    mul(a, b);                         // 计算a=a*b
    scanf("%f%fi", &c.shibu, &c.xubu); // 输入第三个复数
    sub(a, c);                         // 计算a=a-c
    if (a.xubu > 0)
        printf("%.2f+%.2fi\n", a.shibu, a.xubu);
    else if (a.xubu < 0)
        printf("%.2f%.2fi\n", a.shibu, a.xubu);
    else
        printf("%.2f\n", a.shibu);
    return 0;
}