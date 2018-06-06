# Part 4. About OS(간단하게)

  
### Processes
: 리눅스 파일이(프로그램)이 실행된 상태를 프로세스라고 한다. Text(code), Data, Stack, Heap, U-area로 구성된다(여기에는 코드 및 각종 자원과 state, 시스템 resources 등이 존재한다). 

### Threads
: 프로세스 내에서 프로세스가 동작하게하는 single 혹은 multiple의 unit이다(이 말은, 기본적으로 한 프로세스에는 최소한 하나의 스레드가 존재한다는 것이고, 이 스레드를 Main thread라 부른다). Executing code and maintaining the process' running state의 역할을 수행한다.

  
[더 자세한 정보](https://blog.naver.com/and_lamyland/221182893855)

### Process hierarchy
: 각 프로세스는 PID(Process ID)라는 unique positive integer 값이 설정된다. 리눅스에서는 프로세스들이 'Process Tree'라는 계층 구조를 형성한다. 이는 첫 번째 프로세스(Init process)에서부터 트리모양으로 쭉쭉 프로세스들이 확장되기 때문이다. 

  
fork() 시스템 콜에 의해 새로운 프로세스를 만들 수 있다. fork를 호출한 프로세스에(부모 프로세스가 된다) 자식 프로세스를 하나 만들어주고, 보통 자식 프로세스는 부모 프로세스 + 1의 PID값을 가진다.

### Users, Groups, and Permissions
: 리눅스에는 사용자와 사용자 그룹, 기타 사용자에 대한 개념이 존재한다(리눅스 설계 이념). 각 User는 UID값(unique positive integer 형태의)을 갖는데, 이 값은 /etc/passwd에 저장된다. UID 0 은 Root(Special user)의 값이다.

  
각 파일은 Owner & Owing group & Others에 대한 three sets of permission bits를 갖는다.
r(read), w(write), x(execute)권한을 부여해 줄 수 있고, 각 세 비트씩 총 아홉개의 비트로 표현한다. ---,---,--- 앞의 세 비트는 Owner에 대한 rwx, 중간은 Owing group에 대한 세 비트, 마지막은 Everyone else 에 대한 세 비트이고, rwx는 8진수로 표현해 각각 4,2,1의 값을 갖는다.

### Signals
: One way asynchronous 통신 방식이다. 프로세스에서 프로세스로 어떤 메세지를 보낼 때 사용되고, 신호는 커널이 보내준다. Ctrl+C 버튼을 누를 시 Process에게 종료하라는 시그널을 보내는 것 같이 말이다.

### IPC(InterProcess Communication) 
: 프로세스들끼리 information을 교환할 수 있게 만들어주자는 개념이다. Pipes, Named pipes(FIFO), Semaphores, Message queues, Shared memory and Mutexes등이 바로 IPC를 위한 도구이다.

### Error handling
: 함수 사용에 실패하면 보통 -1의 값을 리턴한다. errno는 라이브러리 함수 실행 중 에러가 발생하면 매크로 값을 리턴하며 어떤 에러가 났는지 확인시켜 줄 수 있는 전역 변수다. perror() 함수를 호출해 어떤 에러가 발생했는지 print 해볼 수있다.
