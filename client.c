#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main(void) {
	//Koble til ip addresse x port x
	//Send en pakke med en melding
	//print det den får tilbake
	struct addrinfo hints;
	struct addrinfo* server_info;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 
	char* server_ip = "192.168.0.16";

	if (getaddrinfo(server_ip, "8777", &hints, &server_info) != 0) {
		perror("getaddrinfo");
		return EXIT_FAILURE;
	}
	freeaddrinfo(server_info);
	return EXIT_SUCCESS;
}

