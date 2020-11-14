#include <pthread.h>


#define MAX_PHILPOSHERS         5


typedef struct chopstick {
    int id;
    pthread_mutex_t taken;
} chopstick;

typedef struct philphoser {
    int id;
    chopstick left;
    chopstick right;
} philphoser;