#include "fifo.h"

int main()
{
    const char filename[] = "hi.fifo";
    int fdFifoWrite;
    char buffer[BUFFER_SIZE];

    unlink(filename);

    if (mkfifo(filename, 0666))
    {
        perror("mkfifo error");
        exit(EXIT_FAILURE);
    }

    fdFifoWrite = open(filename, O_WRONLY);

    if (fdFifoWrite == -1)
    {
        perror("fifo open write error");
        exit(EXIT_FAILURE);
    }
    else
    {
        sprintf(buffer, "%s", "Hi!");
        write(fdFifoWrite, buffer, sizeof(buffer));
    }

    close(fdFifoWrite);

    exit(EXIT_SUCCESS);
}