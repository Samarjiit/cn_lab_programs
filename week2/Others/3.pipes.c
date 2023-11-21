#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#define MSGSIZE 14
int main() {
		
	char *msg1 ="Hello world 1";
	char inbuf[MSGSIZE];
	int p[2], pid;
	pipe(p);
	pid =fork();
	if(pid >0) {
		printf("In Parent\n");
		write(p[1], msg1, MSGSIZE);
	}
	else {
		printf("In Child\n");
		read(p[0], inbuf, MSGSIZE);
		printf("Message: %s\n", inbuf);
	}
	return 1;
	}
