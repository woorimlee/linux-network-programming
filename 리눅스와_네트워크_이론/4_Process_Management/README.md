# Part 5. Process Management

### Programs, Processes, and Threads
+ Program은 하드 디스크에 저장되어 있는 실행 가능한(Compile 된) binary form의 파일입니다.
+ Process는 Program이 running 된 상태이고, 메인 메모리에 올라간(올라가려고 대기하는 상태도 포함) 것을 말한다(an instance of virtualized memory, kernel resources such as open files, a security context such as an associated user, and one or more threads 등이 포함됨).
+ Thread는 Process를 구성하는 unit이다. [더 자세한 정보](https://blog.naver.com/and_lamyland/221182893855)

### Process ID
+ 각 프로세스는 unique한 ID 값을 가지고, PID라 부른다. idle process가 0의 pid값을 갖고, init 프로세스가 1의 pid값을 갖는다. PID는 pid_t라는 int 자료형으로 저장된다.

### Process hierarchy
+ 한 프로세스가 실행중 다른 프로세스를 만든다면, 자신은 부모가, 만들어진 프로세스는 자식 프로세스가 된다. 
+ 보통 모든 자식 프로세스는 부모 프로세스를 갖게 된다. PPID는 부모 프로세스의 pid를 일컫는 말이다.
+ 만약 자식 프로세스가 종료되었지만 부모 프로세스에 의해 종료 상태를 체크 & 마무리 작업이 이뤄지지 않는다면, 종료는 했지만 리소스가 남아있기 때문에 좀비 프로세스라고 부릅니다.
+ 만약 부모 프로세스가 자식 프로세스보다 먼저 종료되면 자식 프로세스는 고아 프로세스가 됩니다. 이 경우 자식 프로세스의 새 부모 프로세스가 init process가 되고, init process가 알아서 고아였던 자식 프로세스를 종료해줍니다.

### fork() system call에 대한 정보 및 예제 파일 [링크](https://github.com/woorimlee/study_linux_prog/tree/master/chap9)

### Exec(). Running a new process
+ The exec family of calls를 통해 해당 함수를 호출한 프로세스는 새로운 프로그램을 실행하는 프로세스가 된다.
+ 이전의 address space 등을 새로 갈아버리면서 새로운 프로세스가 동작하게 되는데, 대치되는 개념이지 새로 만들어지는 개념이 아닙니다. 
+ 새로운 프로그램으로 대치되기 때문에 이전에 실행되던 프로세스의 원본 프로그램의 나머지 시퀀스는 더 이상 동작하지 않습니다.
+ 새 프로그램으로 대치될 시
  1. Any pending __signals__ are lost.
  2. __signal handlers__ no longer exist in the process' address space.
  3. Any __memory locks__ are dropped.
  4. 대부분의 스레드나 process 값들 역시 사라진다.
  5. 열린 파일 목록 등도 사라지고, 프로세스 address space에 올라가 있는 것들 역시 사라진다.
+ 기존의 프로그램이 없어지기 때문에 exec() 함수 호출 후 return 할 위치가 없어지기 때문에, exec() sys call이 성공한 경우에는 반환하지 않고, 실패시에만 -1을 return 한다.
+ system() 함수를 사용해 exec() 함수를 쉽게 이용할 수 있다. [예제 링크](https://github.com/woorimlee/study_linux_prog/tree/master/chap9) 링크의 system_func.c와 system_implement.c를 참고하면 됩니다.

### Terminating a process
+ exit() 함수를 호출하면 kernel이 프로세스를 terminate한다. 이 함수를 호출하면, 호출한 프로세스에는 리턴할 곳이 없고, 부모 프로세스에 exit() 값을 리턴한다. 
+ main() 함수의 return도 결국에는 exit()를 호출하는데 이 모든 과정은 C start-up routine에 의해 이루어진다.

### SIGCHLD 
+ Process가 종료될 때(terminates) 커널은 SIGCHLD를(Signal)  종료되는 프로세스의 부모 프로세스에게 보낸다. 기본적으로 이 신호는 무시되지만, 원하는 경우 시그널 핸들링을 통해 처리가 가능하다.
+ 부모에게 날라가는 SIGCHLD는 부모가 wait() 함수를 호출해서 수신할 수 있다. 이 함수는 종료된 child process의 pid 값을 리턴한다(대신 실패시 -1을 리턴). 또한, 블록킹 형태로 동작하기 때문에 자식이 종료되야 wait 함수가 끝난다. [더 자세한 정보](https://github.com/woorimlee/study_linux_prog/tree/master/chap9)


