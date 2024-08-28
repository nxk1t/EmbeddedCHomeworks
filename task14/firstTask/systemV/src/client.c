#include "shMessage.h"

struct message
{
    char buffer[BUFFER_SIZE];
};

int main()
{
    key_t keySHM, keySemaphore;
    int idSHM, idSemaphore;
    struct message *shmPointer;
    struct sembuf semaphoreOperation[2] = {{0, 1, 0}, {0, -1, 0}};

    keySHM = ftok("bin/server", 1);
    if (keySHM == -1)
    {
        printf("ftok shm server error\n");
        exit(EXIT_FAILURE);
    }

    idSHM = shmget(keySHM, 256, 0);
    if (idSHM == -1)
    {
        printf("shmget server error\n");
        exit(EXIT_FAILURE);
    }

    keySemaphore = ftok("bin/server", 2);
    if (keySemaphore == -1)
    {
        printf("ftok semaphore server error\n");
        exit(EXIT_FAILURE);
    }

    idSemaphore = semget(keySemaphore, 1, 0);
    if (idSemaphore == -1)
    {
        printf("semget server error\n");
        exit(EXIT_FAILURE);
    }

    shmPointer = shmat(idSHM, NULL, 0666);

    semop(idSemaphore, semaphoreOperation, 1);
    printf("%s\n", shmPointer->buffer);
    strcpy(shmPointer->buffer, "Hello!");
    semop(idSemaphore, semaphoreOperation, 2);

    shmdt(shmPointer);
    
    exit(EXIT_SUCCESS);
}