#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000


struct calculation {
    double a;
    double b;
    char op;
    double ans;
};

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    int buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }
    struct calculation eq;
    printf("Enter the operands and operator\n");
    printf("Enter a: ");
    scanf("%lf", &eq.a);
    printf("Enter b: ");
    scanf("%lf", &eq.b);
    printf("Enter operator: ");
    scanf("%s", &eq.op);

    
        send(client_socket, &eq, sizeof(eq), 0);
        
	recv(client_socket, &eq, sizeof(eq), 0);
        printf("Answer from server: %.2f\n", eq.ans);
    

    close(client_socket);

    return 0;
}

