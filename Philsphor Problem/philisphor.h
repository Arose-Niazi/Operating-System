#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h> 
#include <pthread.h>

#define PERMISSION              IPC_CREAT|IPC_EXCL|0666
#define SEMKEY                  982133

#define MAX_PHILPOSHERS         5
#define MAX_THINKING_TIME       10
#define MAX_EATING_TIME         5


union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

typedef struct Philosopher
{
    int id;
    int right;
    int left;
} Philosopher;

void think(Philosopher);
void eat(Philosopher);
void takeChops(Philosopher);
void hungry(Philosopher);