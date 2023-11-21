//Ronson Danthy
//220970003
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define SIZE 64


int main() {
    int fd;
    char username[SIZE], pass[SIZE], response[SIZE];

    printf("client: Enter Username: ");
    scanf("%s", username);
    printf("client: Enter Password: ");
    scanf("%s", pass);
    fd = open("named_pipe", O_WRONLY);
    if(fd < 0) {
        printf("Opening pipe failed\n");
        return 1;
    }
    write(fd, username, sizeof(username));
    write(fd, pass, sizeof(pass));
    close(fd);

    fd = open("named_pipe", O_RDONLY);
    read(fd, response, sizeof(response));
    close(fd);
    printf("Client: response from server: %s\n", response);
    unlink("named_pipe");
    return 0;
}
