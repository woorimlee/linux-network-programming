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
