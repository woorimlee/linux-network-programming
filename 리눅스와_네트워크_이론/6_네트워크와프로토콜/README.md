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
