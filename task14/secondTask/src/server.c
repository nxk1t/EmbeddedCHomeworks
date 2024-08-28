#include "chat.h"

char *serverPointer, *clientPointer;
sem_t *semid1, *semid2, *semid3, *semid4;
int temp = 0;

int main()
{
    int fd1, fd2;
    pthread_t thread;
    int status;

    semid1 = sem_open(NAME_SEM1, O_CREAT, 0666, 0);
    semid2 = sem_open(NAME_SEM2, O_CREAT, 0666, 0);
    semid3 = sem_open(NAME_SEM3, O_CREAT, 0666, 0);
    semid4 = sem_open(NAME_SEM4, O_CREAT, 0666, 0);
    
    fd1 = shm_open(NAME_SH1, O_RDWR | O_CREAT, 0666);
    fd2 = shm_open(NAME_SH2, O_RDWR | O_CREAT, 0666);
    if (fd1 == -1 || fd2 == -1)
    {
        printf("shm open server error");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd1, SIZE_SH) == -1 || ftruncate(fd2, SIZE_SH) == -1)
    {
        printf("ftrancate server error");
        exit(EXIT_FAILURE);
    }

    clientPointer = (char *)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    serverPointer = (char *)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    initGraph();

    sem_post(semid2);
    pthread_create(&thread, NULL, threadChat, NULL);
    
    strcat(serverPointer, "server: START CHAT\n");
    
    while (temp != 113)
    {
        temp = getch();
        if(temp == 99)
            refreshWindow();
    }

    serverPointer[0] = '\000';
    sem_post(semid2);
    strcat(serverPointer, "server: END CHAT\n");
    
    refreshWindow();
    
    for (int i = 0; i < 10; i++)
    {
        sem_post(semid1);
        sem_post(semid2);
        sem_post(semid3);
        sem_post(semid4);
    }

    pthread_join(thread, (void *)&status);
    sleep(2);

    endGraph();
    close(fd1);
    close(fd2);
    
    if (munmap(serverPointer, SIZE_SH))
    {
        printf("munmap server error");
        exit(EXIT_FAILURE);
    }

    if (munmap(clientPointer, SIZE_SH))
    {
        printf("munmap server error");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink(NAME_SH1) == -1 || shm_unlink(NAME_SH2) == -1)
    {
        printf("shm unlink server error");
        exit(EXIT_FAILURE);
    }

    if (sem_close(semid1) == -1 || sem_close(semid2) == -1 || sem_close(semid3) == -1 || sem_close(semid4) == -1)
    {
        printf("sem close server error");
        exit(EXIT_FAILURE);
    }

    if (sem_unlink(NAME_SEM1) == -1 || sem_unlink(NAME_SEM2) == -1 || sem_unlink(NAME_SEM3) == -1 || sem_unlink(NAME_SEM4) == -1)
    {
        printf("sem unlink server error");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}