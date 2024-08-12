#include "main.h"

int sum = 0;

int main()
{
    pthread_t threads[SIZE_THREAD];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < SIZE_THREAD; i++)
    {
        pthread_create(&threads[i], NULL, &incrementSum, NULL);
    }

    for (int i = 0; i < SIZE_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Sum = %d\n", sum);

    exit(EXIT_SUCCESS);
}