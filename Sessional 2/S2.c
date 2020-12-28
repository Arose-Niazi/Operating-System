// Author : Arose Niazi FA18_BSE_010
/*
    Includes
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h> 
#include <pthread.h>

/*
    Defines
*/
#define PERMISSION              IPC_CREAT|IPC_EXCL|0666
#define SEMKEY                  982133

#define MAX_CUSTOMERS         		3
#define MAX_BASKETS				3
#define MAX_LOAFS				3

#define MAX_BAKING_TIME       		3	
#define MAX_EATING_TIME         		6

/*
    Types
*/
typedef union semun {
    int              val;  
    struct semid_ds *buf;    
    unsigned short  *array;  
    struct seminfo  *__buf; 
} semun;

/*
    Variables
*/
int semaphoreID;


/*
    Working
*/

void *baker (void *data)
{
	union semun arg;
	struct sembuf sops[MAX_BASKETS];  
    	sops[0].sem_num = 0;
    	sops[0].sem_flg = 0; 	
    	
	while(1)
	{
		printf ("Baker wants to bake.\n");

		sops[0].sem_op = 0; //Checking for empty basket!	
		if(semop(semaphoreID, sops, 1) < 0)
	    	perror("Semop error");
			
		printf ("Basket is empty, baker is going to bake.\n");
		sleep(MAX_BAKING_TIME);

		sops[0].sem_op = 3; //Filled the basket.
		if(semop(semaphoreID, sops, 1) < 0)
	        perror("Semop error");

		printf ("Baker is done baking.\n");	
	}
}

void *customer (void *data)
{
	int id = *((int *) data);
	
	union semun arg;
	struct sembuf sops[MAX_BASKETS];  
	
	sops[0].sem_num = 0;
    	sops[0].sem_flg = 0; 

	while(1)
	{
		printf ("Customer number %d wants one bread.\n",id);
		sops[0].sem_op = -1; //Removing 1 from the basket.

		if(semop(semaphoreID, sops, 1) < 0)
			perror("Semop error");
		
		printf ("Customer number %d eating...\n",id);
		sleep((random() % MAX_EATING_TIME) + 1);
		
		printf ("Customer number %d done eating\n",id);
	}
}



int main(int argc, char *argv[]) {
	pthread_t c_tid[MAX_CUSTOMERS];
	pthread_t b_tid;

	int error;
	union semun arg;
	unsigned short baskets_data[MAX_BASKETS];

	semaphoreID = semget(SEMKEY, 1, (PERMISSION));
    	if(semaphoreID < 0)
		perror("Cannot create semaphore\n");
	else
	{
        	baskets_data[0] = 0;
	    	arg.array = baskets_data;
        	if (semctl(semaphoreID, 0, SETALL, arg) == -1) 
	    	{
            		perror("semctl");
            		exit(1);             
		}   
		
	}

    	if(error = pthread_create((&b_tid), NULL, baker, NULL)) 
		fprintf(stderr, "Failed to create bakers thread: %s\n", strerror(error));

	int customersIDs[MAX_CUSTOMERS];
	for(int i = 0; i < 3; i++)
	{
		customersIDs[i] = i+1;
		if (error = pthread_create((&c_tid[i]), NULL, customer, &customersIDs[i])) 
			fprintf(stderr, "Failed to create customers thread: %s\n", strerror(error));
	}

	if (error = pthread_join(b_tid, NULL)) 
        fprintf(stderr, "Failed to join bakers thread \n");

	for(int i = 0; i < 3; i++)
	{
		if (error = pthread_join(c_tid[i], NULL)) 
        	fprintf(stderr, "Failed to join customers thread \n");
	}


   return 0; 
}

