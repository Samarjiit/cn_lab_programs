#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define MSGSIZE 14
int main() {
	
	char *msg1 ="Hello world 1";
	char *msg2 ="Hello world 2";
	char *msg3 ="Hello world 3";
	
	char inbuf[MSGSIZE];
	int p[2], i;
	pipe(p);
	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);
	
	for(i=0; i<3; i++)
	{
		read(p[0], inbuf, MSGSIZE);
		printf("%s\n", inbuf);
	}
	return 1;
	}
