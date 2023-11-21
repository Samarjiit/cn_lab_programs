#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {

	int n, square, status;
	pid_t pid;
	printf("Parent:Enter a number:");
	scanf("%d", &n);
	pid =fork();
	if(pid <0) {
	printf("child creation failed\n");
	return 1;
	}
	
	else if(pid==0) {
	printf("child:The pid is %d\n", pid);
	square =n*n;
	printf("child:Square of number is:%d\n", square);
	printf("child: %d, Parent: %d\n",getpid(), getppid());	
	}
	else {
	printf("wait: %d\n",wait(&status));
	printf("Parent:The pid is %d\n", getpid());
	printf("child process finished and returned to parent\n");
	}
	
	return 0;

}
