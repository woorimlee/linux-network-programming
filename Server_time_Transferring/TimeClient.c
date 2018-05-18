#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

int main (int argc, char *argv[]) {
    int Socket = 0;
    int Port = 0;
    int returnStatus = 0;
    struct sockaddr_in timeServer;
    struct tm recv_tm;

    if(3 != argc) {
	fprintf(stderr, "Usage : %s <server> <port>\n", argv[0]);
	exit(1);
    }

    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (Socket == -1) {
	fprintf(stderr, "Couldn't create a socket!\n");
	exit(2);
    }else fprintf(stderr, "Socket created!\n");

    Port = atoi(argv[2]);
    bzero(&timeServer, sizeof(timeServer));
    timeServer.sin_family = AF_INET;
    timeServer.sin_addr.s_addr = inet_addr(argv[1]);
    timeServer.sin_port = htons(Port);

    returnStatus = connect(Socket, (struct sockaddr *)&timeServer, sizeof(timeServer));
    if(returnStatus == 0) fprintf(stderr, "Connection success!\n");
    else {
	fprintf(stderr, "Couldn't connect to the address!\n");
	close(Socket);
	exit(3);
    }

    if(recv(Socket, &recv_tm, sizeof(recv_tm),0) > 0 ) {
	printf("Receive server time\n");
	printf("Server time : %d-%d-%d %d:%d:%d\n", recv_tm.tm_year+1900,recv_tm.tm_mon+1, recv_tm.tm_mday, recv_tm.tm_hour, recv_tm.tm_min, recv_tm.tm_sec);
    }
    else {
	fprintf(stderr, "Couldn't receive server time!\n");
	close(Socket);
	exit(4);
    }

    close(Socket);
    return 0;
}



	

