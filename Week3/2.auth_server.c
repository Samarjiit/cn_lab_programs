#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define SIZE 64

int verify(char uname[], char pass[]) {
    //function to verify username and password
    char username[] ="admin";
    char password[] = "admin123";
    if (strcmp(uname, username) == 0 && strcmp(pass, password) == 0) {
        return 1;
    }
    return 0;    
}

int main() {
    char usern[SIZE], pass[SIZE],reply[SIZE];
    int fd, fi;
    fi= mkfifo("named_pipe", 0777);  // Create the named pipe
    if(fi <0) {
        printf("Named pipe creation failed\n");
        return 1;
    }
    printf("Server is ready.\n");
    fd = open("named_pipe", O_RDONLY);
    read(fd, usern, sizeof(usern));
    read(fd, pass, sizeof(pass));
    close(fd);
    printf("Server Received: %s\t%s\n", usern, pass);

    if (verify(usern, pass)) {
        strcpy(reply, "Welcome admin");
    } 
    else {
        strcpy(reply, "Login access denied");
    }

    fd = open("named_pipe", O_WRONLY);
    write(fd, reply, sizeof(reply));
    close(fd);
    
    return 0;
}
