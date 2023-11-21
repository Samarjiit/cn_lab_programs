#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#define MSGSIZE 14
int main() {
		
	int num=2, status;
	int inbuf;
	int p[2], pid;
	pipe(p);
	pid =fork();
	if(pid >0) {
		printf("In Parent\n");
		write(p[1], &num, MSGSIZE);
		wait(&status);
	}
	else if(pid==0)
	{
		printf("In Child\n");
		read(p[0], &inbuf, MSGSIZE);
		printf("Message: %d\n", inbuf);
	}
	return 1;
	}
