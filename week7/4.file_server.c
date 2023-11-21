#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER_SIZE 10

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE], file_name[30];
    int fd;
    int bytesRead=1;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    addr_size = sizeof(clientAddr);
    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Receive the file name from the client
        ssize_t len = recvfrom(sockfd, file_name, sizeof(file_name), 0, (struct sockaddr *)&clientAddr, &addr_size);
        if (len < 0) {
            perror("Receive failed");
            exit(1);
        }
        file_name[len] = '\0';
        printf("Received file name: %s\n", file_name);

        // Open the file for reading
        fd = open(file_name, O_RDONLY);
        if (fd == -1) {
            perror("File open failed");
            strcpy(buffer, "Error\n");
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, addr_size);
            exit(1);
        }

        // Read and send the file data in chunks
       
        while (bytesRead > 0) {
            bytesRead = read(fd, buffer, sizeof(buffer));
            sendto(sockfd, buffer, bytesRead, 0, (struct sockaddr *)&clientAddr, addr_size);
            printf("bytes sent: %d\n",bytesRead);
        }
        if(bytesRead <= 0) {
        break;
        }
        
    }
    
    printf("File transfer complete.\n");
    sleep(2);
    close(fd);
    close(sockfd);
    return 0;
}
