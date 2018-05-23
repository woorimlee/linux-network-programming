#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1024
#define PORTNUM 3500
#define ADDR "127.0.0.1"
int main(int argc, char **argv) {
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[MAXLINE];
	char rbuf[MAXLINE];
	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("error :");
		return 1;
	}
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ADDR);
	serveraddr.sin_port = htons(PORTNUM);
	client_len = sizeof(serveraddr);
	if (connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len) < 0)
	{
		perror("connect error :");
		return 1;
	}
	memset(buf, 0x00, MAXLINE);
	read(0, buf, MAXLINE);
	if (write(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("write error : ");
		return 1;
	}
	memset(buf, 0x00, MAXLINE);
	if (read(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("read error : ");
		return 1;
	}
	close(server_sockfd);
	printf("read : %s", buf);
	return 0;
}
