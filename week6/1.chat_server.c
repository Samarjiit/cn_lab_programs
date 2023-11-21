#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;//Declares two integer variables server_socket and client_socket for storing socket descriptors.
    struct sockaddr_in server_addr, client_addr; //Declares two structures server_addr and client_addr of type sockaddr_in for storing server and client socket addresses, respectively
    socklen_t client_addr_len = sizeof(client_addr); //Declares a socklen_t variable client_addr_len and initializes it with the size of the client_addr structure
    char buffer[BUFFER_SIZE];//for storing the data and reading 

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);//This line creates a socket using the socket function. It specifies that the socket will use IPv4 (AF_INET) and will be of type SOCK_STREAM (TCP)
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);//Configures the server_addr structure with the server's address information. It sets the address family to AF_INET (IPv4), binds the server to all available network interfaces (INADDR_ANY), and specifies the port to listen on (converted to network byte order using htons
//htons() function makes sure that numbers are stored in memory in network byte order, which is with the most significant byte first. It will therefore swap the bytes making up the number so that in memory the bytes will be stored in the order

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in socket binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == 0) {
        printf("Listening for clients...\n");
    } else {
        perror("Error in listening");
        exit(1);
    }

    // Accept a client connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);//Accepts a client connection using the accept function. This blocks until a client connects.


    if (client_socket < 0) {
        perror("Error in accepting");
        exit(1);
    }
    printf("Client connected\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int read_result = recv(client_socket, buffer, sizeof(buffer), 0);
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
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
