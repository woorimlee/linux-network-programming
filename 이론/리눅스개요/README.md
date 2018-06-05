# Part 1. 리눅스와 커맨드
  
  
  
### Open Source 
: 다른 프로그래머가 소스 코드를 참고하거나 issues를 fix해서 more stable & reliable 할 수 있게 소스 코드를 공개하는 것(GPL 라이센스를 갖는 소프트웨어를 말함). __General Public License__ 라이센스를 갖는 리눅스 등은 한 번 GPL 라이센스로 공개되면, 앞으로도 계속 GPL 라이센스를 가져야 한다. 그래야 GPL로 공개된 소프트웨어가 약간 수정되어 상업적 목적으로 팔리는 경우를 막을 수 있기 때문이다.
  
  
  
### BASH
: Bourne-again shell. 본 어게인 셸은 GNU 프로젝트를 위해 브라이언 폭스가 작성한 유닉스 셸이다. 사용자가 입력하는 command line에 대해 command interpreter 역할을 하는 것이 shell이다(셸 그 자체도 프로그램임. 로그인 하면 자동으로 실행되는).
  
  
  
### man
: Manual을 볼 수 있는 명령어. man section 명령어. 형식으로 동작하며, 특히 섹션에 2가 붙으면 System calls에 대해 볼 수 있다. 
참고로. 명령어 --hlep 옵션을 붙여서 간단한 설명서를 볼 수도 있다.

  
  
### Working with the Shell
: 유저가 Shell interface에 어떤 command를 입력하면, kernel이 그 명령어를 받고 기계어 코드로 실행해 하드웨어 컨트롤을 한 후 결과를 리턴해준다.
  
  
  
# Part 2. Default directories.
: 리눅스는 파일 시스템으로 구성된 OS이기 때문에 file 시스템 같은 것에 대해서 잘 알고 있어야 함. 그중 리눅스 OS에 항상 포함되는(distributions마다 조금씩은 다를수도 있지만 거의 같음) default direcories에 대해 살펴보자면,
+ / : Root directory. 리눅스 파일 시스템 시작점. 시스템내 다른 디렉토리들은 이 루트 디렉토리 밑에 존재한다.
+ /bin : Binary files가 존재. 기본적인 명령어가 들어있음. 어떤 문제가 발생해도 모든 순간에 모든 사용자가 사용 가능함.
+ /sbin : System administrator가 사용하는 바이너리 파일이 저장되는 디렉토리. 
+ /boot : 우리의 서버를 booting 할 때 필요한 파일들이 들어있음. 이 안에 커널이 존재함(vmlinuz란 이름). 
+ /dev : 모든 하드웨어 장치들이 들어있음(하드웨어 장치들 역시 파일로 분류됨).
+ /etc : 리눅스 상에서 돌아가는 대부분의 서비스들은 ASCII text file을 사용하는데 이런 텍스트 파일들이 이 디렉토리에 저장됨. 특히 /ect/passwd 안에는 local linux users' database가 저장되어 있음.
+ /home : user별 개인적인 파일이 저장되는 곳. 새로운 사용자를 생성하면 ID와 동일한 이름의 디렉토리가 생성됨.
+ /lib : 모든 라이브러리 파일(needed by binaries)들이 저장되는 공간. 커널이 사용하는 드라이버 모듈 같은 것도 저장되어 있음.
+ /media : CD-ROM 같은 것을 mount하면 디렉토리가 생성되는데, 이게 /media 디렉토리에 서브 디렉토리로 들어감.
+ /mnt : Older Linux 시스템에서 default directory for mounting devices로 사용됨. 요즘에는 정말 가끔 mounts되는 것들의 디렉토리가 이 디렉토리 밑에 생성됨.
+ /usr : 일반 사용자들용 명령어들이 저장되는 디렉토리.
+ /opt : usr에 저장되는 파일이 small software packages라면, opt에는 large software가 저장되어 있음. 보통 /usr/local 디렉토리로 대치되기도 함.
+ /proc : 실제 하드디스크에 존재하는 영역이 아님. computer memory 영역의 interface 역할을 하는 디렉터리로, 실제 사용중인 작업들이 파일 형태로 존재하는 위치라 current status를 get 하거나 tune할 수 있음(예를 들어 cat /proc/cpuinfo로 인포 확인 가능).
+ /root : 시스템 관리자(슈퍼 유저. Superuser)가 사용하는 디렉토리.
+ /run : Run-time configuration을 위해 사용됨. 이 폴더 안에 여러 사용자나 프로세스들이 서브 디렉토리를 생성해 file등을 만들어 쓸 수 있고, 더 이상 쓸 일이 없어질 때 자동적으로 지워짐.
+ /srv : 모든 중요한 서비스가 들어있는 곳으로, some distributions에서는 /var이라는 이름으로 쓰고, FTP server file structures같은 것들이 저장됨.
+ /sys : System states에 대한 정보를 저장하는 곳. /proc와 비슷한 역할을 하지만 이 폴더는 하드디스크에 저장되는 폴더(따라서 리부트 후에도 사용 가능). /sys는 사용자의 server에서 사용하는 하드웨어에 좀 더 관련이 있고, /proc에는 커널이 현재 사용중인 states에 대한 정보가 담겨있음.
+ /tmp : Temporary files가 저장됨. 모든 유저가 쓸 수 있는 공용 디렉토리. 재부팅 후 유지되지 않고, 접근이 빠른 공간임(RAM file system 에서 사용되는 디렉토리).
+ /var : 시스템 운용중에 사용되는 일시 데이터들이 저장됨. /var/log에 컴퓨터에서 발생한 이벤트들에 대한 시스템 로그들이 저장됨.
