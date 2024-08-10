#include "bashFunc.h"

int main()
{
    pid_t childProcess;
    int status;
    char* command;
    char** splitCommand;
    char commandPath[STRSIZE];

    system("clear");

    command = (char*)malloc(STRSIZE * sizeof(char));
    
    splitCommand = (char**)malloc(STRSIZE * sizeof(char*));
    for (int i = 0; i < STRSIZE; i++)
        splitCommand[i] = (char*)malloc(STRSIZE * sizeof(char));

    while (1)
    {
        strcpy(commandPath, "/bin/");

        printf("input: ");
        enterCommandString(command);

        splitCommandString(command, splitCommand);
        strcat(commandPath, splitCommand[0]);

        if (splitCommand == NULL)
        {
            perror("Ошибка выделения памяти для splitCommand");
            exit(EXIT_FAILURE);
        }


        if (strcmp(command, "exit") == 0)
            break;
        else
        {
            childProcess = fork();

            if (childProcess == 0)
            {
                execv(commandPath, splitCommand);
                
                exit(10);
            }
            else if (childProcess < 0)
            {
                perror("Произошла ошибка при вызове fork()");
                exit(EXIT_FAILURE);
            }
            else
            {
                wait(&status);
            }
            clearCommandString(command, splitCommand);
        }

    }

    free(command);
    free(splitCommand);

    exit(EXIT_SUCCESS);
}