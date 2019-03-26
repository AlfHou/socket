#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "logger.h"

int get_socket_file_desc(char* server_ip, char* port, struct addrinfo** server_info) {
	struct addrinfo hints;
	int status;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	LOG(LOGGER_DEBUG, "Getting address info");
	if ((status = getaddrinfo(server_ip, port, &hints, server_info)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	LOG(LOGGER_DEBUG, "Getting socket");
	int target_socket = socket((*server_info) -> ai_family, (*server_info) -> ai_socktype,
		(*server_info) -> ai_protocol);
	if (target_socket == -1) {
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	LOG(LOGGER_DEBUG, "Got socket %d", target_socket);
	return target_socket;
}
void send_message(int target_socket) {
	char message[512];
	printf("Write message:\n");
	fgets(message, 512, stdin);
	
	LOG(LOGGER_DEBUG, "Sending message");
	if (send(target_socket, message, strlen(message) + 1, 0) == 0) {
		close(target_socket);
		perror("Send");
		exit(EXIT_FAILURE);
	}
	
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: ./client [host] [port]\n");
		exit(EXIT_FAILURE);
	}
	char* server_ip = argv[1];
	char* port = argv[2];
	
	/*Struct that will hold info about the server to connect to like what port
	to use, what the destination ip address is, wheter to use IPv4 or 6 etc.
	*/
	struct addrinfo* server_info;
	
	int target_socket = get_socket_file_desc(server_ip, port, &server_info);
	
	LOG(LOGGER_DEBUG, "Connecting to socket %d", target_socket);
	if (connect(target_socket, server_info -> ai_addr, server_info -> ai_addrlen) == -1) {
		close(target_socket);
		perror("Connect");
		exit(EXIT_FAILURE);
	}

	send_message(target_socket);

	LOG(LOGGER_DEBUG, "Closing socket %d", target_socket);
	close(target_socket);
	LOG(LOGGER_DEBUG, "Free address info");
	freeaddrinfo(server_info);
	return EXIT_SUCCESS;
}

