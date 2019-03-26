#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define MYPORT "8777"
int get_port(struct addrinfo** server_info) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int status;
	if ((status = getaddrinfo(NULL, MYPORT, &hints, server_info)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	int my_socket = socket((*server_info) -> ai_family, (*server_info) -> ai_socktype,
		(*server_info) -> ai_protocol);
	if (my_socket == -1) {
		perror("Socket");
		exit(EXIT_FAILURE);
	}
	if (bind(my_socket, (*server_info) -> ai_addr, (*server_info) -> ai_addrlen) == -1) {
		close(my_socket);
		perror("Bind");
		exit(EXIT_FAILURE);
	}
	return my_socket;

}
void get_packet(int my_socket) {
	struct sockaddr_storage incoming_packet;
	int new_socket_descriptor;
	
	socklen_t packet_size = sizeof(incoming_packet);
	new_socket_descriptor = accept(my_socket, (struct sockaddr*) &incoming_packet, &packet_size);  
	if (new_socket_descriptor == -1) {
		close(my_socket);
		perror("Accept");
		exit(EXIT_FAILURE);
	}
	char buffer[512];
	memset(buffer, 0, sizeof(char)); 

	if (recv(new_socket_descriptor, buffer, sizeof(buffer), 0) == -1) {
		close(new_socket_descriptor);
		close(my_socket);
		perror("Receive");
		exit(EXIT_FAILURE);
	}
	printf("%s", buffer);
	close(new_socket_descriptor);

}
int main(void) {
	struct addrinfo* server_info;

	int my_socket = get_port(&server_info);

	printf("Listening...\n");
	if (listen(my_socket, 10) != 0) {
		close(my_socket);
		perror("Listen");
		exit(EXIT_FAILURE);
	}
	get_packet(my_socket);
	close(my_socket);
	freeaddrinfo(server_info);
	return EXIT_SUCCESS;
}
