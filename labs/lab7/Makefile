CC=gcc
.PHONY = clean run memcheck

all: lab07

%.o: %.c
	$(CC) --std=c11 -g -c $<

lab07: checker.o trie.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rvf *.o lab07

memcheck: lab07
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab07
	$(MAKE) clean

run: lab07
	./lab07
	$(MAKE) clean