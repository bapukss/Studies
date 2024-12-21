CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c Skorowidz.c DynamicArray.c
OBJ = main.o Skorowidz.o DynamicArray.o

EXEC = prog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c DynamicArray.h Skorowidz.h
	$(CC) $(CFLAGS) -c main.c

Skorowidz.o: Skorowidz.c Skorowidz.h
	$(CC) $(CFLAGS) -c Skorowidz.c

DynamicArray.o: DynamicArray.c DynamicArray.h
	$(CC) $(CFLAGS) -c DynamicArray.c

clean:
	rm -f $(OBJ) $(EXEC)