# Networks 개념

### Circuits vs Packets
+ 네트워크 통신의 기본적인 두 가지 방식
  1. circuit-switched network : 두 노드 사이에 회선 점유. 회선 점유한 두 노드간 회선 capacity 보장.
  2. packet-switched network : 보낼 데이터를 패킷 단위로 쪼개서 공용 네트워크를 통해 전송. 한 네트워크에 많은 노드들이 사용할 수 있음(회선 점유가 아님).

### Internetworking
+ 가장 흔한 네트워크 기술 컨셉은 LAN(Local area network)이다. 컴퓨터간에 네트워크 연결을 시키는 방식.
+ 가장 popular한 패킷 스위치드 네트워크는 Ethernets이다. 
  + 각 패킷은 frame이라고 명명된다. 
  + MAC Header와 DATA, 등으로 한 프레임이 구성된다. [Ethernet frame](https://en.wikipedia.org/wiki/Ethernet_frame)
  + frame 크기가 커지면 header 크기 비중이 줄어드니(% 적으로) Throughput은 올라간다. 하지만, 데이터 망이 접속량이 많거나 상태가 안 좋으면 하나의 프레임을 제대로 다 읽는데 힘이 많이드니 비효율적으로 변할 수 있다는 단점이 있다.
+ 네트워크를 연결시키기 위해 gateway라는 특별한 장치를 쓴다. 서로 다른 통신망, 프로토콜을 사용하는 네트워크 간의 통신을 가능하게 해주는 장치이다.
+ 네트워크 IP address는 세 클래스로(A, B, C) 쪼개서 관리한다.
+ Loopback address는 127.0.0.1의 주소로, local host에 인터넷 연결을 시도할 때 사용되는 주소다.
+ Ports : 프로세스간 통신을 할 때 통신 데이터가 주고 받아지려면 프로세스별로 ID가 있어야 목적지를 찾아갈 수 있는데, PID는 가변적이다보니 Port number를 부여해 유니크한 프로세스 번호를 만들어준다. 
  + 대표적인 포트 번호로 
    1. 21 : FTP
    2. 22 : SSH
    3. 23 : Telnet
    4. 53 : DNS
    5. 80 : HTTP
    6. 443 : HTTPS 

      
      
등이 있다.

+ 어떤 플랫폼에선 Big Endian 방식을, 어떤 플랫폼에선 Little Endian 방식을 사용해 integers 값을 저장하기 때문에 데이터 수신에서 문제가 발생할 수 있고, 그에 따라 Network byte order라는 것이 만들어졌다. 이 방식은 Big Endian 방식을 사용하기 때문에, 리틀 엔디안을 사용중이라면 반드시 변형의 과정이 필요하다. (ARM, MIPS는 보통 빅, 인텔 x86은 보통 리틀 엔디안 사용)

+ OSI 7 layer가 표준이고, TCP/IP 4 layer는 표준이 아니다(!).
+ UDP는 데이터 패킷을 수신측이 수신했는지에 대해 관심이 없다. 즉 개런티가 없다. 동영상 스트리밍 서비스 같은 경우 UDP를 많이 쓴다.
+ TCP는 수신측이 데이터를 잘 수신했는지 확인을 해주기 때문에 reliable stream delivery로 알려져있다. TCP의 특징은 다음과 같다.
  + [Virtual Circuit](https://en.wikipedia.org/wiki/Virtual_circuit) : 하나의 터미널이 call, 다른 터미널이 accept -> 연결이 됐다면 가상 회선 위에서 통신.
  + Buffered transfer : 패킷 전송시 임의로 데이터를 모아서 전송함. 반대로 큰 데이터는 더 작게 조각낼수도 있다.
  + Stream orientation : 비트 스트림 기반으로 데이터를 전송한다(보내진 시퀀스 그대로 전달).
  + Full duplex : 전이중 방식. 데이터를 동시에 양뱡항으로 전송.
  + Unstructured stream : 데이터 스트림의 구조체 자체는 guarantee를 보장하지 않는다. 어플리케이션이 알아서 보내도록 한다.
+ IP address 기억하기 힘드니 DNS가 나왔다. DNS server : 문자를 IP 주소로 바꿔주는 것.

