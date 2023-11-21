#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <math.h>

int main() {

    char states[4][20] = {"Karnataka","Tamilnadu","Kerala","Goa"};
    char capital[4][20] = {"Banglore","Chennai","Thiruvananthapuram","Panaji"};

    void *shared_memory;
    char *data;
    char response[100]="RESPONSE : ";
    int shmid;

    shmid = shmget((key_t)1122, sizeof(100), 0666 | IPC_CREAT);
    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("Server attached at %p\n", shared_memory);

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
