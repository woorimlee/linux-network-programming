#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXBUF 1024
#define PORTNUM 3500
int main(int argc, char **argv) {
	int server_sockfd, client_sockfd;
	int client_len, n;
	char buf[MAXBUF];
	struct sockaddr_in clientaddr, serveraddr;
	client_len = sizeof(clientaddr);
	if ((server_sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP )) == -1)
	{
		perror("socket error : ");
		exit(0);
	}
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(PORTNUM);
	bind (server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(server_sockfd, 5);
	while(1)
	{
		memset(buf, 0x00, MAXBUF);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr,
				&client_len);
		printf("New Client Connect: %s\n", inet_ntoa(clientaddr.sin_addr));
		if ((n = read(client_sockfd, buf, MAXBUF)) <= 0)
		{
			close(client_sockfd);
			continue;
		}
		printf("Read Data : %s", buf);
		if (write(client_sockfd, buf, MAXBUF) <=0)
		{
			perror("write error : ");
			close(client_sockfd);
		}
		close(client_sockfd);
	}
	close(server_sockfd);
	return 0;
}
