    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    while (1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer),0);
        
	if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat session ended\n");
            break;
        }
        memset(buffer, 0, BUFFER_SIZE);
        int read_result = recv(client_socket, buffer, sizeof(buffer),0);
        if (read_result < 0) {
            perror("Error in reading from server");
            break;
        } else if (read_result == 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("Server: %s", buffer);

        
    }

    close(client_socket);

    return 0;
}
