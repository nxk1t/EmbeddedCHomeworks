#include "filemanager.h"
#define BOTTOM_SIZE 3
#define ATTR_MODE A_BLINK | A_REVERSE


WINDOW *mainWindow;   //  Главное окно программы
 
WINDOW *rightNameWindow;   //  Окно, содержащее имена файлов и каталогов в текущей 
                    //  директории для правой панели программы

WINDOW *rightSizeWindow;   //  Окно, содержащее размеры файлов и каталогов в текущей
                    //  директории для правой панели программы

WINDOW *rightDateWindow;   //  Окно, содержащее дату последних изменений файлов и
                    //  каталогов в текущей директории для правой панели
                    //  программы
 
WINDOW *leftNameWindow;   //  Окно, содержащее имена файлов и каталогов в текущей 
                    //  директории для левой панели программы

WINDOW *leftSizeWindow;   //  Окно, содержащее размеры файлов и каталогов в текущей
                    //  директории для левой панели программы

WINDOW *leftDateWindow;   //  Окно, содержащее дату последних изменений файлов и
                    //  каталогов в текущей директории для правой панели
                    //  программы

WINDOW *bottomWindow; //  Окно, содержащее текущие пути для каждой панели про-
                    //  граммы

struct winsize windowSize;  //  Структура, позволяющая получить данные о размерах
                    //  терминального окна

//  Отрисовка содержимого окон
void fillWindow()
{
    int tempLength;
    struct stat *fileInfo;   //  Структура, содержащая информацию о файлах
    char *tempPath;

    //  Вычисление и отрисовка текущего пути для левой панели программы
    tempLength = strlen(leftPath);
    wmove(bottomWindow, 1, 1); 
    if((windowSize.ws_col/2) < tempLength)
        wprintw(bottomWindow, "/...%s         ", &(leftPath[tempLength - ((windowSize.ws_col/3)-5)]));
    else    
        wprintw(bottomWindow, "%s  ", leftPath);
    
    //  Вычисление и отрисовка текущего пути для правой панели программы
    wmove(bottomWindow, 1, (windowSize.ws_col/2)+1);
    tempLength = strlen(rightPath);
    if((windowSize.ws_col/2) < tempLength)
        wprintw(bottomWindow, "/...%s         ", &(rightPath[tempLength - ((windowSize.ws_col/3)-5)]));
    else    
        wprintw(bottomWindow, " %s ", rightPath); 

    //  Конкатенация пути для правой панели программы
    tempPath = malloc(PATH_MAX);
    strcat(tempPath, rightPath);
    strcat(tempPath, "/"); 

    //  Отрисовка содержимого текущего каталога для правой панели программы
    for(int i = 1; i < rightSize; i++)
    {
        if((totalPos % 2 == 0) && (totalPos / 2 == i))
            wattron(rightNameWindow, COLOR_PAIR(2));
        
        wmove(rightNameWindow, i, 1);
        wmove(rightDateWindow, i, 1); 
        wmove(rightSizeWindow, i, 1); 
        
        if(rightNameList[i]->d_type == 4)
            wprintw(rightNameWindow, "/");
        wprintw(rightNameWindow, "%s", rightNameList[i]->d_name);

        if(i > 1)
        {
            fileInfo = malloc(sizeof(struct stat));
            tempPath[strlen(rightPath)+1] = '\000';
            strcat(tempPath, rightNameList[i]->d_name); 
            stat(tempPath, fileInfo);
            wprintw(rightSizeWindow, "%ld", fileInfo->st_size); 
            wprintw(rightDateWindow, "%s", &(ctime(&(fileInfo->st_mtime)))[4]);
            free(fileInfo); 
        }

        if(totalPos % 2 == 0 && (totalPos / 2 == i))
            wattroff(rightNameWindow, COLOR_PAIR(2));
    }

    free(tempPath);

//  Конкатенация пути для левой панели программы
    tempPath = malloc(PATH_MAX);
    tempPath[0] = '\000';
    strcat(tempPath, leftPath);
    strcat(tempPath, "/");

//  Отрисовка содержимого текущего каталога для левой панели программы
    for(int i = 1; i < leftSize; i++)
    {
        if((totalPos % 2 == 1) && (totalPos / 2 == i))
            wattron(leftNameWindow, COLOR_PAIR(2));
        
        wmove(leftDateWindow, i, 1);
        wmove(leftNameWindow, i, 1);
        wmove(leftSizeWindow, i, 1);
        
        if(leftNameList[i]->d_type == 4)
            wprintw(leftNameWindow, "/");
        wprintw(leftNameWindow, "%s", leftNameList[i]->d_name);
        
        if(i > 1)
        {
            fileInfo = malloc(sizeof(struct stat));
            tempPath[strlen(leftPath)+1] = '\000';
            strcat(tempPath, leftNameList[i]->d_name); 
            stat(tempPath, fileInfo);
            wprintw(leftSizeWindow, "%ld", fileInfo->st_size); 
            wprintw(leftDateWindow, "%s", &(ctime(&(fileInfo->st_mtime)))[4]);
            free(fileInfo); 
        } 
        
        if((totalPos % 2 == 1) && (totalPos / 2 == i))
            wattroff(leftNameWindow, COLOR_PAIR(2));
    }

    free(tempPath);
    
}

