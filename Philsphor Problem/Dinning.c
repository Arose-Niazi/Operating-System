// Author : Muhammad Arose Niazi FA18_BSE_010

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

#define MAX_PHILPOSHERS         5
#define MAX_THINKING_TIME       10
#define MAX_EATING_TIME         5

/*
    Types
*/
typedef union semun {
    int              val;  
    struct semid_ds *buf;    
    unsigned short  *array;  
    struct seminfo  *__buf; 
} semun;

typedef struct Philosopher
{
    int id;
    int right;
    int left;
} Philosopher;

/*
    Variables
*/
int semaphoreID;

/*
    Functions
*/
int createSemaphore();
void initializeSemaphore();

void think(Philosopher);
void hungry(Philosopher);
void takeChops(Philosopher);
void eat(Philosopher);
void finish(Philosopher);


/*
    Working
*/

void *start(void *data)
{
	Philosopher philosopher = *((Philosopher *)data);
	think(philosopher);
}

int main()
{
    semaphoreID = createSemaphore();
    initializeSemaphore();

    pthread_t threadID[MAX_PHILPOSHERS];
	Philosopher philosopher[MAX_PHILPOSHERS];
	for(int i=0; i<MAX_PHILPOSHERS; i++)
	{
		philosopher[i].id = i;
		philosopher[i].right = i;
		philosopher[i].left = (i+1) % MAX_PHILPOSHERS;
		int error;

		if(error = pthread_create((&threadID[i]), NULL, start, &philosopher[i])) 
			fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
	}
	
	for(int i=0; i<MAX_PHILPOSHERS; i++)
	{
		int error;
		if(error = pthread_join(threadID[i], NULL)) 
			fprintf(stderr, "Failed to join thread \n");
	}
    return 0;
}

int createSemaphore()
{
    int sID;    	
    sID = semget(SEMKEY, MAX_PHILPOSHERS, (PERMISSION));
    if(sID < 0)
    {
        perror("Cannot create semaphore\n");
        exit(1);
    }
    return sID;
}

void initializeSemaphore()
{
    semun arg;
	unsigned short chopCount[MAX_PHILPOSHERS];
    for(int i = 0; i < MAX_PHILPOSHERS; i++)
        chopCount[i] = 1;
    arg.array = chopCount;
        
    if(semctl(semaphoreID, 0, SETALL, arg) == -1) 
    {
        perror("semctl");
        exit(1);
    }   
}

void think(Philosopher philosopher)
{
	printf("Philosopher number %d is thinking\n", philosopher.id);
    sleep(random() % MAX_THINKING_TIME);
	hungry(philosopher);
}

void hungry(Philosopher philosopher)
{
	printf("Philosopher number %d wants to eat\n", philosopher.id);
	takeChops(philosopher);
}

void takeChops(Philosopher philosopher)
{
	semun arg;
	unsigned short chopCount[2];
    struct sembuf sops[2];

	arg.array = chopCount;

	sops[0].sem_num = philosopher.right;
	sops[1].sem_num = philosopher.left;
    for(int i=0; i<2; i++)
    {
        sops[i].sem_op = -1;
        sops[i].sem_flg = 0;
    }

	if(semop(semaphoreID, sops, 2) < 0)
    {
        perror("Semop error ");
        exit(1);
    }
	    

	eat(philosopher);
}

void eat(Philosopher philosopher)
{
	printf("Philosopher number %d is going to eat\n", philosopher.id);
	sleep(random() % MAX_EATING_TIME);
    finish(philosopher);
}

void finish(Philosopher philosopher)
{
    printf("Philosopher number %d is done eating\n", philosopher.id);
	semun arg;
	unsigned short chopCount[2];
    struct sembuf sops[2];

	arg.array = chopCount;

	sops[0].sem_num = philosopher.right;
	sops[1].sem_num = philosopher.left;
    for(int i=0; i<2; i++)
    {
        sops[i].sem_op = 1;
        sops[i].sem_flg = 0;
    }

	if(semop(semaphoreID, sops, 2) < 0)
    {
        perror("Semop error ");
        exit(1);
    }
	think(philosopher);
}