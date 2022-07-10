CC=gcc
EXEC=tema3
VAL_FILE=valgrind-result.out
SRC=src
CFLAGS=-Wall -lm -std=c99 -g -I $(SRC)/functions/ -I $(SRC)/utils/ -I $(SRC)/graph/

all: clean build

build: $(EXEC)

$(EXEC): $(SRC)/source.o $(SRC)/utils/utils.o $(SRC)/functions/functions.o $(SRC)/graph/graph.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: $(SRC)/source.c $(SRC)/utils/utils.c $(SRC)/functions/functions.c $(SRC)/graph/graph.c
	$(CC) -c $^

run: build
	./$(EXEC)

clean:
	@rm -rf *.o $(SRC)/*.o $(EXEC) $(SRC)/*/*.o
	@rm -rf $(VAL_FILE)

memcheck: build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VAL_FILE) --track-origins=yes --verbose ./$(EXEC) < tests/inputs/g1e3.in