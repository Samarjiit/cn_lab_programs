#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Define account information
struct Account {
    int account_no;
    int pin;
    int balance;
};

// Account database with pre-stored information
struct Account accounts[] = {
    {1001, 1234, 1500},
    {1002, 1235, 1500},
    {1003, 1236, 5600},
    {1004, 1237, 1200},
    {1005, 1238, 2000}
};

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
    int acc_no, pin, withdrawal_amt;
    int is_valid_account = 0;
    int response, bal=0;

    // Receive account number, PIN, and withdrawal amount from the client
    recv(client_socket, &acc_no, sizeof(acc_no), 0);
    recv(client_socket, &pin, sizeof(pin), 0);
    recv(client_socket, &withdrawal_amt, sizeof(withdrawal_amt), 0);
    printf("Data received from client is\n");
    printf("Account no: %d\n", acc_no);
    printf("Pin: %d\n", pin);
    printf("Withdrawal amount: %d\n", withdrawal_amt);

    // Check if the account is valid
    for (int i = 0; i < 5; i++) {
        if (accounts[i].account_no == acc_no && accounts[i].pin == pin) {
            is_valid_account = 1;
            if (accounts[i].balance >= withdrawal_amt) {
                accounts[i].balance -= withdrawal_amt;
                response = withdrawal_amt;
                bal =accounts[i].balance;
            } else {
                response = -1; // Not enough balance
                bal =accounts[i].balance;
            }
            break;
        }
    }

    if (!is_valid_account) {
        response = 0; // Invalid account number or PIN
    }

    // Send the response back to the client
    send(client_socket, &response, sizeof(response), 0);
    send(client_socket, &bal, sizeof(bal), 0);
    sleep(2);
    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

