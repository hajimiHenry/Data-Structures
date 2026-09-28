#include <stdio.h>

// int main(void)
// {
//     int K;
//     scanf("%d", &K);

//     int arr[K];
//     for (int i = 0; i < K; i++)
//     {
//         scanf("%d", &arr[i]);
//     }

//     int max = arr[0];
//     for (int end = K; end > 0; end--)
//     {
//         for (int start = 0; start < end; start++)
//         {
//             int total = 0;
//             for (int j = start; j < end; j++)
//             {
//                 total += arr[j];
//             }
//             if (total >= max)
//             {
//                 max = total;
//             }
//         }
//     }
//     printf("%d\n", max);

//     return 0;
// }

int main(void)
{
    int k;
    scanf("%d", &k);

    int arr[k];
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &arr[i]);
    }

    int max = arr[0];
    int current = arr[0];
    for (int i = 1; i < k; i++)
    {
        if (current + arr[i] > arr[i])
        {
            current += arr[i];
        }
        else
        {
            current = arr[i];
        }

        if (current > max)
        {
            max = current;
        }
    }

    printf("%d", max);

    return 0;
}