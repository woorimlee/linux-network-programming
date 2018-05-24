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

	//1. socket()  2. bind()  3. listen()  
	//4. accept()  5. read & write  6. close()

	//sockaddr_in structure contains both an IP address and a protocol port num.
	struct sockaddr_in simpleserver;
	
	if(3 != argc) {
		fprintf(stderr, "Usage : %s <port> <filename>\n", argv[0]);
		exit(1);
	}

	//socket()'s 1st argument is Family(Protocol or address family). AF_INET : TCP/IP
	//2nd is Type(Type of service). SOCK_STREAM : for TCP
	//3rd is Protocol. Typically a zero is used for a default (for a given family & type).
	simplesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(simplesocket == -1) {
		fprintf(stderr, "Couldn't create a socket!\n");
		exit(2);
	}
	else fprintf(stderr, "socket created!\n");

	simpleport = atoi(argv[1]);
	//bzero : set simpleserver area to 0
	bzero(&simpleserver, sizeof(simpleserver));
	simpleserver.sin_family = AF_INET;
	//htonl/htons : Byte order function. 
	//INADDR_ANY : bind to all of our local host's addresses.
	simpleserver.sin_addr.s_addr = htonl(INADDR_ANY);
	simpleserver.sin_port = htons(simpleport);

	//bind()'s 1st argument : socket descriptor
	//2nd : sockaddr struct address
	//3rd : length of the 2nd param
	returnstatus = bind(simplesocket, (struct sockaddr *)&simpleserver, sizeof(simpleserver));
	
	if(returnstatus == 0) fprintf(stderr, "Bind completed!\n");
	else {
	      	fprintf(stderr, "Couldn't bind to address!\n");
		exit(3);
	}

	//listen : we're ready to accept connections.
	returnstatus = listen(simplesocket, 5);
	if (returnstatus == -1) {
	       	fprintf(stderr, "Cannot listen on socket!\n");
	       	close(simplesocket); exit(4); 
	}
	
	//So far we've created our socket, bound it to an address and port, and told our
	//socket that we're ready to receive connection requests.
	//Now we need to actually accept client's requests.

	FILE *fp;
	long filesize = 0;
	unsigned char *filedata;
	unsigned int filesize_n = 0;
	

	while (1) {
		struct sockaddr_in clientName = { 0 };
	       	int simpleChildSocket = 0; 
		int clientNameLength = sizeof(clientName); 
		
		//accept() 1st arg : our socket descriptor
		//2nd & 3rd : locations for storing information about the client.
		simpleChildSocket = accept(simplesocket, (struct sockaddr *)&clientName, &clientNameLength);
		//our program will wait at the accpet() until a connection requests is received from a client.
		//On success, accept() returns a new socket descriptor

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

		filesize_n = htonl(filesize);
		printf("file size : %d\n file size htonl(fsize) : %d\n", filesize, filesize_n);

		send(simpleChildSocket, &filesize_n, sizeof(filesize_n),0);

		filedata = (unsigned char *)malloc(filesize);
		fread(filedata, sizeof(unsigned char), filesize, fp);
	    
		send(simpleChildSocket, filedata, filesize,0);

	       	close(simpleChildSocket);
		free(filedata);
		fclose(fp);
	}
	
	free(filedata);
	close(simplesocket); 
	return 0;
}


