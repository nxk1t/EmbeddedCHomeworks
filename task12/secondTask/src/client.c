#include "fifo.h"

int main()
{
    int fdFifoRead;
    const char filename[FILENAME_SIZE] = "hi.fifo";
    char buffer[BUFFER_SIZE];

    fdFifoRead = open(filename, O_RDONLY);

    if (fdFifoRead == -1)
    {
        perror("fifo open read error");
        exit(EXIT_FAILURE);
    }
    else
    {
        read(fdFifoRead, buffer, sizeof(buffer));
        printf("Recieved message: %s\n", buffer);
    }

    close(fdFifoRead);

    exit(EXIT_SUCCESS);
}