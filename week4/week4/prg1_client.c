#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>

struct msgBuff{
        long msgtype;
        int data[100];

}message;

int main(){
        int msgQ_id,n;
        key_t key=1234;
        size_t msgLength;
        int flag=IPC_CREAT|0666;
        if(msgQ_id=msgget(key,flag)<0){
                perror("Error while creating message queue..\n");
                exit(1);
        }
        message.msgtype=1;
        printf("Enter number of elements:");
        scanf("%d",&n);
        message.data[0]=n;
        printf("Enter %d elemtns:",n);
        for(int i=1;i<=n;i++)
                scanf("%d",&message.data[i]);
        msgLength=sizeof(message);// if doesnt work check sizeof(int)*(n-1)
        if(msgsnd(msgQ_id,&message,msgLength,IPC_NOWAIT)<0){
                perror("Error while sending..\n");
        }else printf("Mesasge sent server by  queue..\n");
        msgrcv(msgQ_id,&message,sizeof(message),2,0);
        printf("Sorted array\n");
        for(int i=1;i<=message.data[0];i++)
                printf("%d ",message.data[i]);
        return 0;
}#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>

struct msgBuff{
        long msgtype;
        int data[100];

}message;

int main(){
        int msgQ_id,n;
        key_t key=1234;
        size_t msgLength;
        int flag=IPC_CREAT|0666;
        if(msgQ_id=msgget(key,flag)<0){
                perror("Error while creating message queue..\n");
                exit(1);
        }
        message.msgtype=1;
        printf("Enter number of elements:");
        scanf("%d",&n);
        message.data[0]=n;
        printf("Enter %d elemtns:",n);
        for(int i=1;i<=n;i++)
                scanf("%d",&message.data[i]);
        msgLength=sizeof(message);// if doesnt work check sizeof(int)*(n-1)
        if(msgsnd(msgQ_id,&message,msgLength,IPC_NOWAIT)<0){
                perror("Error while sending..\n");
        }else printf("Mesasge sent server by  queue..\n");
        msgrcv(msgQ_id,&message,sizeof(message),2,0);
        printf("Sorted array\n");
        for(int i=1;i<=message.data[0];i++)
                printf("%d ",message.data[i]);
        return 0;
}