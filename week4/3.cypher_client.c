#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct msgbuf
{
    long mtype;
    char text[100];
};
int main()
{
    char temp[100];
    int c;
    struct msgbuf buf;
    int len = sizeof(buf) - sizeof(long);
    int msqid = msgget(1234, IPC_CREAT | 0777);
    buf.mtype = 1;
    printf("Enter text to convert to cypher: ");
    fgets(buf.text, 100, stdin);
    if (msgsnd(msqid, &buf, len, IPC_NOWAIT) >= 0)
        printf("Message Sent to server\n");
    msgrcv(msqid, &buf, len, 2, 0);
    printf("The cypher text is: %s \n", buf.text);
    msgctl(msqid, IPC_RMID, 0);
    return 1;
}
