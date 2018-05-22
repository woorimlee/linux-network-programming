# Linux Socket Network Programming

이 Repository는 리눅스상에서 구현한 네트워크 프로그래밍에 대한 저장소입니다.
Image_Transferring 폴더에 있는 실행 파일로 이미지를 전송 & 수신 할 수 있으며,
Server_time_Transferring 폴더에 있는 실행 파일로 서버의 현재 시간을 클라이언트로 전송할 수 있습니다.

사용법은 아래와 같습니다.

* SimpleServer.c & SimpleClient.c file is a basic way how to use socket.
Usage : (You just need 2 shells)
1) One shell command this : ./SimpleServer port_num(ex. 4680)
2) The other shell command this : ./SimpleClient 127.0.0.1 4680

* In the Image_Transferring directory, there is JpgClient.c & JpgServer.c file. 
Usage : (You just need 2 shells)
1) One shell command this : ./JpgServer port_num(ex. 4680) test.jpeg
2) The other shell command this : ./JpgClient 127.0.0.1 4680 download_file_name(ex.down.jpeg)

* In the Server_time_Transferring directory, there is TimeServer.c & TimeClient.c file
Usage : (you just need 2 shells also)
1) One shell command this : ./TimeServer port_num
2) The other shell command this : ./TimeClient 127.0.0.1 port_num


