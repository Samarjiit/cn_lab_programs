#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define SIZE 1024

int main()
{
    pid_t pid;
    char filename[100];
    int file, fdwrite, c;
    char buffer[SIZE];
    ssize_t count;

    printf("Inside Parent process: ");
    printf("Enter the file name: ");
    scanf("%s", filename);
    fdwrite = open( filename , O_WRONLY | O_CREAT, S_IRWXU );
    if (fdwrite == -1) {
        printf("Error opening file");
        close(fdwrite);
        return 1;
    }
    printf("Enter the data to be written to the file: ");
    while ((c = getchar()) != '\n');
    fgets(buffer, SIZE, stdin);
    count = write(fdwrite, buffer, sizeof(buffer));
    close(fdwrite);
    printf("File written successfully!\n");

    pid = fork();

    if (pid < 0)
    {
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

        count = read(file, buffer, sizeof(buffer));

        buffer[1024] = '\0';
        printf("Child:Data from the file: %s\n", buffer);

        close(file);
        return 1;
    }
    else
    {
        int status;
        wait(&status);
        printf("Inside Parent: Child process finished.\n");
    }

    return 0;
}
