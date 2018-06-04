#ifndef MODBUS_H
#define MODBUS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include "modbus_exception.h"
using namespace std;


//Modbus function codes : https://en.wikipedia.org/wiki/Modbus
enum{
	READ_COILS			= 0x01,
	READ_INPUT_BITS		= 0x02,
	READ_REGS			= 0x03,
	READ_INPUT_REGS		= 0x04,
	WRITE_COIL			= 0x05,
	WRITE_REG			= 0x06,
	WRITE_COILS			= 0x0F,
	WRITE_REGS			= 0x10,
};

//Exception Codes
enum {
	EX_ILLEGAL_FUNCTION 		= 0x01, // Function Code not Supported
	EX_ILLEGAL_ADDRESS 			= 0x02, // Output Address not exists
	EX_ILLEGAL_VALUE 			= 0x03, // Output Value not in Range
	EX_SERVER_FAILURE 			= 0x04, // Slave Deive Fails to process request
	EX_ACKNOWLEDGE 				= 0x05, // Service Need Long Time to Execute
	EX_SERVER_BUSY 				= 0x06, // Server Was Unable to Accept MB Request PDU
	EX_NOT_ACKNOWLEDGE 			= 0x07, // Slave can not perform the function
	EX_MEMORY_PARITY 			= 0x08, // Slave detected a parity error in memory
	EX_GATEWAY_PROBLEM_PATH 	= 0x0A, // Gateway Path not Available
	EX_GATEWAY_PROBLEM_DEVIVE 	= 0x0B, // Target Device Failed to Response
};

extern uint8_t			_modbus_header[];
extern uint8_t			_npdu_header[];
extern uint8_t			_data_header[];

/**
 * @class Modbus
 * @author mousticke
 * @date 21/05/18
 * @file modbus.h
 * @brief Modbus class
 */
class Modbus{
private:
	const char* 	HOST;
	int 			PORT;
	int 			_socket;
	bool 			_connected;
	int 			_messageID;
	int 			_slaveID;
	string 			_modbus_trame;
	vector<uint8_t> _buffer;

	struct sockaddr_in _server;
	
	void ModbusErrorHanhle(uint8_t *msg, int func);

public:
	Modbus(const char* host, int port);
	Modbus(const char* host);
	~Modbus();
	bool ModbusConnected();
	void ModbusClose();
	ssize_t ModbusSend(vector<uint8_t> to_send, size_t length);
	ssize_t ModbusReceive(); 
	void ModbusSetSlaveID(int id);
	string GetMessageToSend();
	vector<uint8_t> GetMessageFromAutomate();
	void SetMessageToSend(string& message);
	void clear();
	int GetMessageID();
};

#endif // MODBUS_H
