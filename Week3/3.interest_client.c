//Ronson Danthy
//220970003

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd, amount, tenure;
    float si, maturity;
    printf("client: Enter Deposite amount: ");
    scanf("%d", &amount);
    printf("client: Enter tenure: ");
    scanf("%d", &tenure);
    fd = open("named_pipe", O_WRONLY);
    if(fd < 0) {
        printf("Opening pipe failed\n");
        return 1;
    }
    write(fd, &amount, sizeof(int));
    write(fd, &tenure, sizeof(int));
    close(fd);

    fd = open("named_pipe", O_RDONLY);
    read(fd, &si, sizeof(float));
    read(fd, &maturity, sizeof(float));
    close(fd);
    printf("Client: response from server\n");
    printf("Interest earned: %f\nMaturity amount is: %f\n", si,maturity);
    unlink("named_pipe");
    return 0;
}
