/*
3.1 Implement Client putting unsorted array in message queue-1; server reads message queue and sorts
array and puts sorted array to another message queue-2, client reads message queue-2 and displays
sorted array.
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MSGSZ     128


typedef struct msgbuf {
         long    mtype;
         int   m_array[20];
         } message_buf;

main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;
    int n,i;
    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }

   //assigning message type  
    sbuf.mtype = 1;

//accepting data to be passed
    printf("Enter the size of array:");
	scanf("%d",&n); 
    sbuf.m_array[0]=n;   // number of elements in array.
    printf("Enter your elements: ");
    for(i=1;i<=n;i++)
		scanf("%d",&sbuf.m_array[i]);
    
    buf_length = sizeof(int)*(n+1) ;
    
  
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
    //   printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        exit(1);
    }

   else
	printf("written successful"); 
    //  printf("Message: \"%s\" Sent\n", sbuf.mtext);
      
//    exit(0);


//readin

    
    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &sbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     *///num=sbuf.m_array[0];
	printf("\nElements received\n");
	for(i=1;i<=n;i++)
		printf("%d\t", sbuf.m_array[i]);

}

