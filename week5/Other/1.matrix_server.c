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
    printf("Server is waiting\n");
    getchar();
    shmid = shmget((key_t)1122, sizeof(int) * ROWS * COLS, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    matrix = (int *)shmat(shmid, NULL, 0);
    if (matrix == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Received Matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i * COLS + j]);
        }
        printf("\n");
    }

    int transpose[COLS][ROWS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            transpose[j][i] = matrix[i * COLS + j];
        }
    }

    shmdt(matrix);
    shmid = shmget((key_t)1123, sizeof(int) * COLS * ROWS, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    matrix = (int *)shmat(shmid, NULL, 0);
    if (matrix == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            matrix[i * ROWS + j] = transpose[i][j];
        }
    }
printf("Transpose Matrix is:\n");
for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", matrix[i * COLS + j]);
        }
        printf("\n");
    }
    shmdt(matrix);
    printf("Transposed Matrix Sent Back to Client.\n");
    shmctl(shmid,IPC_RMID,0);
    return 0;
}
