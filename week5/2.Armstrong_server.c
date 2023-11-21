#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>
bool isArmstrong(int num)
{
	int originalNum = num;
	double sum = 0;
	double digits = 0;

	while (num > 0)
	{
		digits++;
		num /= 10;
	}

	num = originalNum;

	while (num > 0)
	{
		double digit = num % 10;
		int digitPower = 1;
		for (int i = 0; i < digits; i++)
		{
			digitPower *= digit;
		}
		sum += digitPower;
		num /= 10;
	}

	return sum == originalNum;
}

int main() {
    void *shared_memory;
    int *data;
    char response[100];
    int shmid;
    key_t key1 = 1234;
    printf("Server is running..\n");
    shmid = shmget(key1, sizeof(int), 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);
   
    data = (int *)shared_memory;

    printf("Waiting for client to send an integer...\n");

    while (*data == 0) {
        sleep(1);
    }

    int num = *data;
    printf("Received integer from client: %d\n", num);

   

    if (isArmstrong(num)) {
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
