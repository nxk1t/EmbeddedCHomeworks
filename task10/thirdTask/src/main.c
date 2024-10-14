#include "bashFunc.h"

int main()
{
    pid_t childProcess;
    int status;
    char* command;
    char** splitCommand;
    char** splitCommandSecond;
    char commandPath[STRSIZE];
    int pipefd[2];

    system("clear");

    command = (char*)malloc(STRSIZE * sizeof(char));

    splitCommand = (char**)malloc(STRSIZE * sizeof(char*));
    splitCommandSecond = (char**)malloc(STRSIZE * sizeof(char*));
    for (int i = 0; i < STRSIZE; i++) {
        splitCommand[i] = (char*)malloc(STRSIZE * sizeof(char));
        splitCommandSecond[i] = (char*)malloc(STRSIZE * sizeof(char));
    }

    while (1)
    {
        strcpy(commandPath, "/bin/");

        printf("input: ");
        enterCommandString(command);

        if (splitCommand == NULL)
        {
            perror("Ошибка выделения памяти для splitCommand");
            exit(EXIT_FAILURE);
        }

        // Проверка на команду cd
        if (strncmp(command, "cd", 2) == 0)
        {
            splitCommandString(command, splitCommand);
            if (splitCommand[1] != NULL)
            {
                if (chdir(splitCommand[1]) != 0) {
                    perror("Ошибка при выполнении команды cd");
                }
            }
            else
            {
                fprintf(stderr, "Ошибка: не указан путь для cd\n");
            }
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            // Проверяем, есть ли в команде пайп
            char* pipePosition = strchr(command, '|');
            if (pipePosition != NULL)
            {
                // Разделяем команды по пайпу
                char* firstCommand = strtok(command, "|");
                char* secondCommand = strtok(NULL, "|");

                // Убираем лишние пробелы
                while (*secondCommand == ' ') secondCommand++;

                // Создаем пайп
                if (pipe(pipefd) == -1)
                {
                    perror("Ошибка создания пайпа");
                    exit(EXIT_FAILURE);
                }

                // Создаем дочерний процесс для первой команды
                if (fork() == 0)
                {
                    // Закрываем поток чтения
                    close(pipefd[0]);

                    // Перенаправляем стандартный вывод в пайп
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);

                    // Выполняем первую команду
                    splitCommandString(firstCommand, splitCommand);
                    strcpy(commandPath, "/bin/");
                    strcat(commandPath, splitCommand[0]);
                    execv(commandPath, splitCommand);
                    perror("Ошибка выполнения первой команды");
                    exit(EXIT_FAILURE);
                }

                // Создаем дочерний процесс для второй команды
                if (fork() == 0)
                {
                    // Закрываем поток записи
                    close(pipefd[1]);

                    // Перенаправляем стандартный ввод из пайпа
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);

                    // Выполняем вторую команду
                    splitCommandString(secondCommand, splitCommandSecond);
                    strcpy(commandPath, "/bin/");
                    strcat(commandPath, splitCommandSecond[0]);
                    execv(commandPath, splitCommandSecond);
                    perror("Ошибка выполнения второй команды");
                    exit(EXIT_FAILURE);
                }

                // Закрываем оба конца пайпа в родительском процессе
                close(pipefd[0]);
                close(pipefd[1]);

                // Ждем завершения обоих дочерних процессов
                wait(&status);
                wait(&status);
            }
            else
            {
                splitCommandString(command, splitCommand);
                childProcess = fork();

                if (childProcess == 0)
                {
                    strcat(commandPath, splitCommand[0]);
                    execv(commandPath, splitCommand);

                    perror("Ошибка выполнения команды");
                    exit(EXIT_FAILURE);
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
            }
        }

        clearCommandString(command, splitCommand);
        clearCommandString(command, splitCommandSecond);
    }

    free(command);
    free(splitCommand);
    free(splitCommandSecond);

    exit(EXIT_SUCCESS);
}
