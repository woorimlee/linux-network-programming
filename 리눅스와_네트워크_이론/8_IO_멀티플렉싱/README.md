# Part 9. I/O Multiplexing

### 사전적 의미
: 싱글 프로세스, 싱글 스레드 상태에서 다중 입출력을 통해 순차적으로 여러 개의 입출력을 다룸(물론 싱글이 아니어도 되겠지). 
  
  
IO 이벤트를 감지하는 비트 테이블을 준비해, 입출력이 발생해서 비트 필드가 1로 바뀌어있으면 검사를 통해 입출력을 진행해줌.

### 1. select() [예제](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/IO_Multiplexing)
+ 레벨 트리거 방식을 사용해 다중 파일의 I/O 관리를 해준다.
+ int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
  + nfds는 파일 테이블의 최대 크기로, fd_set에 등록된 fd중에 가장 큰 값 + 1을 한 값을 넣어준다.
  + fd_set 구조체를 사용하는 2, 3, 4번째 인수는 순서대로 (2) 읽기 가능과 관련된 이벤트가 도착시 검사해낼 수 있음 (3) write 관련 (4) 예외 이벤트 관련에 대한 정보를 넘긴다.
  + timeout은 이벤트가 감지되지 않을 때 얼마나 기다릴지에 대한 값이다. NULL을 입력하면 무한 대기다.
+ select는 fd_set 제어가 핵심. 
  1) 초기화 : FD_ZERO(fd_set *fds);
  2) 검사할 상태로 바꿈 : FD_SET(int fd, fd_set *fds);
  3) 검사할 상태에서 삭제 : FD_CLR(int fd, fd_set *fds);
  4) 테이블 검사 : FD_ISSET(int fd, fd_set *fds);
+ 순차적인 처리다보니 I/O 처리가 길어지면 starvation 현상 발생. -> I/O가 긴 서비스에 적합하지 않음.
+ fd_set이 이전 상태를 기억하지 못해서, 매번 파일 테이블을 복사해야 함.

### 2. epoll() [예제](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/epoll)
+ select와 다르게 fd를 등록 & 해제 & 변경하는 함수와, 이벤트를 감시하는 함수가 분리디어있고 메모리 복사의 부담이 많이 줄어 성능이 크게 향상되었다.
+ 또한, 엣지 트리거의 지원이 추가됐기 때문에, 이벤트 기반의 설계가 좀 더 쉬워졌다(epoll도 default는 레벨 트리거). 엣지 트리거로 인해, previous state에서 변화가 생겼는지를 감시할 수 있다.
  
  
이외에도, 엣지 트리거를 사용하면 비동기적 소켓 프로그래밍이 가능하다. epoll_wait를 호출하여 이벤트를 감지하는 부분과, 실제 소켓으로부터 데이터를 수신하는 distpatcher 부분을 스레드로 분리하게되면, 이벤트를 감지 후 디스패처에 통지하고 난 뒤 다음번 epoll_wait를 호출할 때 디스패처가 소켓 버퍼를 읽었는지 확인할 필요가 없기 때문이다. 레벨 트리거였으면 epoll_wait를 다시 호출할 때 아직 소켓 버퍼가 비워지지 않았다면 이벤트가 중복해서 통지될 수 있기 때문에 비동기적 소켓 프로그래밍이 힘들다.
+ Event Poll을 생성하기 위해 epoll_create 함수를 사용한다.
+ epoll에 fd나 이벤트를 등록하거나 변경, 제거하는 함수는 epoll_ctl이다.
  + int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  + 순서대로 epoll_create로 생성된 epoll fd, operation(EPOLL_CTL_ADD ...), 적용 대상 fd, 이벤트 구조체.
  + epoll_event 구조체 내 events 필드에는 이벤트 종류를 넣을 수 있고, EPOLLIN : 입력을 감지, EPOLLOUT : 출력을 감지하는 이벤트 종류이다.
  + epoll_event 구조체 내 data 필드는 union 구조체로, 그 안에 fd 필드가 있다.
+ epoll의 이벤트를 읽는 함수는 epoll_wait이다. (pwait는 이벤트를 기다리면 블록되는 함수)
  + int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
  + *events : 이벤트 검사하는 것을 반환할 곳, maxevents : 반환 할 곳 크기, timeout : 타임 아웃 시간. 0으로 주면 넌블록킹 모드.
