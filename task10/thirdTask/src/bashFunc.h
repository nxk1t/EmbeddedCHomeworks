#ifndef __BASHFUN_H__
#define __BASHFUN_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 256

void initCommandString(char*, char**, char*);
void deleteCommandString(char*, char**);
void splitCommandString(char*, char**);
void enterCommandString(char*);
int get_command(char * str);
void clearCommandString(char*, char**);

#endif