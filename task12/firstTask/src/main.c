#include "main.h"

int main()
{
    int mainPipe[2];
    pid_t childProcess;
    int status;
    char buffer[BUF_SIZE];

    if (pipe(mainPipe))
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }
    
    childProcess = fork();
    if (childProcess == 0)
    {
        close(mainPipe[1]);
        read(mainPipe[0], buffer, sizeof(buffer));
        printf("Recieved message: %s\n", buffer);
        exit(5);
    }
    else if (childProcess < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(mainPipe[0]);
        sprintf(buffer, "%s", "Hi!");
        write(mainPipe[1], buffer, sizeof(buffer));
        wait(&status);
    }

    exit(EXIT_SUCCESS);
}