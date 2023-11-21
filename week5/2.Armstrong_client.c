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
    key_t key1 =1234;
    shmid = shmget(key1, sizeof(int), 0666);
   
    shared_memory = shmat(shmid, NULL, 0);
    data = (int *)shared_memory;

    int num;
    printf("Enter an number to check Armstrong number: ");
    scanf("%d", &num);

    *data = num; 

    printf("Waiting for server response...\n");
    while (strcmp(response, "YES") != 0 && strcmp(response, "NO") != 0) {
        sleep(1);
        strcpy(response, (char *)shared_memory);
    }
    printf("Received response from server\n whether number is Armstrong: %s\n", response);
    shmdt(shared_memory);

    return 0;
}
