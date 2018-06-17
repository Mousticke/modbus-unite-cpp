#include <iomanip>
#include "headers/modbus.h"
#include "headers/communication_factory.h"
#include "headers/requestType.h"
#include <sstream>
#include <thread>  
#include <chrono>
#include <functional>
#include <pthread.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

void * threading_write (void * arg){
	Modbus* modbus = ((Modbus *)arg);
	int values[] = {30,70,80};
	CommunicationFactory* factory = new CommunicationFactory(12, 8, 0, 23, 8, 0); //8.17 8.22
	vector<uint8_t> genWriteVar = factory->generateWriteVar(31, values);
	int size_write_var = genWriteVar.size();

	std::cout << "====== TO SEND FOR WRITE ======" << std::endl;
	for(std::vector<uint8_t>::const_iterator i = genWriteVar.begin(); i != genWriteVar.end(); i++){
		std::cout << "0x" << std::hex << (int)*i << "\t";
	}
	std::cout << "" <<std::endl;
	std::cout << "====== WRITE ======" << std::endl;
	/*std::thread request1(&Modbus::threadRequest, modbus, genWriteVar, (std::size_t)size_write_var);
	request1.join();*/
	modbus->ModbusSend(genWriteVar, (std::size_t)size_write_var);
	modbus->ModbusReceive();

	std::cout << " " << std::endl;

	vector<uint8_t> buffer = modbus->GetMessageFromAutomate();
	for(std::vector<uint8_t>::const_iterator j = buffer.begin(); j != buffer.end(); j++){
			std::cout << (int)*j << '\t';
			std::cout << "0x" << std::hex << (int)*j << std::endl;
	}

	delete factory;
	delete modbus;
	pthread_exit(NULL);
}

void * threading_read(void * arg){
	Modbus* modbus = ((Modbus *)arg);
	CommunicationFactory* factory = new CommunicationFactory(12, 8, 0, 23, 8, 0); //8.17 8.22
	vector<uint8_t> genReadVar = factory->generateReadVar(30, 3);
	int size_read_var = genReadVar.size();

	std::cout << "====== TO SEND FOR READ ======" << std::endl;
	for(std::vector<uint8_t>::const_iterator k = genReadVar.begin(); k != genReadVar.end(); k++){
		std::cout << "0x" << std::hex << (int)*k << "\t";
	}
	std::cout << "" <<std::endl;
	std::cout << "====== READ ======" << std::endl;
	/*std::thread request2(&Modbus::threadRequest, modbus, genReadVar, (std::size_t)size_read_var);
	request2.join();*/
	modbus->ModbusSend(genReadVar, (std::size_t)size_read_var);
	modbus->ModbusReceive();	
	vector<uint8_t> buffer2 = modbus->GetMessageFromAutomate();
	for(std::vector<uint8_t>::const_iterator l = buffer2.begin(); l != buffer2.end(); l++){
		std::cout << (int)*l << '\t';
		std::cout << "0x" << std::hex << (int)*l << std::endl;
	}
	delete factory;
	delete modbus;
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	const char* s = "172.22.209.253";
	Modbus* modbus = new Modbus(s, 502);
	modbus->ModbusConnected();
	pthread_t tid[2];

	pthread_create(&tid[0], NULL, threading_write, modbus);
	pthread_join(tid[0],NULL);

	pthread_create(&tid[1], NULL, threading_read, modbus);
    pthread_join(tid[1],NULL);
  	
	return 0;
}