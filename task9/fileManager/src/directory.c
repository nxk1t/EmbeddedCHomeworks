#include "filemanager.h"

//  Получение пути к текущему / новому выбранному каталогу
int getCurrentPath(char** path)
{
    *path = malloc(PATH_MAX); 
    if(getcwd(*path, PATH_MAX))
    {
        *path = realloc(*path, strlen(*path));  
        return 0;
    }
    else return 1;
}

//  Очистка структуры dirent
int direntDelete(int n, struct dirent **nameList)
{
    while(n--)
    {
        free(nameList[n]);
    }
    
    free(nameList);

    return 0;
}