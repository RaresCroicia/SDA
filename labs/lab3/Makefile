CC=gcc

all: lab03

%.o: %.c
	$(CC) -g -c $<

lab03: lab03.o lab03_checker.o
	$(CC) $^ -o $@

clean:
	rm -rvf *.o lab03

run:
	./lab03

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab03
