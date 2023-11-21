#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Structure to hold the quadratic equation coefficients and roots
struct QuadraticEq {
    double a;
    double b;
    double c;
    double root1;
    double root2;
};

int main() {
    // Create a socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12000);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    // Provide coefficients (a, b, c) of the quadratic equation
    struct QuadraticEq eq;
    printf("Sample equation ax2 + bx + c\n");
    printf("Enter a: ");
    scanf("%lf", &eq.a);
    printf("Enter b: ");
    scanf("%lf", &eq.b);
    printf("Enter c: ");
    scanf("%lf", &eq.c);

    // Send coefficients to the server
    sendto(client_socket, &eq, sizeof(eq), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive the roots from the server
    recvfrom(client_socket, &eq, sizeof(eq), 0, 0, 0);

    // Display the roots of the quadratic equation
    printf("Root 1: %.2f\n", eq.root1);
    printf("Root 2: %.2f\n", eq.root2);

    // Close the client socket
    close(client_socket);

    return 0;
}
