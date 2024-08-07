#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

 
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>  
#include <string.h> 
#include <time.h>

extern WINDOW *stdscr;
extern char *rightPath, *leftPath;
extern struct dirent **rightNameList;
extern struct dirent **leftNameList;
extern int rightSize, leftSize, totalPos;

void fillWindow();
void refResWin();
void sigWinchHandler(int signo);
void initGraph();
int deleteWindows();
int closeGraph();
int getCurrentPath(char** path);
int direntDelete(int n, struct dirent **nameList);
int dirHierarchy(char** path, char *name);
#endif 