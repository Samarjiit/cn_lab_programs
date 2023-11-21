#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
        pid_t pid;
        int n;

       printf("Inside Parent process\n");
        printf("Enter an integer: ");
        scanf("%d", &n);
        
        pid = fork();

        if (pid < 0) {
                printf("Fork failed\n");
                return 1;
        }
        else if (pid == 0)
        {
                printf("Inside Child\n");
                for(int i=1; i<=10; i++)
                {
                        printf("%d * %d = %d\n", n, i, n*i);
                }            

        }
        else {
                int status;
                wait(&status);
                printf("Inside Parent: Child process finished.\n");

        }

        return 0;
}