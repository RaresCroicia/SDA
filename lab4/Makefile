CC=gcc
.PHONY = clean run memcheck

all: lab04

%.o: %.c
	$(CC) --std=c11 -g -c $<

lab04: lab04.o checker.o
	$(CC) $^ -o $@

clean:
	rm -rvf *.o lab04

memcheck: lab04
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab04

run: lab04
	./lab04