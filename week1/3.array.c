#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
        pid_t pid;
        int  arr[20], n;

       printf("Inside Parent process\n");
        printf("Enter size of array: ");
        scanf("%d", &n);
        for(int i=0; i<n; i++) {
                printf("Element %d: ",i);
                scanf("%d", &arr[i]);
        }

        pid = fork();

        if (pid < 0) {
                printf("Fork failed\n");
                return 1;
        }
        else if (pid == 0)
        {
                printf("Inside Child\n");
                for(int i=0; i<n; i++)
                        for(int j=i+1; j<n; j++)
                        {
                                if(arr[i] > arr[j]) {
                                        int temp =arr[i];
                                        arr[i] = arr[j];
                                        arr[j] =temp;
                                }
                        }
                printf("Sorted Array is: ");
                for(int i=0; i<n; i++) {
                        printf("%d\t", arr[i]);
                }
                printf("\n");


        }
        else {
                int status;
                wait(&status);
                printf("Inside Parent: Child process finished.\n");

        }

        return 0;
}