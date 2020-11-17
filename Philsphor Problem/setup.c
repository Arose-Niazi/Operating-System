#include "philisphor.h"

int main(void)
{
	int sem_id;    	
	union semun arg;
	unsigned short chopCount[MAX_PHILPOSHERS];
    
    sem_id = semget(SEMKEY, MAX_PHILPOSHERS, (PERMISSION));
    if(sem_id < 0)
        perror("Cannot create semaphore\n");
    else
    {
        for(int i = 0; i < MAX_PHILPOSHERS; i++)
        {
            chopCount[i] = 0;
        }
        
	    arg.array = chopCount;
        
        if(semctl(sem_id, 0, SETALL, arg) == -1) 
	    {
            perror("semctl");
            exit(1);
        }   
    }
    return 0;
}
