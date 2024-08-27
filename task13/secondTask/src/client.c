#include "client.h"

#define QUEUE_RD_SERVER "/queuerds11"
#define QUEUE_WR_SERVER "/queuewrs11"

extern WINDOW *messageWindow;

char chatBuffer[100];
char messageBuffer[100];
char userBuffer[50];
char tempBuffer[100];
int userCounter = 0, chatCounter = 0;
mqd_t mqdReadServer, mqdWriteServer;
int exits = 0;

int main()
{
    int temp, textCounter = 0;
    char name[50];
    pthread_t thread;
    printf("Введите ваше имя для присоединения к чату (Макс 50 сим): ");
    fgets(name, 50, stdin);

    mqdReadServer = mq_open(QUEUE_RD_SERVER, O_RDWR);
    mqdWriteServer = mq_open(QUEUE_WR_SERVER, O_RDWR);
    if(mqdReadServer == -1 || mqdWriteServer == -1)
    {
        printf("mq open client error\n");
        exit(EXIT_FAILURE);
    }

    initGraph();

    strcat(messageBuffer, "3 connected ");
    strcat(messageBuffer, name);

    pthread_create(&thread, NULL, threadChat, NULL);

    if(mq_send(mqdReadServer, messageBuffer, 30, 10) == -1)
    {
        printf("mq send client error\n");
        exit(EXIT_FAILURE);
    }

    while(exits != 1)
    {
        temp = getch();

        switch(temp)
        {
            case 10:
                if(messageBuffer[0] == '/')
                {
                    if(messageBuffer[1] == 'q')
                        exits = 1;
                }
                else
                {
                    strcat(tempBuffer, "5 ");
                    strcat(tempBuffer, name);
                    tempBuffer[strlen(tempBuffer) - 1] = '\000';
                    strcat(tempBuffer, ": ");
                    strcat(tempBuffer, messageBuffer);

                    if(mq_send(mqdReadServer, tempBuffer, 30, 10) == -1)
                    {
                        printf("mq send c to s error\n");
                        exit(EXIT_FAILURE);
                    }

                    tempBuffer[0] = '\000';
                    messageBuffer[0] = '\000';
                    textCounter = 0;
                }
                break;
            case 127:
                if(textCounter > 0)
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
                if(temp > 39 && temp < 127 && temp != 91)
                {
                    messageBuffer[textCounter] = temp;
                    textCounter++;
                    messageBuffer[textCounter] = '\000';
                    wrefresh(messageWindow);
                }
        }
        refreshMessage();
    }

    messageBuffer[0] = '\000';
    strcat(messageBuffer, "4 Disconnected ");
    strcat(messageBuffer, name);

    if(mq_send(mqdReadServer, messageBuffer, 30, 10) == -1)
    {
        printf("mq send client error\n");
        exit(EXIT_FAILURE);
    }

    endGraph();
    printf("%d\n", temp);

    if(mq_close(mqdReadServer) == -1 || mq_close(mqdWriteServer) == -1)
    {
        printf("mq close client error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}