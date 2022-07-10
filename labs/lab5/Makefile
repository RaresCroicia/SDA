CC=gcc
.PHONY = clean run memcheck

all: lab05

%.o: %.c
	$(CC) --std=c11 -g -c $<

lab05: checker.o lab05.o stack.o queue.o list.o
	$(CC) $^ -o $@

clean:
	rm -rvf *.o lab05

memcheck: lab05
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab05

run: lab05
	./lab05