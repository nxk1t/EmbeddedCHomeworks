#ifndef __SHOP_H__
#define __SHOP_H__

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SHOP_SIZE 5
#define CLIENT_SIZE 3
#define SHOP_BALANCE 10000
#define CLIENT_BALANCE 100000

void* shopVisit(void*);
void* loadShop(void*);

#endif