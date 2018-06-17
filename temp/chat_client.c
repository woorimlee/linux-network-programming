#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>

#define BUFSIZE 1024
#define NAME 20

//사용자 이름을 저장할 곳이다.
char name[NAME];

//클라이언트는 메시지를 비동기적으로 송신 & 수신해야 하니 쓰레드로 운영하였다.
//송신 & 수신용 쓰레드들이 사용하는 함수다.
void *send_func(void *sock_fd);
void *recv_func(void *sock_fd);

int main(int argc, char* argv[]){

        int sock;
	    pthread_t send_thread, recv_thread;
	        char buf[BUFSIZE];
		    struct sockaddr_in serv_addr;

		        if(argc!=4){
			            printf("Usage : %s <IP> <port> <name>\n", argv[0]);
				            exit(1);
					        }

			//인자로 받은 name을 sprintf 함수를 써서 name에 넣어준다. (사실 다른 form으로 변형시켜주느라 sprintf를 썼었다가, 그 폼을 지워서 남게된 함수 사용 흔적이다.)
			    sprintf(name, "%s", argv[3]);

			    //서버에 연결하기 위해 소켓을 생성한다.
			        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				    if(sock == -1)
					        perror("socket");

				    //메모리 초기화 및 sockaddr_in 구조체를 채우는 작업.
				        memset((void *)&serv_addr, 0x00, sizeof(serv_addr));
					    serv_addr.sin_family=AF_INET;
					        serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
						    serv_addr.sin_port=htons(atoi(argv[2]));

						    //위의 구조체 정보와 생성한 소켓을 갖고 서버에 접속한다.
						        if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
							            perror("connect");
							    else
								        printf("연결 됨\n");

							    //서버 접속에 성공하면 자신의 ID 먼저 전송한다.
							        send(sock, name, sizeof(name), 0);

								//그 후 수신용 송신용 스레드를 각각 하나씩 생성해 구현한다.
								    pthread_create(&send_thread, NULL, send_func, &sock);
								        pthread_create(&recv_thread, NULL, recv_func, &sock);
									//정상적으로 리소스 반환을 시켜주기 위해 join 함수를 호출한다.
									    pthread_join(send_thread, NULL);
									        pthread_join(recv_thread, NULL);

										    close(sock);
										        return 0;
}

//송신용 함수.
void *send_func(void *sock_fd){
        int sock = *(int *)sock_fd;
	    char named_msg[BUFSIZE+NAME];
	        char msg[BUFSIZE];

		//메세지 보내기전 항시 메모리 초기화
		    while(1){
			        memset((void *)msg, 0x00, BUFSIZE);
				        memset((void *)named_msg, 0x00, BUFSIZE+NAME);
					//stdin으로부터 입력된 내용을 msg에 저장하고
					        read(0, msg, BUFSIZE);
						//@exit가 아니면
						        if(!strcmp(msg, "@exit\n")) {
							                close(sock);
									            exit(0);
										            }
							//자신의 이름과 메시지 내용을 합쳐서
							        sprintf(named_msg,"[%s] %s", name, msg);
								// 서버에게 전송한다.
								        send(sock, named_msg, strlen(named_msg), 0);
									    }

		        exit(0);
}

void *recv_func(void *sock_fd) {
        int sock = *(int *)sock_fd;
	    int recv_ret = 1;
	        char msg[BUFSIZE];

		//msg 사용전 항시 초기화
		    while(recv_ret > 0){
			        memset((void *)msg, 0, sizeof(msg));
				//서버로부터 전송되어져 온 메시지를 수신하기 위한 recv
				        recv(sock, msg, BUFSIZE, 0);
					        printf("recv : %s", msg);
						    }

		        exit(0);
}
