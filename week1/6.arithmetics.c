#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int arg, char *args[]) {

    double num1 = atof(args[1]); 
    char operator = args[2][0];
    double num2 = atof(args[3]);

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        double result;
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            default:
                printf("Invalid operator");
                return 1;
        }
        
        printf("Child process result: %.2f\n", result);
    } 
    else {  
        wait(NULL);  
    }

    return 0;
}
