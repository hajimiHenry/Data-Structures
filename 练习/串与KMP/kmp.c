#include <stdio.h>
#include <string.h>

int BruteForce(char S[], char T[])
{
    int SLen = strlen(S);
    int Tlen = strlen(T);
    int j = 0; // i对应S 主串 ；j对应T 模式串
    for (int start = 0; start <= SLen - Tlen; start++)
    {
        int i = start;
        j = 0;
        while (S[i] == T[j]) // 如果没有配上直接跳出循环while进入下一轮循环
        {
            i++;
            j++;
            if (T[j] == '\0') // 如果能走到最后，说明前面都配上了
            {
                return start + 1; // 模式串的首字母在主串的位置（按照第一位是是正常的来算
                /* code */
            }
        }
    }
    return 0; // 匹配失败了
}

int KMP(char S[], char T[], int *next)
{
    int SLen = strlen(S);
    int TLen = strlen(T);
    int i = 0;
    int j = 0;
    while (i < SLen && j < TLen) // 错i <= SLen - Tlen
    {
        if (j == -1 || S[i] == T[j])
        {
            i++;
            j++;
            /* code */
        }
        else
        {
            j = next[j];
        }

        /* code */
    }
    if (T[j] == '\0')
    {
        return i - TLen + 1;
        /* code */
    }

    return 0; // 匹配失败了
}

void GetNext(char *p, int *next, int m)
{
    next[0] = 0;
    int j = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && p[i] != p[j])
        {
            j = next[j - 1];
            /* code */
        }

        if (p[i] == p[j])
        {
            j++;
            /* code */
        }
        next[i] = j;
        /* code */
    }
}