#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct msgBuff
{
    long msgtype;
    int data[100];
} message;

int main()
{
    key_t key = 1234;
    int msgQ_id;
    int flag = IPC_CREAT | 0666;
    if (msgQ_id = msgget(key, flag) < 0)
    {
        perror("Error while crating queue");
        exit(1);
    }

    msgrcv(msgQ_id, &message, sizeof(message), 1, 0);
    int n = message.data[0];
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (message.data[j] < message.data[i])
            {
                int temp = message.data[i];
                message.data[i] = message.data[j];
                message.data[j] = temp;
            }
        }
    }
    message.msgtype = 2;
    msgsnd(msgQ_id, &message, sizeof(message), 0);
    printf("Sorted array sent \n");

    return 0;
}