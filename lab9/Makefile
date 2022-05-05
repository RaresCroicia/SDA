CC=gcc
EXEC=lab9
CFLAGS=-g -Wall -std=c99
VAL_FILE=val.out

build: clean $(EXEC)

$(EXEC): graph.o source.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $<

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)

memcheck: build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VAL_FILE) --track-origins=yes --verbose ./$(EXEC) < graf1
