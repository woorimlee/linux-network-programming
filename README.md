# net_prog_lecture

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

