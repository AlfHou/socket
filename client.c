#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT "8777"

	int main(void) {
		struct addrinfo hints;
		struct addrinfo* server_info;
		int status;

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		char* server_ip = "192.168.0.16";

		if ((status = getaddrinfo(server_ip, PORT, &hints, &server_info)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	int target_socket = socket(server_info -> ai_family, server_info -> ai_socktype,
		server_info -> ai_protocol);
	if (target_socket == -1) {
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	if (connect(target_socket, server_info -> ai_addr, server_info -> ai_addrlen) == -1) {
		close(target_socket);
		perror("Connect");
		exit(EXIT_FAILURE);
	}
	char message[512];
	printf("Write message:\n");
	fgets(message, 512, stdin);

	if (send(target_socket, message, strlen(message) + 1, 0) == 0) {
		close(target_socket);
		perror("Send");
		exit(EXIT_FAILURE);
	}

	close(target_socket);
	freeaddrinfo(server_info);
	return EXIT_SUCCESS;
}

