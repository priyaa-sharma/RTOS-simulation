#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

extern pthread_mutex_t lock;

void* task2(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        printf("[Task 2] Crunching numbers...\n");
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
    return NULL;
}