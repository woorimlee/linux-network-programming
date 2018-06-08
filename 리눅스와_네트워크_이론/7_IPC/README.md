# Part 8. Inter Process Communications

### Pipe [예제 링크](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/pipe_ex)
1. Anonymous pipe(익명 파이프) 
    + 셸에서 '|'를 사용해 두 커맨드(프로세스)의 출력과 입력을 연결해주는 것이 익명 파이프.
    + 자식 프로세스를 fork 하고 부모 자식간 간단한 통신을 할 때 주로 사용함.
    + pipe() 함수를 쓸 경우 인자로 int 배열을 넘기는데, [0]은 읽기용, [1]은 쓰기용으로 쓴다.
    + popen() 함수를 사용하면 command 결과물로 부터 입력을 받거나, 입력치를 command에 넣어 출력할 수 있다.
      + 두 번째 인자로 'r' : command 출력을 받아와서 쓰겠다.
      + 두 번째 인자로 'w' : 어떤 값을 command 명령어의 입력 값으로 넣겠다.
    + pipe.c 파일이 예제 파일이다.

2. Named pipe(명명된 파이프)
    + 경로명이 있는 파이프로, 외부 다른 프로세스에서 접근이 가능한 파이프다(PIPE 타입의 파일로 존재).
    + FIFO라고 부르기도 한다.
    + Read 프로세스와 Write 프로세스가 파이프를 open 할 때 공유 페이지가 생성되면서 통신이 된다. 
    + mkfifo() 함수로 FIFO 파일을 생성해주고(경로명+파일 이름), 접근 권한을 설정해준다.
    + FIFO 파일이 생성되면 open으로 파이프를 사용하고, 보통 수신자 먼저 파이프를 오픈한다.
      + 수신자가 파이프를 오픈하면 송신자가 파이프를 오픈할 때까지 block된다.
    + fifo.c & echo_server_pipe.c & echo_client_pipe.c 파일이 예제 파일이다.
  
  
+ 성능면에서 정교한 프로토콜 작성에 적합하지 못하므로, 이벤트 통지용이나 리다이렉션용으로 사용되는 경우가 많다.

### Unix domain socket [예제 링크](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/Unix_Domain_Socket_ex)
+ 소켓 함수와 기술을 사용해 유닉스 시스템 도메인(범위)에서 통신을 하는 것을 말한다. 즉, 로컬 유닉스 시스템 내에서만 접근하는 것이다.
+ sockaddr_un 구조체를 사용해 유닉스 도메인 소켓의 정보를 저장해준다.
+ 그 외 전체적인 프로그램 시퀀스는 소켓 프로그래밍과 동일하다(passive socket과 active socket).

### Shared memory [예제 링크](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/Shared_Memory)
+ 공유 메모리는 shmget, shmat를 순서대로 호출하여 얻는다. 연결 해제시 shmdt를 사용하고, shmctl로 공유 메모리를 제거하거나 메타 데이터를 얻을 수 있다.
+ shmget : 어떤 키 값을 사용해 공유 메모리의 IPC ID를 얻는다. 이미 존재하는 경우 만들어져있는 공유 메모리의 ID를 반환한다.
+ shmat : ID에 해당하는 공유 메모리와 연결하고, 연결된 주소 번지를 반환한다.

### Semaphore [예제 링크](https://github.com/woorimlee/linux-network-programming/tree/master/API_study/Semaphore)
+ 동기화 도구.
+ semget : 세마포어를 만든다. key 값으로 세마포어를 만들어 IPC ID를 반환받는데, 몇 개의 세마포어를 만들지와(몇 개의 프로세스가 접근 가능한가) 어떤 권한으로 만들지를 정해준다.
+ semctl : 세마포어를 제거하거나 메타 데이터를 읽는다. 보통 처음에 초기화 할 때 한번은 꼭 사용한다.
  + semctl(semid, 0, SETVAL, union semun 구조체 이름); 형식으로 초기화해준다.
+ semop : 세마포어 ID와 세마포어 작동 버퍼 구조체의 주소, 버퍼 구조체의 개수를 넘겨줘서 p, v 오퍼레이션을 할 수 있다. 이 함수와 같이 쓰이는 구조체가 sembuf로, 세 개의 필드 값을 갖고 있고 순서대로 인덱스 번호, 세마포어에 더할 값, 플래그 옵션을 입력할 수 있다.
  + 세마포어를 얻을 경우 
    1) struct sembuf semopen;
    2) semopen.sem_num = 0; 세마포어내 인덱스 번호
    3) semopen.sem_op = -1; 세마포어에 더할 값 
    4) semopen.sem_flg = SEM_UNDO; 작동 플래그
    5) semop(semid, &semopen, 1); 1은 버퍼 구조체의 개수
  + 세마포어를 반납할 경우
    1) struct sembuf semclose;
    2) semclose.sem_num = 0;
    3) semclose.sem_op = 1;
    4) sem_close.sem_flg = SEM_UNDO;
    5) semop(semid, &semclose, 1);

### Signal 
+ 비동기적으로 어떤 사건을 알려주기 위해서 사용한다.
+ 혹은 시간을 동기화 하기 위해서 사용한다.
+ Signal 수신시 해당 시그널에 맞는 default action을 취하거나, 시그널 핸들러를 실행한다.
+ sginal() 함수를 사용해 시그널 핸들러를 등록할 수 있다.
  + sighandler_t signal(int signum, sighandler_t handler);
  + signum에는 시그널 이름을, handler에는 함수를 넣으면 되는데, SIG_IGN을 넣으면 시그널을 무시하겠다는 말이고, SIG_DFL은 시그널 기본 행동을 수행하겠단느 말이다.
  + ex) signal(SIGCHILD, SIG_IGN);
+ 대기열이 없기 때문에 시그널을 잃어 버릴 수 있다.

