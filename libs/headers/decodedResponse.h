#ifndef DECODED_RESPONSE_H
#define DECODED_RESPONSE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include "../../headers/requestType.h"

class DecodedResponse{

private:
	uint8_t transmitterStation;
    uint8_t transmitterNetwork;
    uint8_t transmitterPort;
    uint8_t receiverStation;
    uint8_t receiverNetwork;
    uint8_t receiverPort;
    std::vector<uint8_t> overflow;
    RequestType::request req;
    int startAddr;
    std::vector<int> _data;
    bool extended = false;
    uint8_t extended_value;



public:
	DecodedResponse(uint8_t transmitterStation, uint8_t transmitterNetwork, uint8_t transmitterPort,uint8_t receiverStation,
    uint8_t receiverNetwork,uint8_t receiverPort,std::vector<uint8_t> overflow,RequestType::request req,int startAddr,std::vector<int> data, bool extended, uint8_t extended_value);
    DecodedResponse();
	~DecodedResponse();
	uint8_t getReceiverStation();
	uint8_t getReceiverNetwork();
	uint8_t getReceiverPort();
	uint8_t getTransmitterStation();
	uint8_t getTransmitterNetwork();
	uint8_t getTransmitterPort();
	bool getExtended();
	uint8_t getExtendedValue();
	RequestType::request getRequestType();
	void setReceiverStation(uint8_t rs);
	void setReceiverNetwork(uint8_t rn);
	void setReceiverPort(uint8_t rp);
	void setTransmitterStation(uint8_t ts);
	void setTransmitterNetwork(uint8_t tn);
	void setTransmitterPort(uint8_t tp);
	void setExtended(bool ext);
	void setExtendedValue(uint8_t ext_val);
	void setData(std::vector<int> data);
	void setRequestType(RequestType::request request);
	void setStartAddr(int num);
};

#endif
