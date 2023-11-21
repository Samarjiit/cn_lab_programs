//Ronson Danthy
//220970003

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define PATH "pipe"
#define SIZE 100
int main()
{
    
	char name[SIZE],src[SIZE],dest[SIZE], message[SIZE];
    float bill;
    int seats=0,fd, fi, status, remain;
    fd = open(PATH, O_WRONLY);
    printf("Enter Passenger name:");
	scanf("%s",name);
    printf("Available locations:\n");
    printf("manipal-udupi\nudupi-mangalore\nbangalore-mangalore\nbangalore-mysore\nmumbai-bangalore\n");
	printf("Enter source location name:");
	scanf("%s",src);
	write(fd, src, sizeof(src));
	printf("Enter destination location name:");
	scanf("%s", dest);
	write(fd, dest, sizeof(dest));
	printf("Enter Number of seats:");
	scanf("%d",&seats);
	write(fd, &seats, sizeof(seats));
    close(fd);
    fd = open(PATH, O_RDONLY);
    read(fd, message, sizeof(message));
    read(fd, &status, sizeof(int));
    read(fd, &bill, sizeof(float));
    read(fd, &remain, sizeof(int));
    close(fd);
    if(status==1)
    {
        printf("\n------------------------------\n");
        printf("%s\n", message);
        unlink(PATH);
        return 0;
    }
    printf("\n------------------------------\n");
	printf("Passenger name:%s\n",name);
    printf("Source location:%s\n",src);
    printf("Destination location:%s\n",dest);
    printf("Number of seats:%d\n",seats);
    printf("Total bill amount:%.2f\n",bill);
    printf("Remaining seats:%d\n",remain);
    fi =unlink(PATH);
    if(fi <0) {
        printf("Named pipe deletion failed\n");
        return 1;
    }
    return 0;
    
}