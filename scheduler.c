#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include "scheduler.h"

#define MAX_TASKS 10

typedef struct {
    pthread_t thread;
    char name[50];
    int priority;
    TaskFunc func;
} Task;

Task task_list[MAX_TASKS];
int task_count = 0;
pthread_mutex_t lock;

void init_scheduler() {
    task_count = 0;
    pthread_mutex_init(&lock, NULL);
}

void add_task(TaskFunc func, const char* name, int priority) {
    if (task_count < MAX_TASKS) {
        task_list[task_count].func = func;
        task_list[task_count].priority = priority;
        strncpy(task_list[task_count].name, name, 50);
        task_count++;
    }
}

void start_scheduler() {
    for (int i = 0; i < task_count; i++) {
        pthread_create(&task_list[i].thread, NULL, task_list[i].func, NULL);
        printf("Started %s (priority %d)\n", task_list[i].name, task_list[i].priority);
    }

    for (int i = 0; i < task_count; i++) {
        pthread_join(task_list[i].thread, NULL);
    }
}

void pause_task(int id) {
    pthread_kill(task_list[id].thread, SIGSTOP);
    printf("Paused %s\n", task_list[id].name);
}

void resume_task(int id) {
    pthread_kill(task_list[id].thread, SIGCONT);
    printf("Resumed %s\n", task_list[id].name);
}

void set_task_priority(int id, int new_priority) {
    struct sched_param param;
    param.sched_priority = new_priority;
    pthread_setschedparam(task_list[id].thread, SCHED_FIFO, &param);
    printf("%s priority changed to %d\n", task_list[id].name, new_priority);
}