#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <math.h>

int main() {

    char states[4][20] = {"Maharashtra","Andhra","Rajasthan","Karnataka"};
    char capital[4][20] = {"Mumbai","Hydrabad","Jaipur","Banglore"};
    key_t key=1234;
    void *shared_memory;
    char *data;
    char response[100];
    int shmid;

    shmid = shmget(key, sizeof(100), 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);
  

    data = (char *)shared_memory;

    printf("Waiting for client to send an data...\n");
    while (*data == 0) {
        sleep(1);
    }
    char *user_data = data;
    printf("Received data from client: %s\n", user_data);


    int index = -1;
    for(int i=0; i<4; i++){
        if(strcmp(user_data, states[i])==0){
            index = i;
            break;
        }
        if(strcmp(user_data, capital[i])==0){
            index = i;
            break;
        }
    }
    
    if(index != -1){
        strcat(response, states[index]);
        
        strcat(response, " - ");
        strcat(response,capital[index]);
        strcpy((char *)shared_memory, response);
        printf("\nSent response to client: %s\n", response);
    } else {
        strcpy((char *)shared_memory, "NO MATCH FOUND");
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
