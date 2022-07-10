CC=gcc
.PHONY = clean run memcheck

all: lab06

%.o: %.c
	$(CC) --std=c11 -g -c $<

lab06: checker.o binary_tree.o stack.o queue.o utils.o
	$(CC) $^ -o $@

clean:
	rm -rvf *.o lab06

memcheck: lab06
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab06

run: lab06
	./lab06