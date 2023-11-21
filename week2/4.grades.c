#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXSIZE 20
int main()
{
    int pid, marks[MAXSIZE];
    char buffer[MAXSIZE], buff[MAXSIZE], reg[MAXSIZE];
    int i, num, fd[2];
    float avg;
    pipe(fd);
    printf("Enter register number of student:");
    scanf("%s", reg);
    printf("Enter number of subjects:");
    scanf("%d", &num);
    printf("Enter marks:\n");
    for (i = 0; i < num; i++)
    {
        printf("Marks %d: ", i + 1);
        scanf("%d", &marks[i]);
    }
    pid = fork();

    if (pid == 0)
    {
        printf("In Child, calculating average\n");
        for (i = 0; i < num; i++)
        {
            avg += marks[i];
        }
        avg = avg / num;
        char grade;

        if (avg >= 90)
        {
            grade = 'A';
        }
        else if (avg >= 80)
        {
            grade = 'B';
        }
        else if (avg >= 70)
        {
            grade = 'C';
        }
        else if (avg >= 60)
        {
            grade = 'D';
        }
        else if (avg >= 50)
        {
            grade = 'E';
        }
        else
        {
            grade = 'F';
        }
        buffer[0] = grade;
        i=0;
        while(reg[i] != '\0'){
            buffer[i+1] = reg[i];
            i++;
        }
        close(fd[0]);
        write(fd[1], buffer, sizeof(buffer));
        printf("Child ends\n");
    }
    else
    {
        close(fd[1]);
        read(fd[0], buff, sizeof(buff));
        printf("In Parent: Register no is: ");
        i=1;
        while(buff[i] != '\0'){
            printf("%c", buff[i]);
            i++;
        }
        printf("\nGrade is: %c\n", buff[0]);
        
    }
    return 0;
}