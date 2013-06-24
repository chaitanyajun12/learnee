CC=g++
CFLAGS=-Iincludes/

webserver: create main HttpRequestParser ServerFileSystem HttpResponseGenerator SocketConnection
			$(CC) -o webserver build/main.o build/HttpRequestParser.o build/ServerFileSystem.o build/HttpResponseGenerator.o build/SocketConnection.o $(CFLAGS)

create:
			mkdir build/

main: src/main.cpp
			$(CC) -c -o build/main.o $(CFLAGS) src/main.cpp
			#src/main.cpp src/SocketConnection.cpp src/HttpRequestParser.cpp src/ServerFileSystem.cpp src/HttpResponseGenerator.cpp

HttpRequestParser:  src/HttpRequestParser.cpp
			$(CC) -c -o build/HttpRequestParser.o $(CFLAGS) src/HttpRequestParser.cpp

ServerFileSystem:	src/ServerFileSystem.cpp
			$(CC) -c -o build/ServerFileSystem.o $(CFLAGS) src/ServerFileSystem.cpp

HttpResponseGenerator:  src/HttpResponseGenerator.cpp
			$(CC) -c -o build/HttpResponseGenerator.o $(CFLAGS) src/HttpResponseGenerator.cpp

SocketConnection: src/SocketConnection.cpp
			$(CC) -c -o build/SocketConnection.o $(CFLAGS) src/SocketConnection.cpp

clean:
		rm -f build/*.o ./webserver
		rm -r build/

