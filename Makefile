CC=gcc
CFLAGS=-O3 -ansi -Wall
LIBS=-lm
BIN=./graph
SOURCE=graph.c

all: $(BIN)

caracol: $(SOURCE)
	$(CC) -o $(BIN) $(CFLAGS) $(SOURCE) $(LIBS)

clean:
	rm -f $(BIN)

run: $(BIN)
	$(BIN)

test:
	@./runtests.sh
