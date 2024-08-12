#include "main.h"

int main()
{
    int arr[SIZE_THREADS];
    pthread_t threads[SIZE_THREADS];

    for (int i = 0; i < SIZE_THREADS; i++)
    {
        arr[i] = i + 1;
        pthread_create(&threads[i], NULL, &printThreadIndex, &arr[i]);
    }


    for (int i = 0; i < SIZE_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    exit(EXIT_SUCCESS);
}