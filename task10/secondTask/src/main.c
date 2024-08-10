#include "main.h"

int main()
{
    pid_t parentProccess, childProccess;
    int status;

    parentProccess = fork();
    if (parentProccess == 0)
    {
        printf("Parent 1 PID: %d, PPID: %d\n", getpid(), getppid());

        childProccess = fork();
        if (childProccess == 0)
        {
            printf("1) Child 1 PID: %d, PPID: %d\n", getpid(), getppid());
            exit(13);
        }

        childProccess = fork();
        if (childProccess == 0)
        {
            printf("1) Child 2 PID: %d, PPID: %d\n", getpid(), getppid());
            exit(14);
        }
        
        wait(&status);
        printf("Wait status: %d\n", WEXITSTATUS(status) - 10);

        wait(&status);
        printf("Wait status: %d\n", WEXITSTATUS(status) - 10);

        exit(11);
    }
    else
    {
        printf("Progenitor PID: %d, PPID: %d\n", getpid(), getppid());

        childProccess = fork();
        if (childProccess == 0)
        {
            printf("Parent 2 PID: %d, PPID: %d\n", getpid(), getppid());

            childProccess = fork();
            if (childProccess == 0)
            {
                printf("2) Child 1 PID: %d, PPID: %d\n", getpid(), getppid());
                exit(15);
            }

            wait(&status);
            printf("Wait status: %d\n", WEXITSTATUS(status) - 10);

            exit(12);
        }
        else
        {
            wait(&status);
            printf("Wait status: %d\n", WEXITSTATUS(status) - 10);
        }

        wait(&status);
        printf("Wait status: %d\n", WEXITSTATUS(status) - 10);
    }

    exit(EXIT_SUCCESS);
}