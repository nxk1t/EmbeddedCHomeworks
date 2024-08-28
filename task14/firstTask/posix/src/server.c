#include "shMessage.h"

struct message
{
    char buffer[BUFFER_SIZE];
};

int main()
{
    int fd;
    struct message *shmPointer;
    sem_t *semid;

    fd = shm_open("/desc", (O_CREAT | O_RDWR), 0666);
    if (fd == -1)
    {
        printf("shm open server error\n");
        exit(EXIT_FAILURE);
    }

    if(ftruncate(fd, 256) == -1)
    {
        printf("ftruncate server error\n");
        exit(EXIT_FAILURE);
    }

    shmPointer = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    semid = sem_open("/sem", O_CREAT, 0666, 0);
    if (semid == SEM_FAILED)
    {
        printf("sem open server error\n");
        exit(EXIT_FAILURE);
    }
    sem_post(semid);
    strcpy(shmPointer->buffer, "Hi!");
    sem_wait(semid);

    sleep(10);

    sem_post(semid);
    printf("%s\n", shmPointer->buffer);

    if (sem_close(semid) == -1)
    {
        printf("sem close server error\n");
        exit(EXIT_FAILURE);
    }

    if (sem_unlink("/sem") == -1)
    {
        printf("sem unlink server error\n");
        exit(EXIT_FAILURE);
    }

    if (munmap(shmPointer, 256) == -1)
    {
        printf("munmap server error\n");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink("/desc") == -1)
    {
        printf("shm unlink server error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}