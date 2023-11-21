#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    void *shared_memory;
    int *data;
    char response[100];
    int shmid;

    shmid = shmget((key_t)1122, sizeof(int), 0666);
    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("Client attached at %p\n", shared_memory);
    data = (int *)shared_memory;

    int num;
    printf("Enter an integer to send to the server: ");
    scanf("%d", &num);

    *data = num; 

    printf("Waiting for server response...\n");
    while (strcmp(response, "YES") != 0 && strcmp(response, "NO") != 0) {
        sleep(1);
        strcpy(response, (char *)shared_memory);
    }
    printf("Received response from server: %s\n", response);
    shmdt(shared_memory);

    return 0;
}