#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12000
#define BUFFER_SIZE 10

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    int fd;
    int bytesRead;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    addr_size = sizeof(serverAddr);

    // Input file name
    printf("Enter the name of the file: ");
    scanf("%s", buffer);

    // Send the file name to the server
    ssize_t len = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, addr_size);
    if (len < 0) {
        perror("Send failed");
        exit(1);
    }

    // Open an output file for writing
    fd = open("destination.txt", O_WRONLY | O_CREAT, 0600);
    if (fd == -1) {
        perror("File creation failed");
        exit(1);
    }
    printf("Data from server:\n");
    while (1) {
        // Receive data from the server
        memset(buffer, 0, BUFFER_SIZE);
        bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, &addr_size);
        if (bytesRead < 0) {
            perror("Receive failed");
            exit(1);
        }

        if (bytesRead == 0) {
            break;
        }
        if (strcmp(buffer, "Error\n") == 0) {
            printf("Wrong file name given\n");
            exit(1);
        }

        // Display and write the data to the output file
        printf("%s", buffer);
        write(fd, buffer, bytesRead);
    }

    printf("File written successfully to destination.txt\n");

    close(fd);
    close(sockfd);
    return 0;
}
