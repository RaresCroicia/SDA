CC=gcc
CFLAGS=-Wall -lm -std=c99
OFLAGS=-g -c
EXEC=lab12
VAL_FILE=val.log

all: clean build

run: clean build
	./$(EXEC)

build: $(EXEC)

$(EXEC): hash.o source.o
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(OFLAGS) $^

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)
	@rm -rf $(VAL_FILE)

memcheck: clean build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VAL_FILE) --track-origins=yes --verbose ./$(EXEC)
