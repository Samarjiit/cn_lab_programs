/* using shared memory to put array(using pointers) of structure and accessing from shared memory   */
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{
	/* define a structure to be used in the given shared memory segment. */
	struct country
	{
	    char name[30];
	    char capital_city[30];
	    char currency[30];
	    int population;
	};
	struct country* countries;
	int shm_id,i;
	
	shm_id = shmget((key_t)100, 2048, IPC_CREAT |0600);

	countries = (struct country*)(shmat(shm_id, (struct country*)0, 0));

for (i=0; i < 3; i++)
	{
		printf("Country %d:\n", i+1);
		printf(" name: %s:\n", countries[i].name);
		printf(" capital city: %s:\n", countries[i].capital_city);
		printf(" currency: %s:\n", countries[i].currency);
		printf(" population: %d:\n", countries[i].population);
	}
shmctl(shm_id,IPC_RMID,0);	
}
