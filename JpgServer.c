#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int simplesocket = 0;
	int simpleport = 0;
	int returnstatus = 0;

	struct sockaddr_in simpleserver;
	
	if(3 != argc) {
		fprintf(stderr, "Usage : %s <port> <filename>\n", argv[0]);
		exit(1);
	}

	simplesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(simplesocket == -1) {
		fprintf(stderr, "Couldn't create a socket!\n");
		exit(2);
	}
	else fprintf(stderr, "socket created!\n");

	simpleport = atoi(argv[1]);

	bzero(&simpleserver, sizeof(simpleserver));
	simpleserver.sin_family = AF_INET;
	simpleserver.sin_addr.s_addr = htonl(INADDR_ANY);
	simpleserver.sin_port = htons(simpleport);

	returnstatus = bind(simplesocket, (struct sockaddr *)&simpleserver, sizeof(simpleserver));
	
	if(returnstatus == 0) fprintf(stderr, "Bind completed!\n");
	else {
	      	fprintf(stderr, "Couldn't bind to address!\n");
		exit(3);
	}
	if (returnstatus == -1) {
	       	fprintf(stderr, "Cannot listen on socket!\n");
	       	close(simplesocket); exit(1); 
	}
	while (1) {
		FILE *fp;
		long filesize = 0;	
		unsigned char *filedata;

		struct sockaddr_in clientName = { 0 };
	       	int simpleChildSocket = 0; 
		int clientNameLength = sizeof(clientName); 
		
		simpleChildSocket = accept(simplesocket, (struct sockaddr *)&clientName, &clientNameLength);
	       	if (simpleChildSocket == -1) {
		       	fprintf(stderr, "Cannot accept connections!\n");
		       	close(simplesocket);
		       	exit(4); 
		}

		if ((fp = fopen(argv[2], "rb")) ==NULL) {
			fprintf(stderr, "File Open Error!\n");
			exit(5);
		}

		fseek(fp, 0L, SEEK_END);
		filesize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		filedata = (unsigned char *)malloc(filesize);

		fread(filedata, sizeof(unsigned char), filesize, fp);

		write(simpleChildSocket, filedata, filesize);
	       	close(simpleChildSocket);
		free(filedata);
		fclose(fp);
	}
	close(simplesocket); 
	return 0;
}


