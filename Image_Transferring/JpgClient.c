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
	int receive_filesize = 0;
	unsigned char * filedata;
	struct sockaddr_in simpleServer;
	FILE *fp;
	int n = 1;

	if (4 != argc) {
		fprintf(stderr, "Usage: %s <server> <port> <filename>\n", argv[0]);
		exit(1);
	}
	
	simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (simpleSocket == -1) {
		fprintf(stderr, "Could not create a socket!\n");
		exit(2);
	}else fprintf(stderr, "Socket created!\n");
	
	simplePort = atoi(argv[2]);
	bzero(&simpleServer, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	simpleServer.sin_addr.s_addr = inet_addr(argv[1]);
	simpleServer.sin_port = htons(simplePort);

	returnStatus = connect(simpleSocket,(struct sockaddr *)&simpleServer, sizeof(simpleServer));
	
	if (returnStatus == 0) fprintf(stderr, "Connect successful!\n");
	else {
		fprintf(stderr, "Could not connect to address!\n");
		close(simpleSocket);
		exit(3);
	}
	
	fp = fopen(argv[3], "wb");

	if(recv(simpleSocket,&receive_filesize, sizeof(receive_filesize),0)>0) {
    	    printf("received file size = %d\n", receive_filesize);
	    receive_filesize = ntohl(receive_filesize);
	    printf("ntohl size = %d\n", receive_filesize);
	}
	else {
	    fprintf(stderr, "Couldn't receive file size\n");
	    exit(4);
	}

	filedata = (unsigned char *)malloc(receive_filesize);

	recv(simpleSocket, filedata, receive_filesize,0);


	n = fwrite(filedata, sizeof(unsigned char), receive_filesize, fp);
	printf("n : %d\n",n);
	
	free(filedata);	
	fclose(fp);
	close(simpleSocket);
	return 0;
}
