#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include <dirent.h>
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h>

void *threadChat(void *args);
void initGraph();
void refreshWindow();
void endGraph();
void deleteWindows();
void refreshMessage();

#endif