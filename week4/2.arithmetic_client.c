#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf
{
    long mtype;
    float num[5];
    char op;
};

int main()
{
    struct msgbuf buf;
    char op;
    int msqid = msgget(1234, IPC_CREAT | 0777);
    buf.mtype = 1;
    printf("Enter Two numbers: ");
    scanf("%f", &buf.num[0]);
    scanf("%f", &buf.num[1]);
    printf("Enter operator: ");
    scanf(" %c", &op);
    buf.num[2] = (int)op;
    int len = sizeof(buf);
    if (msgsnd(msqid, &buf, len, IPC_NOWAIT) >= 0)
        printf("Message written\n");
    float ans;
    msgrcv(msqid, &buf, sizeof(buf), 2, 0);
    printf("Answer= %.2f\n", buf.num[4]);
    msgctl(msqid, IPC_RMID, 0);
    return 1;
}
