#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

float calculate_bill(int units) {
    //calculate bill
    float amount;
    if (units <=50)
        amount = units * 1;
    else if (units > 51 && units <= 100)
       amount= units * 1.5;
    else if(units > 101 && units <= 200)
        amount= units * 2;
    else if(units > 200)
        amount = units * 3;
    return amount;
}

int main() {
    int fd, fi, units;
    float bill;
    fi= mkfifo("named_pipe", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  // Create the named pipe
    if(fi <0) {
        printf("Named pipe creation failed\n");
        return 1;
    }
    printf("Server is ready.\n");
    fd = open("named_pipe", O_RDONLY);
    read(fd, &units, sizeof(int));
    close(fd);
    printf("Server Received: units=%d\n", units);
    bill = calculate_bill(units);
    fd = open("named_pipe", O_WRONLY);
    write(fd, &bill, sizeof(float));
    close(fd);
    
    return 0;
}
