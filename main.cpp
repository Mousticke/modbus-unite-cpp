#include <iomanip>
#include "headers/modbus.h"
#include "headers/communication_factory.h"
#include <sstream>


int main(int argc, char const *argv[])
{
	const char* s = "172.22.209.252";
	int values[] = {30,70,80};

	Modbus* modbus = new Modbus(s, 502);
	modbus->ModbusConnected();

	CommunicationFactory* factory = new CommunicationFactory(23, 8, 0, 22, 8, 0); //8.17 8.22
	vector<uint8_t> genWriteVar = factory->generateWriteVar(31, values);
	int size_write_var = genWriteVar.size();
	std::cout << "====== WRITE ======" << std::endl;
	modbus->ModbusSend(genWriteVar, (std::size_t)size_write_var);
	modbus->ModbusReceive();
	vector<uint8_t> buffer = modbus->GetMessageFromAutomate();
	for(std::vector<uint8_t>::const_iterator i = buffer.begin(); i != buffer.end(); i++){
			std::cout << (int)*i << '\t';
			std::cout << "0x" << std::hex << (int)*i << std::endl;
	}
	return 0;
}