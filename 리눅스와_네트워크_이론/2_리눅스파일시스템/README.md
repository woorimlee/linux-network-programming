# Part3. 리눅스 파일 시스템 개요
  

### About files
+ Regular files : 바이트 스트림으로 이루어진 일반적인 파일
+ Directories and links : Directories are used to provide the names with which to
access files, Links are a pair of a name and inode
    출처 : Linux System Programming 2nd edition by Robert Love
+ Special files : 커널 object 파일. Pipes(called FIFOs)와 Sockets는 IPC를 위한 스페셜 파일이다.
+ Filesystems and namespaces : 리눅스에서는 파일과 디렉토리에 대해  global and unified namespace를 제공해준다. C++에서 배운 그 네임 스페이스와 매커니즘은 비슷하다. 네임 스페이스들로 구분할 수 있는 범주를 만들어주기 때문이다.
  
### Mounting Disks 
+ 리눅스상에서 device 들은 항상 자동으로 마운트되진 않기 때문에 mount command를 사용하기도 해야한다. 
  
Mounted된 모든 디바이스들은 /etc/mtab디렉토리 내에 [configuration file](https://en.wikipedia.org/wiki/Configuration_file) 이 생성된다.

+ 디바이스를 disconnect할 때 먼저 unmount를 해줘야 한다. 캐시에 있는 내용과 디바이스에 아직 write되지 않은 내용을 파일 시스템에 넣어줘야 하기 때문이다.

+ /etc/fstab 디렉토리 내에는 자동으로 마운트되야 할 목록들이 들어있다. fstab에서 디바이스를 마운트하기 위해서 __UUID(Universal Unique ID)__ 혹은 __LVM(Logical Volume Manager)__을 사용한다. 
  
+ /etc/fstab 구조의 필드 값은 순서대로 다음과 같습니다.
  1. File system : 파일 시스템 장치명.
  2. Mount point : 마운트 시켜줄 디렉토리 경로.
  3. File system type : 파일 시스템의 타입(ntfs나 nfs, ext3 같은 것).
  4. Mount options : 파일 시스템을 마운트 할 시 사용되는 옵션(auto 같은 것).
  5. Dump status : 덤프(백업)을 할 것인지 설정하는 필드로, 0이면 덤프를 안 하고 1이면 dump 명령어를 줬을 때 덤핑함.
  6. FSCK(File Sequence Check) status : 부트로더가 FSCK 체크를 할 지 결정하는 옵션으로 1이면 루트 파일 시스템을, 0이면 자동 검사를 하지 않겠다는 설정.

### Inodes
+ 모든 리눅스 파일이나 디렉토리는 inode라는 것을 갖고 있다. Inode는 file's metadata를 저장하는 파일이다. 

### Links
+ 간략하게 설명하자면, 다른 파일에 대한 포인터라고 볼 수 있다. 
+ 링크에는 Soft(Symbolic) links와 Hard links가 있다.
  1. Symbolic : Link를 설정하려는 파일을 가리키는데, 새로운 Inode를 생성해서 그 포인터가 오리지널 파일을 가리키기 때문에 원본 파일이 삭제되면 해당 데이터에 접근할 수 없다.
  2. Hard : Link를 설정하려는 파일의 Inode를 가르키기 때문에 원본 파일이 삭제 되어도 문제 없이 사용이 가능하다.
