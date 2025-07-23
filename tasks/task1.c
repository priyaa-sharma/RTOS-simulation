#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

extern pthread_mutex_t lock;

void* task1(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        printf("[Task 1] Writing to shared log...\n");
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}