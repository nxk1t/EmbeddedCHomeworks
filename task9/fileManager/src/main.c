#include "filemanager.h" 

char *leftPath, *rightPath;  //  Пути к текущим каталогам для левой и правой панели
                        //  программы соответственно

struct dirent **rightNameList; //  Список файлов в текущей директории для правой
                            //  панели программы

struct dirent **leftNameList; //  Список файлов в текущей директории для левой
                            //  панели программы
int rightSize, leftSize;   //  Количество записей в текущих директориях для правой и левой
                //  панелей программы соответственно

int totalPos = 3; //  Ключ для определения текущей панели (значение по-умолчанию
                //  3 соотвествует левому окну, 2 - соответствует правому
                //  окну) и положению курсора

int main()
{
    int commandKey;    //  Переменная, которая хранит введенные с клавиатуры
                    //  клавиши
    
    getCurrentPath(&rightPath);
    getCurrentPath(&leftPath);
    rightSize = scandir(rightPath, &rightNameList, 0, alphasort);
    leftSize = scandir(leftPath, &leftNameList, 0, alphasort);
    
    initGraph();

    //  Основной цикл программы, работает до ввода с клавиатуры q или й
    while(commandKey != 113 && commandKey != 185)
    {
        commandKey = getch();
        
        switch (commandKey)
        {
            case 65:    //  Стрелка вверх (переход к предыдущему файлу)
                if(totalPos > 3)
                    totalPos -= 2;
                break;
            case 66:    //  Стрелка вниз (переход к следующему файлу)
                if(totalPos % 2 == 1)
                {
                    if(totalPos / 2 < (leftSize -1)) totalPos += 2;
                }
                else
                    if(totalPos / 2 < rightSize - 1) totalPos += 2;
                break;
            case 9:     //  TAB (смена панели)
                if(totalPos % 2 == 1) totalPos = 2;
                else totalPos = 3;
                break;
            case 10:    //  Enter (переход в выбранный каталог)
                if(totalPos % 2 == 1)
                {
                    if(leftNameList[totalPos / 2]->d_type == 4)
                    {
                        dirHierarchy(&leftPath, leftNameList[totalPos / 2]->d_name);
                        direntDelete(leftSize, leftNameList);
                        leftSize = scandir(leftPath, &leftNameList, 0, alphasort);
                        totalPos = 3;
                    }
                }
                else
                {
                    if(rightNameList[totalPos / 2]->d_type == 4)
                    {
                        dirHierarchy(&rightPath, rightNameList[totalPos / 2]->d_name);
                        direntDelete(rightSize, rightNameList);
                        rightSize = scandir(rightPath, &rightNameList, 0, alphasort);
                        totalPos = 2;
                    }
                }  
                break;
        }

        refResWin();  
    }

    direntDelete(rightSize, rightNameList);
    direntDelete(leftSize, leftNameList);
    free(rightPath);
    free(leftPath); 
    closeGraph();
    
    return 0;
}