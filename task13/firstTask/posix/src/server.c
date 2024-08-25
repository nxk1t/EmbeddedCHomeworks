#include "queueMsgPosix.h"

int main()
{
    mqd_t mqd;
    char bufferSend[BUFFER_SIZE] = "Hi!";
    char bufferReceive[BUFFER_SIZE];
    unsigned int priority = 1;
    char fdPath[FDPATH_SIZE] = "/desc";

    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = 50;
    attr.mq_curmsgs = 1;

    mqd = mq_open(fdPath, (O_CREAT | O_RDWR), 0666, &attr);
    if (mqd == -1)
    {
        printf("mq open server error\n");
        exit(EXIT_FAILURE);
    }

    if (mq_send(mqd, bufferSend, strlen(bufferSend), 1) == -1)
    {
        printf("mq send server error\n");
        exit(EXIT_FAILURE);
    }

    sleep(3);

    if (mq_receive(mqd, bufferReceive, BUFFER_SIZE, &priority) == -1)
    {
        printf("mq receive server error\n");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", bufferReceive);

    if (mq_close(mqd) == -1)
    {
        printf("mq close server error\n");
        exit(EXIT_FAILURE);
    }

    if(mq_unlink(fdPath) == -1)
    {
        printf("mq unlink error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}