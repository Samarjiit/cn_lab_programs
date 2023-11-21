/*
3.1 Implement Client putting unsorted array in message queue-1; server reads message queue and sorts
array and puts sorted array to another message queue-2, client reads message queue-2 and displays
sorted array.
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include<stdlib.h>

#define MSGSZ     128


/*
 * Declare the message structure.
 */

typedef struct msgbuf {
    long    mtype;
    int  a[20];
    } message_buf;


main()
{
    int i,j,temp,num;
    int msqid;
    key_t key;
    message_buf  rbuf;
    size_t buf_length;
    int msgflg = IPC_CREAT | 0666;

    key = 1234;

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    
    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */num=rbuf.a[0];
	printf("\nElements received\n");
	for(i=1;i<=num;i++)
		printf("%d\t", rbuf.a[i]);
		for(i=1;i<=num;i++)
				for(j=1;j<=num-i;j++)
				if(rbuf.a[j]>rbuf.a[j+1])	
				{
					temp=rbuf.a[j];
					rbuf.a[j]=rbuf.a[j+1];
					rbuf.a[j+1]=temp;
				}
		printf("\nElements after sorting\n");
	for(i=1;i<=num;i++)
		printf("%d\t", rbuf.a[i]);
	printf("\n");
	
	//server sending message	
	buf_length = sizeof(int)*(num+1) ;
        if (msgsnd(msqid, &rbuf, buf_length, IPC_NOWAIT) < 0) {
    //   printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        exit(1);
        }

       else
	printf("written successful"); 
    //  printf("Message: \"%s\" Sent\n", sbuf.mtext);
      

    exit(0);
}

