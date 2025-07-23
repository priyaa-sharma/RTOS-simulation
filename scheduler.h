#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef void* (*TaskFunc)(void*);

void init_scheduler();
void add_task(TaskFunc func, const char* name, int priority);
void start_scheduler();
void pause_task(int id);
void resume_task(int id);
void set_task_priority(int id, int new_priority);

#endif