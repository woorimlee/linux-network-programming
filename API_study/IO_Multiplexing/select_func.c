#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define STDIN 0
#define MAX_LINE 80
int main(int argc, char **argv)
{
	fd_set readfds;
	int fdn;
	char rbuf[MAX_LINE];
	struct timeval timeout;
	FD_ZERO(&readfds);
	FD_SET(STDIN, &readfds);
	while (1)
	{
		timeout.tv_sec = (long)5;
		timeout.tv_usec = 0L;
		printf("> ");
		fflush(stdout);
		fdn = select(STDIN + 1, &readfds, NULL, NULL, &timeout);
		if (fdn == 0)
		{
			printf("\nError : Time Out\n");
		}
		else
		{
			memset(rbuf, 0x00, MAX_LINE);
			read(STDIN, rbuf, MAX_LINE - 1);
			if (strncmp(rbuf, "quit\n", 5) == 0)
				break;
			printf("Your Message : %s", rbuf);
		}
		FD_SET(STDIN, &readfds);
	}
	return 0;
}
