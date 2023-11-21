#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <math.h>

int main() {
    void *shared_memory;
    int *data;
    char response[100];
    int shmid;

    shmid = shmget((key_t)1122, sizeof(int), 0666 | IPC_CREAT);
    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("Server attached at %p\n", shared_memory);

    data = (int *)shared_memory;

    printf("Waiting for client to send an integer...\n");

    while (*data == 0) {
        sleep(1);
    }

    int num = *data;
    printf("Received integer from client: %d\n", num);

    int originalNum = num;
    int sum = 0;
    int digit;
    int n = (int)log10(num) + 1;

    while (num > 0) {
        digit = num % 10;
        sum += (int)pow(digit, n);
        num /= 10;
    }

    if (sum == originalNum) {
        strcpy(response, "YES");
    } else {
        strcpy(response, "NO");
    }

    strcpy((char *)shared_memory, response);
    printf("Sent response to client: %s\n", response);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
