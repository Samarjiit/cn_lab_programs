#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXSIZE 20
int main()
{
    int pid, array[MAXSIZE], buffer[MAXSIZE];
    int i, j=0, num;
    int p[2];
    pipe(p);
    printf("Enter number of elements:");
    scanf("%d", &num);
    printf("Enter the elements one by one \n");
    for (i = 0; i < num; i++)
    {
        scanf("%d", &array[i]);
    }
    printf("Input array is \n");
    for (i = 0; i < num; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");
    pid = fork();
    
    if (pid == 0)
    {
        printf("In Child, selecting evens\n");
        for (i = 0; i < num; i++)
        {
            if(array[i] %2 ==0) {
                buffer[j] = array[i];
                j++;
            }
        }
        close(p[0]);
        write(p[1], buffer, sizeof(buffer));
        printf("Child ends\n");
    }
    else
    {
        close(p[1]);
        read(p[0], buffer, sizeof(buffer));
        printf("Parent: Even array is:");
        int m=0;
		while(buffer[m] !=0){
            printf("\t%d", buffer[m]);
            m++;
    }
    printf("\n");
    }
    return 0;
}