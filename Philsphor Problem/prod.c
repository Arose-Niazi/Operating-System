#include "philisphor.h"

int sem_id;
struct sembuf sops[MAX_PHILPOSHERS];

void *run(void *data)
{
	Philosopher philosopher = *((Philosopher *)data);
	think(philosopher);
}

int main()
{
	sem_id = semget(SEMKEY, MAX_PHILPOSHERS, 0666);

    if(sem_id < 0)
        perror("Cannot get semaphore\n");
    else
    {
		pthread_t tid[MAX_PHILPOSHERS];
		Philosopher philosopher[MAX_PHILPOSHERS];
		for(int i=0; i<MAX_PHILPOSHERS; i++)
		{
			philosopher[i].id = i;
			philosopher[i].right = i;
			philosopher[i].left = (i+1) % MAX_PHILPOSHERS;
			int error;

			if(error = pthread_create((&tid[i]), NULL, run, &philosopher[i])) 
				fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
		}
		
		for(int i=0; i<MAX_PHILPOSHERS; i++)
		{
			int error;
			if(error = pthread_join(tid[i], NULL)) 
				fprintf(stderr, "Failed to join thread \n");
		}
    }
    return 0;
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
	union semun arg;
	unsigned short chopCount[MAX_PHILPOSHERS];

	arg.array = chopCount;
    if(semctl(sem_id, 0, GETALL, arg) == -1) 
	{
        perror("semctl");
        exit(1);
    }  

	sops[0].sem_num = philosopher.right;
    sops[0].sem_op = 0;
    sops[0].sem_flg = 0;

	sops[1].sem_num = philosopher.left;
    sops[1].sem_op = 0;
    sops[1].sem_flg = 0;

	if(semop(sem_id, sops, 2) < 0)
	    perror("Semop error ");

	takeChops(philosopher);
}

void takeChops(Philosopher philosopher)
{
	union semun arg;
	unsigned short chopCount[MAX_PHILPOSHERS];

	arg.array = chopCount;
    if(semctl(sem_id, 0, GETALL, arg) == -1) 
	{
        perror("semctl");
        exit(1);
    }  

	sops[0].sem_num = philosopher.right;
    sops[0].sem_op = 1;
    sops[0].sem_flg = 0;

	sops[1].sem_num = philosopher.left;
    sops[1].sem_op = 1;
    sops[1].sem_flg = 0;

	if(semop(sem_id, sops, 2) < 0)
	    perror("Semop error ");

	eat(philosopher);
}

void eat(Philosopher philosopher)
{
	printf("Philosopher number %d is going to eat\n", philosopher.id);
	sleep(random() % MAX_EATING_TIME);
    printf("Philosopher number %d is done eating\n", philosopher.id);
	union semun arg;
	unsigned short chopCount[MAX_PHILPOSHERS];

	arg.array = chopCount;
    if(semctl(sem_id, 0, GETALL, arg) == -1) 
	{
        perror("semctl");
        exit(1);
    }  


	sops[0].sem_num = philosopher.right;
    sops[0].sem_op = -1;
    sops[0].sem_flg = 0;

	sops[1].sem_num = philosopher.left;
    sops[1].sem_op = -1;
    sops[1].sem_flg = 0;

	if(semop(sem_id, sops, 2) < 0)
	    perror("Semop error ");

	think(philosopher);
}

