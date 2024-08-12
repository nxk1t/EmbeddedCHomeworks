#include "main.h"

extern int sum;

void* incrementSum(void* data)
{
    for (int i = 0; i < (TOTAL / SIZE_THREAD); i++)
    {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}