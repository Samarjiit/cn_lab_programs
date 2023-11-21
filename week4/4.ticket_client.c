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
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    key = 1234;

    if ((msqid = msgget(key, msgflg)) < 0) {
        printf("Message queue creation failed\n");
        return 1;
    }
        

    char name[20];
    int phone;
    sbuf.mtype = 1;
    sbuf.flag = 0;
    printf("Enter your name : ");
    scanf("%s", name);
    printf("Enter your phone number : ");
    scanf("%d", &phone);
    printf("Enter the ticket Category");
    printf("\n1.Comedy\n2.Horror\n3.Action\n4.Romance\n5.Drama\n");
    printf("Enter your choice : ");
    scanf("%d", &sbuf.category);
    printf("Enter the number of tickets : ");
    scanf("%d", &sbuf.no);
    int snd_byt = sizeof(sbuf) - sizeof(long);
    int num;
    if ((num = (msgsnd(msqid, &sbuf, snd_byt, IPC_NOWAIT))) < 0)
    {
        printf("Message Sending Failed\n");
        return 1;
    }
    else
    {
        printf("Message Sent to server\n");
    }

    struct msgbuf rbuf;
    int rcv_byt;
    int sizebyte_rcv = sizeof(rbuf) - sizeof(long);
    if ((rcv_byt = msgrcv(msqid, &rbuf, sizebyte_rcv, 2, 0)) < 0) {
        printf("Message Receiving Failed\n");
        return 1;
    }
        
    if (rbuf.flag == 1)
    {
        printf("Tickets not available\n");
    }

    else
    {
        printf("%d ticket booking successful under the name : %s\n", rbuf.no, name);
        printf("remaining tickets : %d\n", rbuf.remain);
        printf("\n");
    }
}