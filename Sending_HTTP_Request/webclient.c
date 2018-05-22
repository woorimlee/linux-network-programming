#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main (int argc, char *argv[]) {
    int sock = 0;
    int port = 0;
    char *url_Addr;
    struct sockaddr_in web_Client;
    struct in_addr addr;
    struct hostent *host;    

    if (3 != argc) {
	fprintf(stderr, "Usage : %s <URL> <Port>\n", argv[0]);
	exit(2);
    }
    
    url_Addr = argv[1];
    port = atoi(argv[2]);

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == -1) {
	fprintf(stderr, "Couldn't create a socket\n");
	exit(3);
    } else fprintf(stderr, "Socket is created\n");

    host = gethostbyname(url_Addr);
    addr.s_addr = *(u_long *)host->h_addr_list[0];
    printf("ip : %s\n", inet_ntoa(addr));
    bzero(&web_Client, sizeof(web_Client));
    web_Client.sin_family = AF_INET;
    web_Client.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
    web_Client.sin_port = htons(port);
    
    if(connect(sock, (struct sockaddr *)&web_Client, sizeof(web_Client)) == -1) {
	fprintf(stderr, "Couldn't connect!\n");
	close(sock);
	exit(4);
    } else fprintf(stderr, "Connection success\n");

    //body

    close(sock);
    return 0;
}
