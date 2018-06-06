# Part 6. Threading

### Thread 이론에 대해 정리한 링크
1. [스레드에 대한 개념 정리](https://blog.naver.com/and_lamyland/221182893855)
2. [스레드 라이브러리에 대한 간단한 정보](https://blog.naver.com/and_lamyland/221186424738)


### 멀티 스레딩 장점
1. 프로세스 생성에 비해 라이트함(Cost of context switching, 메모리 세이빙 등에서)
2. Parallelism : 멀티플 스레드들이 멀티플 프로세서에 의해 동시에 돌아감.
3. 스레드가 여러개 동작하니 하나만 동작하다가 IO 등으로 멈추는 것에 비해 Resposiveness가 향상된다.

### 커널 스레드와 유저 스레드
+ 커널 레벨에서 동작하는 스레드와 유저 레벨에서 동작하는 스레드가 있고, 이 스레드들이 어떤 커넥션을 맺고 있느냐에 따라 다양한 모델들이 나온다(스레드에 대한 개념 정리 링크에 설명되어 있습니다).

### 멀티 스레드를 이용하다보면
+ 여러 스레드들이 공용으로 사용하는 자원에 대한 동기화 문제가 발생합니다(멀티 프로세스도 동일한 문제가 발생). [그 부분에 대해 정리한 링크](https://blog.naver.com/and_lamyland/221187949898) 해당 링크에서 Critical section과 race condition 등이 무엇인지 확인하실 수 있습니다.

### Thread 프로그래밍 
1. Pthread 사용법 소개 --> 작성중
2. [pthread 간단한 사용 예제](https://github.com/woorimlee/linux-network-programming/tree/mas    ter/API_study/thread)

