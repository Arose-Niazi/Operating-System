#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "philisphor.h"
#include <unistd.h>


chopstick chopSticks[MAX_PHILPOSHERS];
philphoser philphosers[MAX_PHILPOSHERS];

void *philphoserStart (void *data)
{
    while(1)
    {
        philphoser phil = *((philphoser *)data);
        int count1, count2;

        printf("Philospher %d has joined the table \n", phil.id);

        printf("Philospher %d is thinking\n", phil.id);
        sleep(random() % 10);
        printf("Philospher %d is hungry\n", phil.id);
        pthread_mutex_lock(&chopSticks[phil.id].taken);
        printf("Philospher %d has taken right chopstick\n", phil.id);
        pthread_mutex_lock(&chopSticks[(phil.id + 1) % MAX_PHILPOSHERS].taken);
        printf("Philospher %d has taken left chopstick\n", phil.id);

        printf("Philospher %d is eating now\n", phil.id);
        sleep(random() % 5);
        printf("Philospher %d has stopped eating\n", phil.id);
        pthread_mutex_unlock(&chopSticks[phil.id].taken);
        pthread_mutex_unlock(&chopSticks[(phil.id + 1) % MAX_PHILPOSHERS].taken);
    }    
    //pthread_barrier_wait(chopSticks[phil.id].taken);
	/*for (count1 = 0;count1 < 10; ++count1 )
	{
		pthread_mutex_lock(&lock); 
		for (count2 = 0; count2 < 10000000; count2++)
			sin(count2*.0000005);
		printf ("%c",x);
		pthread_mutex_unlock(&lock); 
	}*/
}


int main() {
	pthread_t tid[MAX_PHILPOSHERS];
    for(int i=0; i<MAX_PHILPOSHERS; i++)
    {
        philphosers[i].id = i;
        chopSticks[i].id = i;
        int error;
	    if(error = pthread_create((&tid[i]), NULL, philphoserStart, &philphosers[i])) 
		    fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
    }
    
    /* wait for the threads to finish  */
    for(int i=0; i<MAX_PHILPOSHERS; i++)
    {
        int error;
        if(error = pthread_join(tid[i], NULL)) 
            fprintf(stderr, "Failed to join thread \n");
    }
   return 0; 
}
