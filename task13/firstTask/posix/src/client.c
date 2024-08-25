#include "queueMsgPosix.h"

int main()
{
    mqd_t mqd;
    char bufferSend[BUFFER_SIZE] = "Hello!";
    char bufferReceive[BUFFER_SIZE];
    unsigned int priority = 1;
    char fdPath[FDPATH_SIZE] = "/desc";

    mqd = mq_open(fdPath, O_RDWR);
    if (mqd == -1)
    {
        printf("mq open client error\n");
        exit(EXIT_FAILURE);
    }

    if (mq_receive(mqd, bufferReceive, BUFFER_SIZE, &priority) == -1)
    {
        printf("mq receive client error\n");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", bufferReceive);

    if (mq_send(mqd, bufferSend, strlen(bufferSend), 1) == -1)
    {
        printf("mq send client error\n");
        exit(EXIT_FAILURE);
    }

    if (mq_close(mqd) == -1)
    {
        printf("mq close client error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}