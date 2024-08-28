#ifndef __CHAT_H__
#define __CHAT_H__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>          
#include <sys/stat.h>     
#include <unistd.h> 
#include <pthread.h>     
#include <semaphore.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <curses.h> 
#include <dirent.h>
#include <limits.h>  
#include <sys/wait.h>

#define SIZE_SH 1500
#define NAME_SH1 "/SHARED_SERVER123"
#define NAME_SH2 "/SHARED_CLIENT456"
#define NAME_SEM1 "/SEM1111"
#define NAME_SEM2 "/SEM2222"
#define NAME_SEM3 "/SEM3333"
#define NAME_SEM4 "/SEM4444"

void *threadChat(void *args);
void initGraph();
void refreshWindow(); 
void endGraph();
void deleteWindows();
void refreshMessage();

#endif 