//  Отображение окон при обновлении информации в них (в том числе при изменении
//  размера терминального окна)
void refResWin()
{
    deleteWindows();

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize); 
    mainWindow = newwin(windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col, 0, 0); 
    wbkgd(mainWindow, COLOR_PAIR(1));

    rightNameWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col / 4, 0, (windowSize.ws_col / 2) + 1);
    rightSizeWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col / 8, 0, (windowSize.ws_col / 2) + 1 + windowSize.ws_col / 4);
    rightDateWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, (windowSize.ws_col / 8) - 1, 0, (windowSize.ws_col / 2) + 1 + windowSize.ws_col / 4 + windowSize.ws_col / 8);
     
    leftNameWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col / 4, 0, 0);
    leftSizeWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col / 8, 0, windowSize.ws_col / 4);
    leftDateWindow = derwin(mainWindow, windowSize.ws_row - BOTTOM_SIZE - 1, windowSize.ws_col / 8, 0, windowSize.ws_col / 4 + windowSize.ws_col / 8);

    bottomWindow = newwin(BOTTOM_SIZE, windowSize.ws_col - 1, windowSize.ws_row - BOTTOM_SIZE, 0);
    wbkgd(bottomWindow, COLOR_PAIR(2));

    fillWindow();

    move(windowSize.ws_row - 1 - BOTTOM_SIZE, 1);
    printw("Exit - q,    Swap window - TAB,    input: ");
 
    box(rightSizeWindow, 0, 0);
    box(rightNameWindow, 0, 0);
    box(rightDateWindow, 0, 0); 

    box(leftSizeWindow, 0, 0);
    box(leftNameWindow, 0, 0);
    box(leftDateWindow, 0, 0);

    box(bottomWindow, 0, 0);

    wrefresh(mainWindow); 
    wrefresh(bottomWindow); 
    refresh();   
}

//  Переход по иерархии каталогов
int dirHierarchy(char** path, char *name)
{
    if(totalPos / 2 == 1)
    {
        for(int i = strlen(*path); i != 0; i--)
        {
            if((*path)[i] == '/')
            {
                (*path)[i] = '\000';
                break;
            }
        }
        *path = realloc(*path, strlen(*path)); 
    }
    else
    {
        *path = realloc(*path, strlen(*path) + strlen(name)); 
        strcat(*path, "/");
        strcat(*path, name); 
    } 
    return 0;
}

//  Реализация для сигнала SIGWINCH (изменение размера терминального окна)
void sigWinchHandler(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);  
    refResWin(); 
}

//  Инициализация графики ncurses
void initGraph()
{
    initscr();
    signal(SIGWINCH, sigWinchHandler);
    cbreak();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    refresh();

    refResWin();
}

//  Удаление окон
int deleteWindows()
{
    delwin(mainWindow);
    delwin(bottomWindow); 
    delwin(rightNameWindow);
    delwin(rightDateWindow);
    delwin(rightSizeWindow);
    delwin(leftNameWindow);
    delwin(leftDateWindow);
    delwin(leftSizeWindow);

    return 0;
}

//  Завершение программы на графическом уровне
int closeGraph()
{
    deleteWindows();
    return endwin();
}