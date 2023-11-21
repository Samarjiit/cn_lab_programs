#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define PATH "pipe"
struct Bus {
	char src[100],dest[100];
	int price,seats;
};
int main()
{   	
    unlink(PATH);
	int fi = mkfifo(PATH, 0744);
    if(fi <0) {
        printf("Named pipe creation failed\n");
        return 1;
    }
	struct Bus b[5];
	b[0]=(struct Bus){"manipal","udupi",20,10};
	b[1]=(struct Bus){"udupi","mangalore",200,50};
	b[2]=(struct Bus){"bangalore","mangalore",500,20};
	b[3]=(struct Bus){"bangalore","mysore",400,30};
	b[4]=(struct Bus){"mumbai","bangalore",1000,50};
	char src[100],dest[100], message[100];
    printf("server running\n");
	int seat,j=-1, status=0;
    float bill=0;
	int fd = open(PATH, O_RDONLY);
	read(fd, src, sizeof(src));
	read(fd, dest, sizeof(dest));
	read(fd, &seat, sizeof(seat));
	close(fd);
	for(int i=0;i<5;i++)
	{
		if(strcmp(src,b[i].src)==0 &&strcmp(dest,b[i].dest)==0)
		{
			strcpy(src,b[i].src);
			strcpy(dest,b[i].dest);
			j=i;
			break;
		}
	}
	if(j==-1) {
		strcpy(message,"No routes available\n");
        status=1;
    }
	else
	{
		if(seat >b[j].seats||seat <=0) {
			strcpy(message,"Not enough seats\n");
            status=1;
        }
		else
		{
			b[j].seats=b[j].seats-seat;	
			bill = seat * b[j].price;
		}
	}
        
	
    printf("Bill generated:%f\n",bill);
    fd=open(PATH, O_WRONLY);
    write(fd, message, sizeof(message));
    write(fd, &status, sizeof(int));
    write(fd, &bill, sizeof(float));
    write(fd, &b[j].seats, sizeof(int));
    close(fd);
    return 0;
}
