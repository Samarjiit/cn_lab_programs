#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50
struct msgbuf
{
    long mtype;
    int flag;
    int no, category, remain;
};
int main()
{
    int msqid;
    key_t key;
    struct msgbuf rbuf;
    size_t buflen;
    int tickets[5][2] = {{1, 20}, {2, 20}, {3, 20}, {4, 20}, {5, 20}};
    key = 1234;
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        perror("msgget");
        exit(1);
    }

    printf("srever is running\n");
    int rcv_byt, k;
    int sizebyte_rcv = sizeof(rbuf) - sizeof(long);
    if ((rcv_byt = msgrcv(msqid, &rbuf, sizebyte_rcv, 1, 0)) < 0) {
        perror("msgrcv");
        exit(1);
    }
    printf("Message Received from client\n");
    printf("Category: %d\nRequest for booking:%d\n", rbuf.category, rbuf.no);    
    if (rbuf.no <= 20)
    {
        for (int i = 0; i < 5; i++)
        {
            if (rbuf.category == tickets[i][0])
            {
                tickets[i][1] -= rbuf.no;
                printf("Remainig tickets: %d\n", tickets[i][1]);
                rbuf.remain = tickets[i][1];
                break;
            }
        }
    }
    else
    {
        rbuf.flag = 1;
    }

    int snd_byt = sizeof(rbuf) - sizeof(long);
    int num;
    rbuf.mtype = 2;
    if ((num = (msgsnd(msqid, &rbuf, snd_byt, IPC_NOWAIT))) < 0)
    {
        perror("error in msgget");
    }
    else
    {
        printf("Message Sent to client\n");
    }

    return 0;
}