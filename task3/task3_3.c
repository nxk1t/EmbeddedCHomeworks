#include <stdio.h>

#define N 10

int main()
{
    int arr[N];
    int *ptr = arr;
    for (int i = 0; i < N; i++)
    {
        *ptr = i + 1;
        ptr++;
    }

    ptr = arr;
    printf("Array: ");
    for (int i = 0; i < N; i++) printf("%d ", *(ptr + i));
    printf("\n");

    return 0;
}