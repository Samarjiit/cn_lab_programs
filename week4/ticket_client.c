// multiplex_client.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

struct msg
{
    long mtype;
    char name[50];
    char phone[15];
    int category;
    int num_tickets;
    int failed;
};

int main()
{
    int key = 1500;
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid < 0)
    {
        perror("msgget");
        return 1;
    }

    struct msg booking_request;
    int size = sizeof(struct msg) - sizeof(long);

    printf("Enter your name: ");
    fgets(booking_request.name, sizeof(booking_request.name), stdin);

    printf("Enter your phone number: ");
    fgets(booking_request.phone, sizeof(booking_request.phone), stdin);

    printf("Enter ticket category (1-5): ");
    scanf("%d", &booking_request.category);

    printf("Enter number of tickets: ");
    scanf("%d", &booking_request.num_tickets);

    booking_request.mtype = 1;

    // Send booking request
    int res = msgsnd(msqid, &booking_request, size, 0);
    if (res < 0)
    {
        perror("msgsnd");
        return 1;
    }

    // Receive booking information
    struct msg resp;
    res = msgrcv(msqid, &resp, size, 2, 0); // 2 -> server to client messages
    if (res < 0)
    {
        perror("msgrcv");
        return 1;
    }

    if (resp.failed)
    {
        printf("Sorry, booking failed!\n");
    }
    else
    {
        printf("Booking Successfull!\n");
        printf("Name: %s", resp.name);
        printf("Phone: %s", resp.phone);
        printf("Category: %d\n", resp.category);
        printf("Number of tickets: %d\n", resp.num_tickets);
    }

    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
