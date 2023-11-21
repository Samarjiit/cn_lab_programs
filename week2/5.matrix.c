#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define S 10
int main()
{
    int pid, matrix[S][S], r, c;
    int i, j, num, array[S][S];
    int p[2];
    pipe(p);
    printf("Enter the row and column size \n");
    scanf("%d%d", &r, &c);
    printf("Enter the elements one by one \n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    printf("Input Matrix is \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    pid = fork();
    if (pid == 0)
    {
        printf("Inside Child\n");
        printf("Enter the number to multiply: \n");
        scanf("%d", &num);
        for (i = 0; i < r; i++)
        {
            for (j = 0; j < c; j++)
            {
                matrix[i][j] = matrix[i][j] * num;
            }
        }

        close(p[0]);
        write(p[1], matrix, S * S * sizeof(int));
        printf(" child ends \n");
    }
    else
    {
        close(p[1]);
        read(p[0], array, S * S * sizeof(int));
        printf("Parent:Final Matrix is...\n");
        for (i = 0; i < r; i++)
        {
            for (j = 0; j < c; j++)
            {
                printf("%d\t", array[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}