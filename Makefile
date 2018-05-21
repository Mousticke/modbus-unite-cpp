CC=g++

CFLAGS=-c -Wall

all: main

main: main.o modbus.o
	$(CC) main.o modbus.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

modbus.o: src/modbus.cpp
	$(CC) $(CFLAGS) src/modbus.cpp
	
clean:
	rm -rf *.o