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
	
	strcpy(countries[0].name, "U.S.A");
	strcpy(countries[0].capital_city, "Washington");
	strcpy(countries[0].currency, "U.S. Dollar");
	countries[0].population = 250000000;
	
	strcpy(countries[1].name, "Japan");
	strcpy(countries[1].capital_city, "Tokiyo");
	strcpy(countries[1].currency, "Yen");
	countries[1].population = 600000;

	strcpy(countries[2].name, "India");
	strcpy(countries[2].capital_city, "New Delhi");
	strcpy(countries[2].currency, "Rupees");
	countries[2].population = 900000000;

for (i=0; i < 3; i++)
	{
		printf("Country %d:\n", i+1);
		printf(" name: %s:\n", countries[i].name);
		printf(" capital city: %s:\n", countries[i].capital_city);
		printf(" currency: %s:\n", countries[i].currency);
		printf(" population: %d:\n", countries[i].population);
	}
//shmctl(shm_id,IPC_RMID,0);	
}
