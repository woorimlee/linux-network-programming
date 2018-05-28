#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char **argv) {
	if( mkfifo("/tmp/myfifo_r", S_IRUSR|O_RDONLY) == -1)
	{
		return 1;
	}
	printf("Success Read Only Named PIPE : /tmp/myfifo_r\n");
	if( mkfifo("/tmp/myfifo_s", S_IRUSR|O_WRONLY) == -1)
	{
		return 1;
	}
	printf("Success Read Only Named PIPE : /tmp/myfifo_s\n");
	return 0;
}
