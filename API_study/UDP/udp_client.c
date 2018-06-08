#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXBUF 1024

int main(int argc, char* argv[]){

    int udpSocket;
    int ret = 0;
    int addrlen;
    struct sockaddr_in udpClient, udpServer;
    char buf[MAXBUF];

    if (argc < 3){
	fprintf(stderr, "Usage : %s <Ip> <Port>\n", argv[0]);
	exit(1);
    }

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(udpSocket == -1) {
	fprintf(stderr, "Couldn't create a socket\n");
	exit(1);
    }
    else 
	printf("Socket created\n");

    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = htonl(INADDR_ANY);
    udpClient.sin_port = 0;

    ret = bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient));

    if(ret == 0)
	fprintf(stderr, "Binding\n");
    else {
	fprintf(stderr, "Couldn't bind\n");
	close(udpSocket);
	exit(1);
    }

    strcpy(buf, "HIHI HIHIHI\n");

    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(argv[1]);
    udpServer.sin_port = htons(atoi(argv[2]));

    ret = sendto(udpSocket, buf, strlen(buf)+1, 0, (struct sockaddr *)&udpServer, sizeof(udpServer));
    if( ret == -1) 
	fprintf(stderr, "Couldn't send\n");
    else {
	printf("Message send.\n");
	addrlen = sizeof(udpServer);
	ret = recvfrom(udpSocket, buf, MAXBUF, 0, (struct sockaddr*)&udpServer, &addrlen);
	if (ret == -1) 
	    fprintf(stderr, "Didn't receive\n");
	else {
	    buf[ret] = 0;
	    printf("Received : %s\n", buf);
	}
    }
    close(udpSocket);
    return 0;
}

