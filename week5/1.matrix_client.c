#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define ROWS 3
#define COLS 3

int main() {
    int *matrix;
    int shmid;
    key_t key1 =1234;
    key_t key2 =1235;

    shmid = shmget(key1, sizeof(int) * ROWS * COLS, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    matrix = (int *)shmat(shmid, NULL, 0);
    if (matrix == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Enter a Matrix of dimension 3:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &matrix[i * ROWS + j]);
        }
    }

    shmdt(matrix);
    printf("Matrix Sent to Server.\n");
    shmid = shmget(key2, sizeof(int) * COLS * ROWS, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    matrix = (int *)shmat(shmid, NULL, 0);
    if (matrix == (void *)-1) {
        perror("shmat");
        exit(1);
    }
getchar();
getchar();
    printf("Received Transposed Matrix:\n");
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", matrix[i * ROWS + j]);
        }
        printf("\n");
    }
    shmdt(matrix);
shmctl(shmid,IPC_RMID,0);
    return 0;
}
