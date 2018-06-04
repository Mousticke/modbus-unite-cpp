CC=g++

CFLAGS=-c -Wall

all: main

main: main.o modbus.o communication_factory.o
	$(CC) main.o modbus.o communication_factory.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

server: server.o modbus.o communication_factory.o
	$(CC) server.o modbus.o communication_factory.o -o server

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

modbus.o: headers/modbus.h src/modbus.cpp
	$(CC) $(CFLAGS) src/modbus.cpp

communication_factory.o: headers/communication_factory.h src/communication_factory.cpp
	$(CC) $(CFLAGS) src/communication_factory.cpp

clean:
	rm -rf *.o