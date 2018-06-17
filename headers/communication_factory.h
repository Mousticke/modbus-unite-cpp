#ifndef COMMUNICATION_FACTORY_H
#define COMMUNICATION_FACTORY_H

#include <iostream>
#include "modbus.h"
#include "requestType.h"
using namespace std;

class CommunicationFactory{
private:
	uint8_t _transmitterStation;
    uint8_t _transmitterNetwork;
    uint8_t _transmitterPort;
    uint8_t _receiverStation;
    uint8_t _receiverNetwork;
    uint8_t _receiverPort;

    vector<uint8_t> mergeToFrame(vector<uint8_t> npdu, vector<uint8_t> apdu, vector<uint8_t> data, vector<uint8_t> values);
   	vector<uint8_t> mergeToFrame(vector<uint8_t> npdu, vector<uint8_t> apdu, vector<uint8_t> values);
    vector<uint8_t> generateAPDU(RequestType::request req);
    vector<uint8_t> generateNPDU();
    vector<uint8_t> generateDATA(int startAddr, int* values);
    vector<uint8_t> generateVALUES(int* values);

public:
	CommunicationFactory(int transmitterStation,int transmitterNetwork,int transmitterPort,int receiverStation,int receiverNetwork,int receiverPort);
	~CommunicationFactory();
	vector<uint8_t> generateWriteVar(int startAddr, int* values);
	vector<uint8_t> generateReadVarResponse(int* values);
	vector<uint8_t> generateReadVar(int startAddr, int nbrToRead);
};

#endif
