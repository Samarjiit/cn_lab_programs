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
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);//This line creates a UDP socket using the socket() function. It specifies the address family as AF_INET (IPv4) and the socket type as SOCK_DGRAM, which is used for UDP communication. The third argument (0) typically represents the protocol (0 means the default protocol for the given address family and socket type)
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);//sin_port is set to the port number, with htons() used to convert the port number to network byte order.

        printf("Enter the ip address: ");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(client_socket, buffer, strlen(buffer),0, (struct sockaddr*)&server_addr, sizeof(server_addr));//This line sends the contents of the buffer to the server using the sendto() function. It includes the client's socket descriptor, the data to send (the IP address entered by the user), the length of the data, flags (0 in this case), the server's address, and the size of the server's address structure.
        
	
        memset(buffer, 0, BUFFER_SIZE);
        int read_result = recvfrom(client_socket, buffer, sizeof(buffer),0, NULL, NULL);//he recvfrom() function is used to receive data from the server. The last two NULL arguments are for the source address and source address length, which are not needed in this case.
        if (read_result < 0) {
            perror("Error in reading from server");
            exit(1);
        } else if (read_result == 0) {
            printf("Server disconnected\n");
            exit(1);
        }

        printf("Server found class: %s", buffer);
        printf("session ended\n");
           

    close(client_socket);
  
    return 0;
}
