#include "main.h"

int main()
{
    pid_t childProccess;
    int status;

    childProccess = fork();

    if (childProccess == 0)
    {
      printf("Child PID: %d, Child PPID: %d\n", getpid(), getppid());
      exit(5);
    }
    else
    {
      printf("Parent PID: %d, Parent PPID: %d\n", getpid(), getppid());
      wait(&status);
      printf("Wait status: %d\n", WEXITSTATUS(status));
    }

    exit(EXIT_SUCCESS);
}