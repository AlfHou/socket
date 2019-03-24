CC = gcc
FLAGS = -Wall -Werror -pedantic
BINARIES = server client

.PHONY: clean
all: $(BINARIES)

server: server.c
	$(CC) $^ $(FLAGS) -o $@

client: client.c
	$(CC) $^ $(FLAGS) -o $@

clean:
	rm -rf $(BINARIES)
