#include <iostream>
#include <iomanip>
#include "headers/modbus.h"
#include "headers/communication_factory.h"



int main(int argc, char const *argv[])
{
	const char* s = "172.22.209.252";
	std::string message_to_server = "something here";
	int values[] = {20,50,60};

	Modbus* modbus = new Modbus(s, 502);
	modbus->ModbusConnected();

	CommunicationFactory* factory = new CommunicationFactory(17, 8, 0, 22, 8, 0); //8.17 8.22
	vector<uint8_t> genWriteVar = factory->generateWriteVar(31, values);
	
	int size_write_var = genWriteVar.size();
	std::cout << size_write_var << std::endl;

	/*for(std::size_t i=0; i < (std::size_t)size_write_var; ++i){
    	std::cout << (int)genWriteVar[i] << '\t'; 
    	std::cout << 
    		std::hex <<           // output in hex
            std::setw(4) <<       // each byte prints as two characters
            std::setfill('0') <<  // fill with 0 if not enough characters
            static_cast<unsigned int>(genWriteVar[i]) << std::endl;
	}*/
	modbus->ModbusSend(genWriteVar, (std::size_t)size_write_var);
	modbus->ModbusReceive();
	modbus->printVector();

	
	return 0;
}