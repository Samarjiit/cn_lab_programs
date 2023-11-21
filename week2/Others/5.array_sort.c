#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXSIZE 10
void main()
{
    int pid, array[MAXSIZE], a[10];
    int i, j, num, temp;
    int p[2], o;
    pipe(p);
    printf("Enter the value of num \n");
    scanf("%d", &num);
    printf("Enter the elements one by one \n");
    for (i = 0; i < num; i++)
    {
        scanf("%d", &array[i]);
    }
    printf("Input array is \n");
    for (i = 0; i < num; i++)
    {
        printf("%d\n", array[i]);
    }
    pid = fork();
    /* Bubble sorting begins */
    if (pid == 0)
    {
        printf("Child -Sorting \n");
        for (i = 0; i < num; i++)
        {
            for (j = 0; j < (num - i - 1); j++)
            {
                if (array[j] > array[j + 1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }

        for (i = 0; i < num; i++)
        {
            printf("Child %d\n", array[i]);
        }
        close(p[0]);
        write(p[1], array, sizeof(int) * num);
        printf(" child ends \n");
    }
    else
    {
        close(p[1]);
        read(p[0], a, sizeof((int) * num));
        printf("Sorted array is...\n");
        for (i = 0; i < num; i++)
        {
            read(p[0], a, sizeof(int)*num);
            printf("Parent %d\n", a[i]);
        }
    }
}