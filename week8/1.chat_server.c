#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER_SIZE 1024


void handle_client(int client_socket, int i) {
    char buffer[BUFFER_SIZE];
    printf("Client %d connected\n",i);
    while (1) {
        int read_size = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (read_size <= 0) {
            printf("Client disconnected\n");
            break;
        }

        buffer[read_size] = '\0';
        printf("Client %d: %s", i,buffer);
	if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat ended\n");
            break;
        }
        printf("Server message to client %d: ", i);
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);
     
    }
    sleep(2);
    close(client_socket);
    
}

int main() {
    int server_socket, new_socket, i=0;
    struct sockaddr_in server_addr, new_addr;//server_socket is the socket descriptor for the server. new_socket is the socket descriptor for the connected clients.i is an identifier for the clients.server_addr and new_addr are structures that store information about the server and new client addresses.addr_size is the size of the address structure.pid is used to store process IDs when forking.
    socklen_t addr_size;
    pid_t pid;//pid is used to store process IDs when forking.

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;//sin_addr.s_addr is set to INADDR_ANY, which means the server can accept connections on any available network interface.

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    if (listen(server_socket, 2) == 0) {//Here, the code makes the server socket listen for incoming connections. It specifies a maximum queue size of 2 for pending connections
        printf("Listening at port %d\n", PORT);
    } else {
        printf("Error in listening");
    }

    addr_size = sizeof(new_addr);

    while(1) {
        new_socket = accept(server_socket, (struct sockaddr*)&new_addr, &addr_size);//Here, the code uses the accept() function to accept incoming client connections. The accepted socket descriptor is stored in new_socket, and i is incremented to assign an identifier to the new client
	i++;
        pid = fork();            // Fork a child process to handle this client The code forks a child process using fork(). The child process will handle the communication with the new client, while the parent process continues to listen for new connections
        if (pid == 0) {
            close(server_socket);
            handle_client(new_socket, i);
            close(new_socket);  
            exit(0); 
        } 
        
        else {
        
        close(new_socket); 
        
        }
        
    }
     
    close(server_socket);
    return 0;
}

