#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <Winsock2.h>
#include <arpa/inet.h>

// Structure to hold the quadratic equation coefficients and roots
struct QuadraticEq {
    double a;
    double b;
    double c;
    double root1;
    double root2;
};

// Function to calculate the roots of the quadratic equation
void calculateRoots(struct QuadraticEq* eq) {
    double discriminant = (eq->b * eq->b) - (4 * eq->a * eq->c);

    if (discriminant > 0) {
        eq->root1 = (-eq->b + sqrt(discriminant)) / (2 * eq->a);
        eq->root2 = (-eq->b - sqrt(discriminant)) / (2 * eq->a);
    } 
    
    else if (discriminant == 0) {
        eq->root1 = eq->root2 = -eq->b / (2 * eq->a);
    }

}

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server is listening...\n");

    // Accept a client connection
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

    // Handle client requests
    struct QuadraticEq eq;

    // Receive coefficients (a, b, c) from the client
    recv(client_socket, &eq, sizeof(eq), 0);
    printf("Received from client:\n");
    printf("a= %.2lf\n", eq.a);
    printf("b= %.2lf\n", eq.b);
    printf("c= %.2lf\n", eq.c);

    // Calculate the roots of the quadratic equation
    calculateRoots(&eq);
    printf("Root 1: %.2lf\n", eq.root1);
    printf("Root 2: %.2lf\n", eq.root2);
    printf("Roots sent to clinet\n");
    // Send the roots back to the client
    send(client_socket, &eq, sizeof(eq), 0);
    sleep(2);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
