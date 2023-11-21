#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

float calculate_si(int amount, int tenure) {
    //calculate simple interest
    float si;
    if (tenure <=1)
        si = amount * tenure * 0.05;
    else if (tenure > 1 && tenure <= 2)
       si= amount * tenure * 0.06;
    else if(tenure > 2 && tenure <= 3)
        si= amount * tenure * 0.07;
    else if(tenure > 3)
        si = amount * tenure * 0.08;
    return si;
}

int main() {
    int fd, fi;
    int amount, tenure;
    float si, maturity;
    fi= mkfifo("named_pipe", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  // Create the named pipe
    if(fi <0) {
        printf("Named pipe creation failed\n");
        return 1;
    }
    printf("Server is ready.\n");
    fd = open("named_pipe", O_RDONLY);
    read(fd, &amount, sizeof(int));
    read(fd, &tenure, sizeof(int));
    close(fd);
    printf("Server Received: amount=%d\tTenure=%d\n", amount, tenure);
    si = calculate_si(amount, tenure);
    fd = open("named_pipe", O_WRONLY);
    maturity = amount + si;
    write(fd, &si, sizeof(float));
    write(fd, &maturity, sizeof(float));
    close(fd);
    
    return 0;
}
