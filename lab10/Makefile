CC=gcc
CFLAGS=-Wall -lm -std=c99
EXEC=lab10
VAL_FILE=valgrind.out

all: clean build

run: clean build
	@./$(EXEC) < g3

build: $(EXEC)

$(EXEC): graph_adj_list.o source.o
	@gcc -o $@ $^ $(CFLAGS) 

%.o: %.c
	@gcc -g -c $^

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)
	@rm -rf *.out

memcheck: clean build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VAL_FILE) --track-origins=yes --verbose ./$(EXEC) < g3