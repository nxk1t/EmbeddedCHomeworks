#include "server.h"

#define QUEUE_RD_SERVER "/queuerds11"
#define QUEUE_WR_SERVER "/queuewrs11"

char chatBuffer[100];
char userBuffer[50];
int userCounter = 1, chatCounter = 1;
mqd_t mqdReadServer, mqdWriteServer;
int temp;

int main()
{
    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = 150;
    pthread_t thread;
    int status;

    mqdReadServer = mq_open(QUEUE_RD_SERVER, O_RDWR | O_CREAT, 0666, &attr);
    mqdWriteServer = mq_open(QUEUE_WR_SERVER, O_RDWR | O_CREAT, 0666, &attr);
    if(mqdReadServer == -1 || mqdWriteServer == -1)
    {
        printf("mq open server error\n");
        exit(EXIT_FAILURE);
    }

    initGraph();

    pthread_create(&thread, NULL, threadChat, NULL);

    if(mq_send(mqdWriteServer, "1 Test", 100, 10) == -1) printf("F");
    if(mq_send(mqdReadServer, "1 Start chat", 100, 10) == -1) printf("F");

    while(temp != 113)
    {
        temp = getch();
        if(temp == 99) refreshWindow();
    }

    refreshWindow();
    mq_send(mqdReadServer, "2 exit server", 100, 10);
    pthread_join(thread, (void *)&status);
    sleep(1);

    endGraph();

    if(mq_close(mqdReadServer) == -1 || mq_close(mqdWriteServer) == -1)
    {
        printf("mq close server error\n");
        exit(EXIT_FAILURE);
    }

    if(mq_unlink(QUEUE_RD_SERVER) == -1 || mq_unlink(QUEUE_WR_SERVER) == -1)
    {
        printf("mq unlink server error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}