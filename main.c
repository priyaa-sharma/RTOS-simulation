#include <pthread.h>
#include "scheduler.h"
#include <stdio.h>
#include <string.h>
#include "tasks/task1.h"
#include "tasks/task2.h"

void* cli_thread(void* arg) {
    char cmd[50];
    while (1) {
        printf(">> ");
        scanf("%s", cmd);

        if (strcmp(cmd, "pause1") == 0) pause_task(0);
        else if (strcmp(cmd, "resume1") == 0) resume_task(0);
        else if (strcmp(cmd, "pause2") == 0) pause_task(1);
        else if (strcmp(cmd, "resume2") == 0) resume_task(1);
        else printf("Unknown command\n");
    }
    return NULL;
}

int main() {
    init_scheduler();

    add_task(task1, "Task 1", 1);
    add_task(task2, "Task 2", 2);

    pthread_t cli;
    pthread_create(&cli, NULL, cli_thread, NULL);

    start_scheduler();

    return 0;
}