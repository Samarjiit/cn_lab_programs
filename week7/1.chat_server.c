#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create a socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { //bind() function is used to associate a socket with a specific network address and port. It is typically used on the server side to specify which local network interface and port the server should listen on for incoming connections.
        perror("Error in socket binding");
        exit(1);
    }

    printf("Server is ready...\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int read_result = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (read_result < 0) {
            perror("Error in reading from client");
            break;
        } else if (read_result == 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Client: %s", buffer);
        
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat session ended\n");
            break;
        }

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_addr_len);
    }

    
    close(server_socket);

    return 0;
}
