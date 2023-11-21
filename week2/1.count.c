#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#define MSGSIZE 1024
int main() {
		
	char msg1[MSGSIZE];
	char inbuf[MSGSIZE];
	int p[2], pid;
	int count_d=0, count_c=0;
	pipe(p);
	
	printf("In Parent\n");
	printf("Enter the message:");
	scanf("%s", msg1); 
	write(p[1], msg1, MSGSIZE);	
	
	pid= fork();
	
	if(pid==0){
		
		printf("In Child\n");
		read(p[0], inbuf, sizeof(inbuf));
		printf("Message is:%s\n", inbuf);
		int i=0;
		while(inbuf[i] !='\0'){
			if((inbuf[i]>= 97 && inbuf[i] <=122) || (inbuf[i] >=65 && inbuf[i] <=90)) {
				count_c++;
			}
			else count_d++;
		i++;
		}
		printf("Number of characters is:%d\n", count_c);
		printf("Number of digits is:%d\n", count_d);
	}
	return 0;
	}
