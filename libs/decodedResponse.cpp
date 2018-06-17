#include "headers/decodedResponse.h"

/************************************PUBLIC*******************************/

DecodedResponse::DecodedResponse(){

}

DecodedResponse::DecodedResponse(uint8_t transmitterStation, uint8_t transmitterNetwork, uint8_t transmitterPort,uint8_t receiverStation,
    uint8_t receiverNetwork,uint8_t receiverPort,std::vector<uint8_t> overflow,RequestType::request req,int startAddr,std::vector<int> data, bool extended, uint8_t extended_value){
	this->transmitterStation = transmitterStation;
    this->transmitterNetwork = transmitterNetwork;
    this->transmitterPort = transmitterPort;
    this->receiverStation = receiverStation;
    this->receiverNetwork = receiverNetwork;
    this->receiverPort = receiverPort;
    this->overflow = overflow;
    this->req = req;
    this->startAddr = startAddr;
    this->_data = data;
    this->extended = extended;
    this->extended_value = extended_value;
}

DecodedResponse::~DecodedResponse(){

}

uint8_t DecodedResponse::getReceiverStation(){
    return receiverStation;
}

uint8_t DecodedResponse::getReceiverNetwork(){
    return receiverNetwork;
}

uint8_t DecodedResponse::getReceiverPort(){
    return receiverPort;
}

uint8_t DecodedResponse::getTransmitterStation(){
    return transmitterStation;
}

uint8_t DecodedResponse::getTransmitterNetwork(){
    return transmitterNetwork;
}

uint8_t DecodedResponse::getTransmitterPort(){
    return transmitterPort;
}

bool DecodedResponse::getExtended(){
    return extended;
}

uint8_t DecodedResponse::getExtendedValue(){
    return extended_value;
}

RequestType::request DecodedResponse::getRequestType(){
    return req;
}

void DecodedResponse::setReceiverStation(uint8_t rs){
    receiverStation = rs;
}

void DecodedResponse::setReceiverNetwork(uint8_t rn){
    receiverNetwork = rn;
}

void DecodedResponse::setReceiverPort(uint8_t rp){
    receiverPort = rp;
}

void DecodedResponse::setTransmitterStation(uint8_t ts){
    transmitterStation = ts;
}

void DecodedResponse::setTransmitterNetwork(uint8_t tn){
    transmitterNetwork = tn;
}

void DecodedResponse::setTransmitterPort(uint8_t tp){
    transmitterPort = tp;
}
    
void DecodedResponse::setExtended(bool ext){
    extended = ext;
}

void DecodedResponse::setExtendedValue(uint8_t ext_val){
    extended_value = ext_val;
}

void DecodedResponse::setRequestType(RequestType::request request){
    req = request;
}

void DecodedResponse::setData(std::vector<int> data){
    _data = data;
}

void DecodedResponse::setStartAddr(int num){
    startAddr = num;
}