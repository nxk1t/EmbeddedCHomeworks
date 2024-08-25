#include "queueMsg.h"

struct msgbuf
{
    long mtype;
    char mtext[BUF_SIZE];
};

int main()
{
    int id;
    key_t key;

    key = ftok("bin/server", 1);
    if (key == -1)
    {
        printf("key error\n");
        exit(EXIT_FAILURE);
    }

    id = msgget(key, 0);
    if (id == -1)
    {
        printf("id error\n");
        exit(EXIT_FAILURE);
    }

    struct msgbuf bufferSend, bufferReceive;
    strcpy(bufferSend.mtext, "Hello!");
    bufferSend.mtype = 10;

    msgrcv(id, &bufferReceive, BUF_SIZE, 0, 0);

    printf("Received message: %s\n", bufferReceive.mtext);

    if (msgsnd(id, &bufferSend, strlen(bufferSend.mtext), 0) == -1)
    {
        printf("msgsnd client error\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}