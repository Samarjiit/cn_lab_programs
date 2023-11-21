//Ronson Danthy
//220970003

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd, fi, cust_no, units;
    float bill;
    printf("client: Enter customer number: ");
    scanf("%d", &cust_no);
    printf("client: Enter units consumed: ");
    scanf("%d", &units);
    fd = open("named_pipe", O_WRONLY);
    if(fd < 0) {
        printf("Opening pipe failed\n");
        return 1;
    }
    write(fd, &units, sizeof(int));
    close(fd);

    fd = open("named_pipe", O_RDONLY);
    read(fd, &bill, sizeof(float));
    close(fd);
    printf("Client: response from server\n");
    printf("Bill generated for customer no %d is: %f\n", cust_no, bill);
    fi =unlink("named_pipe");
    if(fi <0) {
        printf("Named pipe deletion failed\n");
        return 1;
    }

    return 0;
}
