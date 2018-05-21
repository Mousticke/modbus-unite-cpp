#include <iostream>
#include "headers/modbus.h"

int main(int argc, char const *argv[])
{
	const char* s = "127.0.0.1";
	std::string message_to_server = "something here";

	Modbus* modbus = new Modbus(s, 502);
	
	modbus->ModbusConnected();
	modbus->SetMessageToSend(message_to_server);

	std::string message_to_send = modbus->GetMessageToSend();
	std::cout << "To send : " << message_to_send.c_str() << std::endl;
	modbus->ModbusSend();

	modbus->ModbusReceive();
	std::string message_response = modbus->GetMessageFromAutomate();
	std::cout << "Response : " << message_response.c_str() << std::endl;
	return 0;
}