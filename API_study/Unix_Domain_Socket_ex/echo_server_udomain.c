#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 1024
int main(int argc, char **argv)
{
	int listen_fd, client_fd;
	socklen_t addrlen;
	int readn;
	char buf[MAXLINE];
	struct sockaddr_un client_addr, server_addr;
	if(argc != 2)
	{
		printf("Usage : %s [socket file name]\n", argv[0]);
		return 1;
	}
	if(access(argv[1], F_OK) == 0)
	{
		unlink(argv[1]);
	}
	if( (listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 )
	{
		perror("Error : socket");
		return 0;
	}
	memset((void *)&server_addr, 0x00, sizeof(server_addr));
	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, argv[1], strlen(argv[1]));
	if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("Error : bind");
		return 0;
	}
	if (listen(listen_fd, 5) == -1)
	{
		perror("Error : listen");
		return 1;
	}
	while(1)
	{
		memset((void *)&client_addr, 0x00, sizeof(client_addr));
		printf("accept wait\n");
		client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addrlen);
		while(1)
		{
			if(client_fd == -1)
			{
				printf("Accept Error ");
				return 0;
			}
			memset(buf, 0x00, MAXLINE);
			readn = read(client_fd, buf, MAXLINE);
			if(readn == 0) break;
			printf("==> %s", buf);
			write(client_fd, buf, strlen(buf));
		}
	}
	return 0;
}
