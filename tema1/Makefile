FLAGS = -lm -g
CC = gcc

all: tema1

build: tema1

tema1: source.o work.o utils.o liste.o
	$(CC) -o $@ $^ $(FLAGS)

source.o: source.c work.c liste.c utils.c
	$(CC) -c $^ $(FLAGS)

clean:
	rm -f tema1 *.o

run: tema1
	./tema1 --c < ex.txt

memcheck:
	valgrind --leak-check=full -s --error-exitcode=2 ./tema1 --c < ex.txt
