#include <stdio.h>

int main(void)
{
    int arr[40];

    for (int i = 0; i < 40; i++)
    {
        scanf("%d", &arr[i]);
        /* code */
    }

    int Mean = 0;

    for (int j = 0; j < 40; j++)
    {
        Mean += arr[j];
        /* code */
    }
    Mean = Mean / 40;

    for (int i = 0; i < 40 - 1; i++)
        for (int j = 0; j < 40 - 1 - i; j++)
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }

    int Median = (arr[19] + arr[20]) / 2;

    int count[11] = {0};
    for (int i = 0; i < 40; i++)
    {
        count[arr[i]]++;
        /* code */
    }

    int max_index = 0;
    int max = 0;
    for (int i = 1; i < 11; i++)
    {
        if (count[i] >= max)
        {
            max = count[i];
            max_index = i;

            /* code */
        }
        /* code */
    }

    printf("Mean value=%d\nMedian value=%d\nMode value=%d\n", Mean, Median, max_index);

    return 0;
}
