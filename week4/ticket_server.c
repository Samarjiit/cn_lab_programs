// multiplex_server.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define NUM_CATEGORIES 5
#define MAX_TICKETS 20

struct msg
{
    long mtype;
    char name[50];
    char phone[15];
    int category;
    int num_tickets;
    int failed;
};

int available_tickets[] = {MAX_TICKETS, MAX_TICKETS, MAX_TICKETS, MAX_TICKETS, MAX_TICKETS};

int main()
{
    int key = 1500;
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid < 0)
    {
        perror("msgget");
        return 1;
    }

    int size = sizeof(struct msg) - sizeof(long);

    struct msg req;
    int res = msgrcv(msqid, &req, size, 1, 0); // 1 -> client to server messages
    if (res < 0)
    {
        perror("msgrcv");
        return 1;
    }

    // Prepare response
    struct msg response;
    response.mtype = 2;
    strcpy(response.name, req.name);
    strcpy(response.phone, req.phone);
    response.category = req.category;

    if (req.num_tickets > available_tickets[req.category - 1])
    {
        printf("Not enough tickets!\n");
        response.num_tickets = 0;
        response.failed = 1;
    }
    else
    {
        // Update available tickets
        available_tickets[req.category - 1] -= req.num_tickets;
        response.num_tickets = req.num_tickets;
        response.failed = 0;
    }

    // Send booking information
    res = msgsnd(msqid, &response, size, 0);
    if (res < 0)
    {
        perror("msgsnd");
        return 1;
    }

    return 0;
}
