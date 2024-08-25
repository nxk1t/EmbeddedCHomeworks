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

    id = msgget(key, (IPC_CREAT | 0666));
    if (id == -1)
    {
        printf("id error\n");
        exit(EXIT_FAILURE);
    }

    struct msgbuf bufferSend, bufferReceive;
    strcpy(bufferSend.mtext, "Hi!");
    bufferSend.mtype = 10;

    sleep(2);

    if (msgsnd(id, &bufferSend, strlen(bufferSend.mtext), 0) == -1)
    {
        printf("msgsnd server error\n");
        exit(EXIT_FAILURE);
    }

    msgrcv(id, &bufferReceive, BUF_SIZE, 0, 0);

    printf("Received message: %s\n", bufferReceive.mtext);

    if (msgctl(id, IPC_RMID, 0) == -1)
    {
        printf("msgctl server error\n");
        exit(EXIT_FAILURE);
    }
    
    
    exit(EXIT_SUCCESS);
}