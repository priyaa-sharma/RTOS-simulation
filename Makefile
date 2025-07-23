CC = gcc
CFLAGS = -Wall -pthread
OBJS = main.o scheduler.o tasks/task1.o tasks/task2.o

all: rtos-sim

rtos-sim: $(OBJS)
	$(CC) $(CFLAGS) -o rtos-sim $(OBJS)

clean:
	rm -f *.o tasks/*.o rtos-sim