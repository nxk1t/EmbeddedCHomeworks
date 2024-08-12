#include "main.h"

void* printThreadIndex(void* data)
{
    int* index = (int*) data;
    printf("%d\n", *index);
    pthread_exit(0);
}
