#include <iostream>
#include "headers/modbus.h"

int main(int argc, char const *argv[])
{
	const char* s = "127.0.0.1";
	std::string message_to_server = "something here";

	Modbus* modbus = new Modbus(s, 502);
	
	modbus->ModbusConnected();
	
	return 0;
}