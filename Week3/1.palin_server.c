#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define SIZE 64

int is_palindrome(char str[]) {
    // Check if the string is a palindrome
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // Not a palindrome
        }
    }
    return 1; // Palindrome
}

int main() {
    char buffer[SIZE], reply[SIZE];
    int fd, fi;
    fi= mkfifo("named_pipe", 0777);  // Create the named pipe
    if(fi <0) {
        printf("Named pipe creation failed\n");
        return 1;
    }
    printf("Server is ready.\n");
    fd = open("named_pipe", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("Server Received: %s\n", buffer);

    if (is_palindrome(buffer)) {
        strcpy(reply, "YES");
    } 
    else {
        strcpy(reply, "NO");
    }
    reply[3]='\0';

    fd = open("named_pipe", O_WRONLY);
    write(fd, reply, sizeof(reply));
    close(fd);
    
    return 0;
}
