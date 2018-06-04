#include <iomanip>
#include "headers/modbus.h"
#include "headers/communication_factory.h"
#include <sstream>


/*std::string ToHex(const unsigned char* buffer, size_t size){
	std::stringstream str;
	str.setf(std::ios_base::hex, std::ios::basefield);
	str.setf(std::ios_base::uppercase);
	str.fill('0');
	
	for(size_t i=0; i<size; ++i){
		str << std::setw(3) << "x" << (unsigned short)(unsigned char)buffer[i] << " ";
	}
	return str.str();
}*/



int main(int argc, char const *argv[])
{
	const char* s = "172.22.209.252";
	//int values[] = {30,70,80};

	Modbus* modbus = new Modbus(s, 502);
	modbus->ModbusConnected();

	//CommunicationFactory* factory = new CommunicationFactory(23, 8, 0, 22, 8, 0); //8.17 8.22

	int message = modbus->GetMessageID();
	for(;;){
		if(modbus->GetMessageID() != message){
			modbus->ModbusReceive();
			vector<uint8_t> buffer = modbus->GetMessageFromAutomate();
			for(std::vector<uint8_t>::const_iterator i = buffer.begin(); i != buffer.end(); i++){
      			std::cout << (int)*i << '\t';
      			std::cout << "0x" << std::hex << (int)*i << std::endl;
			}
			message = modbus->GetMessageID();
		}
		
	}

	return 0;
}