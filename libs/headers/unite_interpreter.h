#ifndef UNITE_INTERPRETER_H
#define UNITE_INTERPRETER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include "../../headers/requestType.h"
#include "decodedResponse.h"

class UniteInterpreter{

private:
	DecodedResponse* _response;
	int checkMagic(std::vector<uint8_t> raw);
	int getSize(std::vector<uint8_t> raw);
	DecodedResponse* getDecodedExtResponse(std::vector<uint8_t> raw, DecodedResponse* response);
	DecodedResponse* getDecodedResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start);
	void decodeAddress(std::vector<uint8_t> raw, DecodedResponse* response);
	DecodedResponse* getReadObjectFrame(std::vector<uint8_t> raw, DecodedResponse* response, int start);
	DecodedResponse* getReadObjectResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start);
	DecodedResponse* getWriteObjectResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start);

public:
	UniteInterpreter(uint8_t transmitterStation, uint8_t transmitterNetwork, uint8_t transmitterPort,uint8_t receiverStation,
    uint8_t receiverNetwork,uint8_t receiverPort,std::vector<uint8_t> overflow,RequestType::request req,int startAddr,int* data);
    UniteInterpreter();
	UniteInterpreter(std::vector<uint8_t> v);
	~UniteInterpreter();
};

#endif
