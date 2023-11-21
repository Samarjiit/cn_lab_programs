#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {


    int account_no;
    int pin;
    int withdrawal_amt;
     
    // Create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    printf("Enter account no:");
    scanf("%d", &account_no);
    printf("Enter 4-digit pin: ");
    scanf("%d", &pin);
    printf("Enter withdrawal amount:");
    scanf("%d",&withdrawal_amt);
    

    // Send account details to the server
    send(client_socket, &account_no, sizeof(account_no), 0);
    send(client_socket, &pin, sizeof(pin), 0);
    send(client_socket, &withdrawal_amt, sizeof(withdrawal_amt), 0);

    int response, balance;
    recv(client_socket, &response, sizeof(response), 0);
    recv(client_socket, &balance, sizeof(balance), 0);
    if (response == 0) {
        printf("Invalid account number or PIN.\n");
    } else if (response == -1) {
        printf("Not enough balance.\n");
    } else {
        printf("Withdrawn amount: %d\n", response);
    }
    printf("Balace amount is: %d\n", balance);

    // Close the client socket
    close(client_socket);

    return 0;
}
