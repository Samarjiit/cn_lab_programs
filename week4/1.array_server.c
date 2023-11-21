
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 128

// Declare the message structure
typedef struct msgbuf
{
    long mtype;
    int arr[20];
} message;

int main()
{
    int i, j, temp, num;
    int msqid;
    key_t key;
    message rbuf;
    size_t buf_length;
    int msgflg = IPC_CREAT | 0666;

    key = 1234;

    if ((msqid = msgget(key, 0666)) < 0)
    {
        printf("Message queue creation failed");
        exit(1);
    }
    printf("Server is running\n");
    if (msgrcv(msqid, &rbuf, SIZE, 1, 0) < 0)
    {
        printf("Message not received\n");
        exit(1);
    }
    // Print the answer.
    num = rbuf.arr[0];
    printf("\nElements received: ");
    for (i = 1; i <= num; i++)
        printf("%d  ", rbuf.arr[i]);
    for (i = 1; i <= num; i++)
        for (j = 1; j <= num - i; j++)
            if (rbuf.arr[j] > rbuf.arr[j + 1])
            {
                temp = rbuf.arr[j];
                rbuf.arr[j] = rbuf.arr[j + 1];
                rbuf.arr[j + 1] = temp;
            }
    printf("\nElements after sorting:");
    for (i = 1; i <= num; i++)
        printf("%d  ", rbuf.arr[i]);
    printf("\n");

    // server sending message
    buf_length = sizeof(int) * (num + 1);
    if (msgsnd(msqid, &rbuf, buf_length, IPC_NOWAIT) < 0)
    {
        printf("Message not sent\n");
        exit(1);
    }

    else
        printf("Server: written successful\n");
    exit(0);
}
