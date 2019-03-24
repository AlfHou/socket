#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(void) {
	//Lytt på port x
	//Hvis den mottar en pakke, print innholdet i pakken osv
	//Send en beskjed tilbake til den ip addressen som sendte noe
	struct addrinfo hints;
	struct addrinfo* server_info;
	int status;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, "8777", &hints, &server_info)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return EXIT_FAILURE;
	}

	int my_socket = socket(server_info -> ai_family, server_info -> ai_socktype,
		server_info -> ai_protocol);
	if (my_socket == -1) {
		perror("Socket");
	}
	if (bind(my_socket, server_info -> ai_addr, server_info -> ai_addrlen) == -1) {
		perror("Bind");
		return EXIT_FAILURE;
	}
	


	freeaddrinfo(server_info);
	return EXIT_SUCCESS;
}
