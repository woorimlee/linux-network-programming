#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#define MAXLINE 1024
#define PORTNUM 3500
int main(int argc, char **argv) {
	int listen_fd, client_fd;
	pid_t pid;
	socklen_t addrlen;
	int readn;
	char buf[MAXLINE];
	struct sockaddr_in client_addr, server_addr;
	if( (listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return 1;
	}
	memset((void *)&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORTNUM);
	if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==-1)
	{
		perror("bind error");
		return 1;
	}
	if(listen(listen_fd, 5) == -1)
	{
		perror("listen error");
		return 1;
	}
	signal(SIGCHLD, SIG_IGN);
	while(1)
	{
		addrlen = sizeof(client_addr);
		client_fd = accept(listen_fd,
				(struct sockaddr *)&client_addr, &addrlen);
		if(client_fd == -1)
		{
			printf("accept error\n");
			break;
		}
		pid = fork();
		if(pid == 0)
		{
			memset(buf, 0x00, MAXLINE);
			while((readn = read(client_fd, buf, MAXLINE)) > 0)
			{
				printf("Read Data %s : %s",
						inet_ntoa(client_addr.sin_addr),
						buf);
				write(client_fd, buf, strlen(buf));
				memset(buf, 0x00, MAXLINE);
			}
			close(client_fd);
			return 0;
		}
	}
	return 0;
}
