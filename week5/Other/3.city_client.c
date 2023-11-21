#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    void *shared_memory;
    char *data;
    char response[100];
    int shmid;

    shmid = shmget((key_t)1122, sizeof(100), 0666| IPC_CREAT);
    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("Client attached at %p\n", shared_memory);
    data = (char *)shared_memory;

    char* user_data;
    printf("Enter an state/capital to send to the server: ");
    scanf("%s", data);

    printf("Waiting for server response...\n");
    while (strlen(response)<5) {
        sleep(1);
        strcpy(response, (char *)shared_memory);
    }
    printf("Received response from server: %s\n", response);
    shmdt(shared_memory);

    return 0;
}