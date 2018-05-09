#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(void) {
	const char * dns = "www.kw.ac.kr";
	struct hostent * host;
	struct in_addr addr;

	host = gethostbyname(dns);
	printf("off n ame : %s\n", host->h_name);
	addr.s_addr = *(u_long *)host->h_addr_list[0];
	printf("ip address : %s\n", inet_ntoa(addr));

}	
