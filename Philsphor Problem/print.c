#include "philisphor.h"

int sem_id;
struct sembuf sops[MAX_PHILPOSHERS];
pthread_mutex_t takingChops;


int main(int argc, char *argv[])
{
	//int i = atoi(argv[1]);
	//printf("%d - %s", i, argv[1]);
	sem_id = semget(SEMKEY, MAX_PHILPOSHERS, 0666);
    if(sem_id < 0)
        perror("Cannot get semaphore\n");
    else
    {
		union semun arg;
		unsigned short chopCount[MAX_PHILPOSHERS];

		arg.array = chopCount;
		if(semctl(sem_id, 0, GETALL, arg) == -1) 
		{
			perror("semctl");
			exit(1);
		}  
		for(int i=0; i<MAX_PHILPOSHERS; i++)
		{
			printf("Chopstick[%d] = %d\n", i, arg.array[i]);
		}	
	
    }
    return 0;
}
