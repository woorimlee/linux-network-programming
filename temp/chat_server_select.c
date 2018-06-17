#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXUSER 1000
#define MAXLINE 1024
#define NAME 20
#define PORT 3500
#define MEM_SET(a) memset((void *)a, 0x00, sizeof(a))

int main () {
        int listen_sock, accept_sock;
	    int client_addr_len;
	        int max_sock_fd;
		    int select_ret;
		        int chatter = 0;
			    //골뱅이 문자 위치 찾기 위한 포인터
			    char * at_ptr;
			        char welcome_msg[MAXLINE];
				    int client_array[MAXUSER] = {0};
				        char name[MAXUSER][NAME];

					    char buf[MAXLINE];
					        struct sockaddr_in server_addr, client_addr;
						    fd_set fds_read, fds_backup;

						    //서버 리슨용 소켓 생성
						        if((listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
							            fprintf(stderr, "socket() error\n");
								            return -1;
									        }

							//메모리 초기화 및 소켓 구조체에 정보 추가
							    memset((void*)&server_addr, 0x00, sizeof(server_addr));
							        server_addr.sin_family = AF_INET;
								    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
								        server_addr.sin_port = htons(PORT);

									//추가한 정보로 소켓에 바인드
									    if(bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
										        perror("bind() error");
											        return -1;
												    }

									    //리슨 큐 생성
									        if((listen(listen_sock, 5)) == -1) {
										            fprintf(stderr, "listen() error\n");
											            return -1;
												        }

										    //fd_set 초기화
										    FD_ZERO(&fds_read);
										        //listen_sock의 fd를 fd_set에 세팅한다.
										        FD_SET(listen_sock, &fds_read);
											    //select() 함수에 최대 값을 넣어주기 위해 쓴 변수
											    max_sock_fd = listen_sock;

											        while(1) {
												            //select함수를 쓰면 기존의 fd_set이 자기 상태를 보존하지 못하기 때문에 복사본을 하나 만들어서 사용함.
												            fds_backup = fds_read;
													            //printf("Waiting [%d]", max_sock_fd);

													            //select함수 인자 순서대로, fd 값중 가장 큰 값, read 이벤트 확인, write 확인, execpt 확인, timeout 값. NULL은 무한 대기
													            select_ret = select(max_sock_fd + 1, &fds_backup, (fd_set *)0, (fd_set *)0, NULL);

														            //listen_sock의 fd가 read 이벤트가 발생했다면? accept 해줘야지
														            if(FD_ISSET(listen_sock, &fds_backup)) {
																                client_addr_len = sizeof(client_addr);
																		                accept_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
																				                //accept 한 클라이언트 소켓 fd를 등록해야지
																				                FD_SET(accept_sock, &fds_read);

																							//접속이 된 클라이언트들을 저장할 배열이다. 
																						                client_array[accept_sock] = accept_sock;

																									//클라이언트가 전송할 이름을 수신해준다.
																								                recv(accept_sock, name[accept_sock], NAME, 0);
																											//접속 요청한 클라이언트에게만 메시지 전송
																										                send(client_array[accept_sock], "[서버] 채팅 접속 완료\n", sizeof("[서버] 채>팅 접속 완료\n"), 0);

																												                printf("check name : %s\n", name[accept_sock]);
																														                //만약 accept 한 소켓 fd가 기존의 max값보다 크다면 교체
																														                if(accept_sock > max_sock_fd)
																																                        max_sock_fd = accept_sock;
																																                sprintf(welcome_msg, "[%s]가 접속했습니다.\n", name[accept_sock]);
																																		                //접속중이었던 나머지 모든 프로세스들에게 접속자 알림 메시지를 전송
																																			for(int i = 0; i <= max_sock_fd; i++) {
																																			                        if(client_array[i] != client_array[accept_sock])
																																						                            send(client_array[i], welcome_msg, sizeof(welcome_msg), 0);
																																						                }
																																			                //accept 과정 끝났고, 다시 처음으로 돌아가서 복사본 생성~select 확인 과정을 >거친다. 클라이언트가 메세지 보냈는지 확인해야하니까 or 새로운 accept 요청이 있는지 확인해야 >하니까.
																																			                printf("[%d] Accept OK\n", accept_sock);
																																					                continue;
																																							        }

															            //accept 요청은 없었구나
															            for (int check_fd = 0; check_fd <= max_sock_fd; check_fd++) { //select의 단점. sock fd가 크면 sock 갯수랑 상관없이 쓸데없이 for 루프를 돌아야함.
																	            //어떤 fd 값이 select read 이벤트 검사한 곳에서 이벤트 요청한게 확인 됐다면
																	            if (FD_ISSET(check_fd, &fds_backup)) {
																			                MEM_SET(buf);
																					                if((read(check_fd, buf, MAXLINE)) <= 0) {
																							                        //연결 끊겨서 접속된 부분. @exit를 호출한 것은 따로 처리하지 않아도 상대방 연결이 끊겼다는 기준으로 생각해보면, 같은 루틴으로 한 번에 처리 가능.
																							                        //뒷정리 작업
																								        client_array[check_fd] = 0;
																									                    memset((void *)name[check_fd], 0x00, sizeof(name[check_fd]));
																											                        close(check_fd);
																														                    FD_CLR(check_fd, &fds_read);
																																                        printf("[%d] 연결 끊김\n", client_array[check_fd]);
																																			                }

																							                else {
																										        // 만약 전송된 문자에 @가 있다면(@show를 예상중) at_ptr에 해당 위치 반환하고
																									                        at_ptr = strchr(buf, '@');
																												                    if (at_ptr != NULL)  {
																															                        if(strcmp(at_ptr, "@show\n") == 0) { //@show인지 확인하고
																																		                                if(client_array[check_fd] == check_fd);//fd값 확인하고
																																						                            for (int i = 0; i <= max_sock_fd; i++) { //접속중인 모든 프로세스들의 네임을 전송한다.
																																										                                    if(name[i][0] != '\0') {
																																															                                        printf("User : %s\n", name[i]);
																																																				                                        send(client_array[check_fd], name[i], sizeof(name[i]), 0);
																																																									                                    }
																																														                                }
																																									                            }
																																		                    }
																														    //서버 확인용
																														                        printf("Read : %s" ,buf);
																																	//일반적인 메시지 처리 루틴. 모든 클라이언트에 클라이언트로부터 수신된 메시지를 전송해준다.
																																	                    for(int i = 0; i <= max_sock_fd; i++) {
																																				                        if(client_array[i] != 0)
																																							                                    send(client_array[i], buf, sizeof(buf), 0);
																																							                    }
																																			                    }
																									                if(--select_ret <= 0)
																											                        break;
																											            }
																		            }
																        }

												    close(listen_sock);
												        return 0;
}

