#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	int p[2], retval;
	retval =pipe(p);
	printf("p[0] is: %d, p[1] is:%d\n",p[0], p[1]);
	}
