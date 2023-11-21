#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define SIZE 10

int isArmstrong(int num)
{
	int originalNum = num;
	double sum = 0;
	double digits = 0;

	while (num > 0)
	{
		digits++;
		num /= 10;
	}

	num = originalNum;

	while (num > 0)
	{
		double digit = num % 10;
		int digitPower = 1;
		for (int i = 0; i < digits; i++)
		{
			digitPower *= digit;
		}
		sum += digitPower;
		num /= 10;
	}

	return sum == originalNum;
}

int main()
{
	int fd[2], num;
	pid_t pid;
	if (pipe(fd) == -1)
	{
		printf("pipe error");
		return 1;
	}
	
	printf("Parent:Enter an integer: ");
	scanf("%d", &num);
	pid = fork();

	if (pid == -1)
	{
		printf("fork failed");
		return 1;
	}

	if (pid == 0)
	{				 

		close(fd[0]); // Close the read end of the pipe in child

		if (isArmstrong(num))
		{
			char *buffer = "Yes";
			write(fd[1],buffer , 4);
			printf(" child ends \n");
		}
		else
		{
			char *buffer = "No";
			write(fd[1],buffer, 3);
			printf(" child ends \n");

		}

		return 0;
	}
	if(pid > 0)
	{
		wait(NULL);	// Wait for the child process to finish
		close(fd[1]); // Close the write end of the pipe
		char result[3]; 
		read(fd[0], result, sizeof(result));
		printf("In parent:Is Armstrong: %s\n", result);
	}

	return 0;
}
