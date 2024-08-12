#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE_THREADS 5

void* printThreadIndex(void*);

#endif