#include "chat.h"

sem_t *semid1, *semid2, *semid3, *semid4;
char *serverPointer, *clientPointer;
int temp = 0;
int exits = 0;
char messageBuffer[100];

extern WINDOW *messageWindow;

int main()
{
    int fd1, fd2, textCounter = 0;
    pthread_t thread;
    int status;

    char name[50];
    printf("Введите ваше имя для присоединения к чату (Макс 50 сим): ");
    fgets(name, 50, stdin);

    semid1 = sem_open(NAME_SEM1, O_CREAT);
    semid2 = sem_open(NAME_SEM2, O_CREAT);
    semid3 = sem_open(NAME_SEM3, O_CREAT);
    semid4 = sem_open(NAME_SEM4, O_CREAT);

    fd1 = shm_open(NAME_SH1, O_RDWR, 0666);
    fd2 = shm_open(NAME_SH2, O_RDWR, 0666);
    if (fd1 == -1 || fd2 == -1)
    {
        printf("shm open client error\n");
        exit(EXIT_FAILURE);
    }

    clientPointer = (char *)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    serverPointer = (char *)mmap(NULL, SIZE_SH, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    initGraph();

    sem_post(semid2);
    sem_wait(semid1);
    strcat(serverPointer, "CC: connected ");
    strcat(serverPointer, name);

    pthread_create(&thread, NULL, threadChat, NULL);

    while (exits != 1)
    {
        temp = getch();

        switch(temp)
        {
            case 10:
                if (messageBuffer[0] == '/')
                {
                    if (messageBuffer[1] == 'q')
                        exits = 1;
                }
                else
                {
                    sem_post(semid2);
                    sem_wait(semid1);
                    strcat(serverPointer, name);
                    serverPointer[strlen(serverPointer) - 1] = '\000';
                    strcat(serverPointer, ": ");
                    strcat(serverPointer, messageBuffer);
                    messageBuffer[0] = '\000';
                    textCounter = 0;
                }
                break;
            case 127:
                if (textCounter > 0)
                {
                    textCounter -= 1;
                    messageBuffer[textCounter] = '\000';
                }
                else
                {
                    messageBuffer[0] = '\000';
                    textCounter = 0;
                }
                break;
            default:
                if (temp > 39 && temp < 127 && temp != 91)
                {
                    messageBuffer[textCounter] = temp;
                    textCounter++;
                    messageBuffer[textCounter] = '\000';
                    wrefresh(messageWindow);
                }
        }
        refreshMessage();
    }

    sem_post(semid2);
    sem_wait(semid1);

    strcat(serverPointer, "CC: Disconnected ");
    strcat(serverPointer, name);

    pthread_join(thread, (void *)&status);
    endGraph();
    close(fd1);
    close(fd2);

    if (sem_close(semid1) == -1 || sem_close(semid2) == -1 || sem_close(semid3) == -1)
    {
        printf("sem close client error\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}