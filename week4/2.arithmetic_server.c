#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
    int n, msqid;
    struct msgbuf buf;
    int len = sizeof(buf);
    buf.mtype = 1;
    msqid = msgget(1234, 0666);
    printf("server running\n");
    msgrcv(msqid, &buf, len, 1, 0);
    float num1 = buf.num[0], num2 = buf.num[1], ans;
    char sign = (char)buf.num[2];
    printf("number1: %.2f\nnumber2: %.2f\noperation: %c\n", num1, num2, sign);
    if (sign == '+')
        ans = num1 + num2;
    else if (sign == '-')
        ans = num1 - num2;
    else if (sign == '*')
        ans = num1 * num2;
    else if (sign == '/')
        ans = num1 / num2;
    else
        printf("Invalid operator\n");
    buf.num[4] = ans;
    buf.mtype = 2;
    if (msgsnd(msqid, &buf, sizeof(buf), IPC_NOWAIT) >= 0)
        printf("Message Sent\n");
    return 0;
}
