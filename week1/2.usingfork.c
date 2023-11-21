#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
        pid_t pid;
        char filename[100];
        int file;
        char buffer[11];
       ssize_t count;

       printf("Inside Parent process\n");
        printf("Enter the file name: ");
        scanf("%s", filename);

        pid = fork();

        if (pid < 0) {
                printf("Fork failed\n");
                return 1;
        }
        else if (pid == 0)
        {
                printf("Inside Child Process\n");
                file = open(filename, O_RDONLY);
                if (file == -1)
                {
                        printf("Error opening file\n");
                        return 1;
                }

                count=read(file, buffer, sizeof(buffer));

                buffer[10] = '\0';
                printf("Child: First 10 characters from the file: %s\n", buffer);

                close(file);
                return 1;
        }
        else {
                int status;
                wait(&status);
                printf("Inside Parent: Child process finished.\n");
        }

        return 0;
}