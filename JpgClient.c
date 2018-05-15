#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;
	char buffer[256] = "";
	struct sockaddr_in simpleServer;
	FILE *fp;

	if (4 != argc) {
		fprintf(stderr, "Usage: %s <server> <port> <filename>\n", argv[0]);
		exit(1);
	}
		simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (simpleSocket == -1) {
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}else {
		fprintf(stderr, "Socket created!\n");
	}
	simplePort = atoi(argv[2]);

	bzero(&simpleServer, sizeof(simpleServer));
	
	simpleServer.sin_family = AF_INET;
	
	simpleServer.sin_addr.s_addr = inet_addr(argv[1]);
	
	simpleServer.sin_port = htons(simplePort);
	
	returnStatus = connect(simpleSocket,
			(struct sockaddr *)&simpleServer,
			sizeof(simpleServer));
	
	if (returnStatus == 0) {
		fprintf(stderr, "Connect successful!\n");
	
	}else {
		fprintf(stderr, "Could not connect to address!\n");
		close(simpleSocket);
		exit(1);
	}

	fp = fopen(argv[3], "wb");

	returnStatus = read(simpleSocket, buffer, sizeof(buffer));
	
	if ( returnStatus > 0 ) {
		printf("%d: %s", returnStatus, buffer);
	}
	else {
		fprintf(stderr, "Return Status = %d \n", returnStatus);
	}

	fwrite(buffer, sizeof(unsigned char), sizeof(buffer), fp);
	fclose(fp);
	close(simpleSocket);
	return 0;
}
