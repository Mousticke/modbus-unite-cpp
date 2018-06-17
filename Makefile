CC=g++

CFLAGS=-c -Wall

all: main server

main: main.o modbus.o communication_factory.o
	$(CC) main.o modbus.o communication_factory.o -o main -lpthread

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

server: server.o modbus.o communication_factory.o
	$(CC) server.o modbus.o communication_factory.o -o server -lpthread

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

modbus.o: headers/modbus.h src/modbus.cpp
	$(CC) $(CFLAGS) src/modbus.cpp

communication_factory.o: headers/communication_factory.h src/communication_factory.cpp
	$(CC) $(CFLAGS) src/communication_factory.cpp

decoded_response.o: libs/headers/decodedResponse.h libs/decodedResponse.cpp
	$(CC) $(CFLAGS) libs/decodedResponse.cpp

unite_interpreter.o: libs/headers/unite_interpreter.h libs/unite_interpreter.cpp
	$(CC) $(CFLAGS) libs/unite_interpreter.cpp

clean:
	rm -rf *.o