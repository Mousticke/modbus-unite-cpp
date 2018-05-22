#include <iostream>
#include <iomanip>
#include "headers/modbus.h"
#include "headers/communication_factory.h"



int main(int argc, char const *argv[])
{
	const char* s = "127.0.0.1";
	std::string message_to_server = "something here";
	int values[] = {10,20,30};

	Modbus* modbus = new Modbus(s, 502);
	modbus->ModbusConnected();

	CommunicationFactory* factory = new CommunicationFactory(48, 3, 0, 10, 8, 0);
	vector<uint8_t> genWriteVar = factory->generateWriteVar(100, values);
	
	int size_write_var = genWriteVar.size();

	for(std::size_t i=0; i < (std::size_t)size_write_var; ++i){
    	std::cout << (int)genWriteVar[i] << '\t'; 
    	std::cout << 
    		std::hex <<           // output in hex
            std::setw(4) <<       // each byte prints as two characters
            std::setfill('0') <<  // fill with 0 if not enough characters
            static_cast<unsigned int>(genWriteVar[i]) << std::endl;
	}

	return 0;
}