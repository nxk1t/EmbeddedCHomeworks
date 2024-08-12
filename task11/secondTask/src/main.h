#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE_THREAD 5
#define TOTAL 1000000

pthread_mutex_t mutex;

void* incrementSum(void*);

#endif