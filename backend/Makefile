
CC = gcc

SRC = $(wildcard ./src/**/*.c ./src/*.c)
LIB = lib
OBJ = obj
BIN = bin

DYN_SRC = $(wildcard ../ssc/*.c)

# 										v compiler warns about variables that are actually being used
CFLAGS = -m64 -Wall -Wpedantic -Wextra -Wno-unused-variable -march=native -rdynamic -Wno-unused-parameter
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3

LD_FLAGS = -lpthread -rdynamic

debug:
	$(CC) -c $(DYN_SRC) $(SRC) $(CFLAGS) $(DEBUG_FLAGS) -I $(LIB)
	mv *.o $(OBJ)

release:
	$(CC) -c $(DYN_SRC) $(SRC) $(CFLAGS) $(RELEASE_FLAGS) -I $(LIB)
	mv *.o $(OBJ)

build:
	$(CC) $(OBJ)/*.o $(LD_FLAGS) -o $(BIN)/main

run:
	./$(BIN)/main

gdb:
	gdb ./$(BIN)/main

clean:
	rm -f $(OBJ)/*.o
