#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#define SIZE 50

int isPallindrome(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}

int main()
{
	int fd[2];
    char str[SIZE], buffer[SIZE];
	pid_t pid;
	if (pipe(fd) == -1)
	{
		printf("pipe error");
		return 1;
	}
	
	printf("Parent:Enter an String: ");
	scanf("%s", str);
	pid = fork();

	if (pid == -1)
	{
		printf("fork failed");
		return 1;
	}

	if (pid == 0)
	{				 
		printf(" child starts \n");
		close(fd[0]); // Close the read end of the pipe in child

		if (isPallindrome(str))
		{
			char buffer[] = "PALLINDROME";
			write(fd[1],buffer , sizeof(buffer));
			printf(" child ends \n");
		}
		else
		{
			char buffer[] = "NOT PALLINDROME";
			write(fd[1],buffer, sizeof(buffer));
			printf(" child ends \n");

		}

		return 0;
	}
	if(pid > 0)
	{
		wait(NULL);	// Wait for the child process to finish
		close(fd[1]); // Close the write end of the pipe
		char result[SIZE]; 
		read(fd[0], result, sizeof(result));
		printf("In parent:Is Pallindrome: %s\n", result);
	}

	return 0;
}
