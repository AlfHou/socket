CC = gcc
FLAGS = -Wall -Werror -pedantic -Wno-gnu-zero-variadic-macro-arguments 
BINARIES = server client

.PHONY: clean
all: $(BINARIES)

server: server.c logger.c
	$(CC) $^ $(FLAGS) -o $@

client: client.c logger.c
	$(CC) $^ $(FLAGS) -o $@

clean:
	rm -rf $(BINARIES)
