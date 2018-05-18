#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char * argv[]) {
    int Socket = 0;
    int Port = 0;
    int returnStatus = 0;
    struct sockaddr_in timeServer;
    //time_t server_time = time(NULL);
    //struct tm tm = *localtime(&server_time);

    if (argc != 2) {
	fprintf(stderr, "Usage : %s <port>\n", argv[0]);
	exit(1);
    }

    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(Socket == -1) {
	fprintf(stderr, "Could not create a socket!\n");
	exit(2);
    }
    else fprintf(stderr, "socket created!\n");

    Port = atoi(argv[1]);
    
    bzero(&timeServer, sizeof(timeServer));    
    timeServer.sin_family = AF_INET;
    timeServer.sin_addr.s_addr = htonl(INADDR_ANY);
    timeServer.sin_port = htons(Port);

    returnStatus = bind(Socket, (struct sockaddr *)&timeServer, sizeof(timeServer));
    if(returnStatus == 0) fprintf(stderr, "Bind Completed!\n");
    else {
	fprintf(stderr, "Couldn't bind to address!\n");
	close(Socket);
	exit(3);
	}

    returnStatus = listen(Socket, 5);
    if (returnStatus == -1) {
	fprintf(stderr, "Couldn't listen on socket!\n");
	close(Socket);
	exit(4);
    }

   while(1) { 
	struct sockaddr_in clientName = { 0 };
	int simpleChildSocket = 0;
	int clientNameLength = sizeof(clientName);

	simpleChildSocket = accept(Socket, (struct sockaddr *)&clientName, &clientNameLength);

	if(simpleChildSocket == -1) {
	    fprintf(stderr, "Couldn't accept connection!\n");
	    close(Socket);
	    exit(5);
	}

	time_t server_time = time(NULL);
	struct tm tm = *localtime(&server_time);

	send(simpleChildSocket, &tm, sizeof(tm), 0);
	printf("Sending my tm\n");

	close(simpleChildSocket);
    }

    close(Socket);
    return 0;
}
