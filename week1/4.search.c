#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
	pid_t pid;
	int file, arr[20], n, m;

	printf("Inside Parent process\n");
	printf("Enter size of array: ");
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
	printf("Element %d: ",i);
	scanf("%d", &arr[i]);
	}

	pid = fork();

	if (pid < 0) {
	printf("Fork failed\n");
	return 1;
	}
	else if (pid == 0)
	{
		printf("child:Enter the number to search in the array:");
		scanf("%d", &m);
		for(int i=0; i<n; i++) {
			if(arr[i]==m){
			printf("number found at index: %d \n", i);
			m=-1;
			}
		}
		if(m !=-1)
		printf("Number not found\n");

	}
	else {
	int status;
	wait(&status);
	printf("Inside Parent: Child process finished.\n");

	}

return 0;
}
