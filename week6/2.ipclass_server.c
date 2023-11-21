#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    char str[BUFFER_SIZE];

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

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
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        perror("Error in accepting");
        exit(1);
    }
    printf("Client connected\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int read_result = read(client_socket, buffer, sizeof(buffer));
        if (read_result < 0) {
            perror("Error in reading from client");
            break;
        } else if (read_result == 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Client: %s\n", buffer);
       
   	int ip=0;
	for(int i=0; buffer[i]!='\0'&&buffer[i]!='.'; i++)   
       		ip=(ip*10)+(buffer[i]-'0');
    	if(ip>=0&&ip<=127)
        	strcpy(str,"Class A Mask:255.0.0.0\n");
    	else if(ip>=128&&ip<=191)
        	strcpy(str,"Class B Mask:255.255.0.0\n");
    	else if(ip>=192&&ip<=223)
        	strcpy(str,"Class C Mask:255.255.255.0\n");
    	else if(ip>=224&&ip<=239)
        	strcpy(str,"Class D\n");
    	else if(ip>=240&&ip<=255)
        	strcpy(str,"Class E \n");
    	else 
        	strcpy(str,"Class Invalid\n");

        write(client_socket, str, strlen(str));
        printf("Calculated class:%s", str);
        printf("Ending the connection\n");
        sleep(2);
        break;
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
