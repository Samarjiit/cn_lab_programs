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
    key_t key= 1234;
    shmid = shmget(key, sizeof(100), 0666| IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);
    
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
