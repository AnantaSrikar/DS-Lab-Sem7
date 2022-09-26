# -*- MakeFile -*-

all : TCPEchoClient.o TCPEchoServer.o

TCPEchoClient.o: TCPEchoClient.c
	gcc TCPEchoClient.c -o TCPEchoClient.o

TCPEchoServer.o: TCPEchoServer.c
	gcc TCPEchoServer.c -o TCPEchoServer.o

clean:
	rm -fr *.o