#ifndef MODBUS_H
#define MODBUS_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

class Modbus{
private:
	const char* HOST;
	int PORT;
	int _socket;
	bool _connected;
	char* buffer;
	std::string modbus_trame;

	struct sockaddr_in _server;

public:
	Modbus(const char* host, int port);
	Modbus(const char* host);
	~Modbus();

	bool ModbusConnected();
	void ModbusClose();

	void ModbusSend();//send(socket, message, strlen(message))
	void ModbusReceive(); //read(socket, buffer, 1024)

	std::string GetMessageToSend();
	void SetMessageToSend(std::string& message);

	std::string GetMessageFromAutomate();

};

#endif // MODBUS_H
