CC=gcc
.PHONY = clean run memcheck

all: lab08

%.o: %.c
	$(CC) --std=c11 -g -c $<

lab08: checker.o heap.o priority_queue.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rvf *.o lab08

memcheck: lab08
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab08
	$(MAKE) clean

run: lab08
	./lab08
	$(MAKE) clean