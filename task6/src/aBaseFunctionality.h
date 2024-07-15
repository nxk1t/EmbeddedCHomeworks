#ifndef __ABASEFUNCTIONALITY_H__
#define __ABASEFUNCTIONALITY_H__

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
#include <malloc.h>

#define STRUCT_SIZE 100

struct abonent {
    char name[20];
    char second_name[20];
    char tel[20];
};

void initAbonent(struct abonent**);
int addAbonent(struct abonent**, int*);
void printAbonents(struct abonent*, int);
void dataBaseRebuild(struct abonent**, int, int);
void deleteAbonent(struct abonent**, int*);
int searchAbonent(struct abonent*, int);

#endif