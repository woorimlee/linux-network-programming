#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAXBUF 1024

int main (int argc, char *argv[]) {

    int udpSocket;
    int ret = 0;
    int addrlen = 0;
    
    struct sockaddr_in udpServer, udpClient;
    char buf[MAXBUF]; 

    if (argc <2) {
	fprintf(stderr, "Usage : %s <port>\n", argv[0]);
	exit(1);
    }

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(udpSocket == -1) {
	fprintf(stderr, "Couldn't create a socket!\n");
	exit(1);
    }

    else {
	printf("Socket created.\n");
    }

    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    udpServer.sin_port = htons(atoi(argv[1]));

    ret = bind(udpSocket, (struct sockaddr *)&udpServer, sizeof(udpServer));

    if(ret == 0) 
	fprintf(stderr, "Bind completed!\n");
    else {
	fprintf(stderr, "Couldn't bind\n");
	close(udpSocket);
	exit(1);
    }

    while (1)
    {
	addrlen = sizeof(udpClient);
	//TCP는 listen하고, accpet(서버소켓정보, 클라이언트접속소켓구조체, 구조체사이즈)
	//한 뒤 read하는 걸
	ret = recvfrom(udpSocket, buf, MAXBUF, 0, (struct sockaddr*)&udpClient, &addrlen);
	if(ret == -1) 
	    fprintf(stderr, "Couldn't receive message!\n");
	else {
	    printf("Received : %s\n", buf);
	    strcpy(buf, "OK");

	    ret = sendto(udpSocket, buf, strlen(buf)+1, 0, (struct sockaddr*)&udpClient, sizeof(udpClient));
	    if(ret == -1)
		fprintf(stderr, "Couldn't send!\n");
	    else 
		printf("Confirmation sent.\n");
	}
    }

    close(udpSocket);
    return 0;
}

