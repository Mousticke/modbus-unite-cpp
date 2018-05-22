#ifndef COMMUNICATION_FACTORY_H
#define COMMUNICATION_FACTORY_H

#include <iostream>
#include "modbus.h"
using namespace std;

class CommunicationFactory{
private:
	uint8_t _transmitterStation;
    uint8_t _transmitterNetwork;
    uint8_t _transmitterPort;
    uint8_t _receiverStation;
    uint8_t _receiverNetwork;
    uint8_t _receiverPort;

public:
	CommunicationFactory(int transmitterStation,int transmitterNetwork,int transmitterPort,int receiverStation,int receiverNetwork,int receiverPort);
	~CommunicationFactory();

	vector<uint8_t> generateWriteVar(int startAddr, int* values);
};

#endif
