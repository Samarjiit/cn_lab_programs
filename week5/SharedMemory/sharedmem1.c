#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{

	int shmid,pid;
	char * ptr1 , *ptr2;

		shmid=shmget(0x100,20,IPC_CREAT|0666);

		//ptr1=(char *)shmat(shmid,(char *)0,0);
		ptr1=(char *)shmat(shmid,NULL,0);
		ptr2=(char *) malloc(20);
		pid=fork();
		
		if(pid==0)
		{
			strcpy(ptr1,"Hello World ");
			strcpy(ptr2,"Good Morning World ");
		}
		else
		{
			wait(0);
			printf("parent reads from shared memeory (ptr1)- %s \n",ptr1); // This data available here because it uses shared 												//memory to store data, so both
			printf("parent reads from ptr2 -  %s \n",ptr2); // This data not avaiable here ptr2 because data eneted is in child
			
			shmdt(ptr1);
			shmctl(shmid,IPC_RMID,NULL);
		}
}









/*
main()
{
  	int shmid;
	char *ptr1,*ptr2;
	ptr1=(char *) malloc(10);
	ptr2=(char *) malloc(10);
	scanf("%s",ptr1);
	printf(" string is %s \n",ptr1);
	strcpy(ptr2,ptr1);
	printf(" string is %s \n",ptr2);
}
*/
