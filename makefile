CC = gcc
FLAGS = -Wall -Werror -pedantic

server: server.c
	$(CC) $^ $(FLAGS) -o $@
