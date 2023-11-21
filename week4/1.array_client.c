

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 128

typedef struct msgbuf
{
    long mtype;
    int arr[20];
} message;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message sbuf;
    size_t buf_length;
    int n, i;
    key = 1234;

    if ((msqid = msgget(key, msgflg)) < 0)
    {
        printf("Message queue creation failed");
        exit(1);
    }
    sbuf.mtype = 1;
    printf("Enter the size of array:");
    scanf("%d", &n);
    sbuf.arr[0] = n;
    printf("Enter your elements: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &sbuf.arr[i]);

    buf_length = sizeof(int) * (n + 1);
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0)
    {
        printf("Message not sent\n");
        exit(1);
    }

    else
        printf("client: written successful\n");

    if (msgrcv(msqid, &sbuf, SIZE, 1, 0) < 0)
    {
        printf("Message not received\n");
        exit(1);
    }

    printf("Elements received: ");
    for (i = 1; i <= n; i++)
        printf("%d  ", sbuf.arr[i]);
    printf("\n");
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}
