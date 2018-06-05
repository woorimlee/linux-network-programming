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
