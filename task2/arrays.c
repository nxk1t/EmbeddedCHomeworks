#include <stdio.h>

#define N 5

void printMatrix(int arr[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void printArray(int arr[N])
{
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
}

void task1()
{
    int arr[N][N];

    int digit = 1;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = digit;
            digit++;
        }

    printf("Ascending fill of cube matrix: \n");
    printMatrix(arr);
    printf("\n\n");
}

void task2()
{
    int arr[N];

    for (int i = 0; i < N; i++) arr[i] = i + 1;

    printf("Direct sequence: ");
    printArray(arr);

    for (int i = 0; i < N/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[N - 1 - i];
        arr[N - 1 - i] = temp;
    }

    printf("\nReverse sequence: ");
    printArray(arr);
    printf("\n\n");
}

void task3()
{
    int arr[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (i + j >= N - 1) arr[i][j] = 1;
            else arr[i][j] = 0;
        }

    printf("Triangle fill of matrix:\n");
    printMatrix(arr);
    printf("\n\n");
}

void task4()
{
    int arr[N][N];

    int i1 = 0, i2 = 0;
    int j1 = 0, j2 = 0;
    
    int k = 1;
    int i = 0;
    int j = 0;

    while (k <= N * N)
    {
        arr[i][j] = k;
        if (i == i1 && j < N - j2 - 1)
            ++j;
        else if (j == N - j2 - 1 && i < N - i2 - 1)
            ++i;
        else if (i == N - i2 - 1 && j > j1)
            --j;
        else
            --i;

        if ((i == i1 + 1) && (j == j1) && (j1 != N - j2 - 1))
        {
            ++i1;
            ++i2;
            ++j1;
            ++j2;
        }
        ++k;
    }

    printf("Spiral fill of matrix:\n");
    printMatrix(arr);
    printf("\n");
}

int main()
{
    task1();
    task2();
    task3();
    task4();
    

    return 0;
}