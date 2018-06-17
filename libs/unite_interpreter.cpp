#include "headers/unite_interpreter.h"

/************************************PUBLIC*******************************/


UniteInterpreter::UniteInterpreter(std::vector<uint8_t> v){
	DecodedResponse* response = new DecodedResponse;
	if(!UniteInterpreter::checkMagic(v)){
		std::cout << "Magic modbus missmatch, return : null" << std::endl;
	}
	unsigned int size = (unsigned int)UniteInterpreter::getSize(v);
	if(size != v.size() -6 ){
		std::cout << "Size missmatch" << std::endl;
	}
	UniteInterpreter::decodeAddress(v, response);
	if (v[7] == (uint8_t) 0xF0) {
		response = UniteInterpreter::getDecodedResponse(v, response, 12);
    }else if (v[7] == (uint8_t) 0xF2) {
    	response = UniteInterpreter::getDecodedExtResponse(v, response);
    }
    _response = response;
}

UniteInterpreter::~UniteInterpreter(){

}

/**********************************PRIVATE**********************************/

DecodedResponse* UniteInterpreter::getDecodedExtResponse(std::vector<uint8_t> raw, DecodedResponse* response){
	response->setExtended(true);
    response->setExtendedValue(raw[13]);
    return UniteInterpreter::getDecodedResponse(raw, response, 14);
}

DecodedResponse* UniteInterpreter::getDecodedResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start){
	RequestType* rt = new RequestType(raw[start]);
	RequestType type = rt->_type;
    if (type.requestObject) {
        std::cout << "Request type is not supported or does not exist, return : null" << std::endl;
        return NULL;
    }
    response->setRequestType(type.requestObject);
    if (type.requestObject == RequestType::request::ACK_OK || type.requestObject == RequestType::request::ACK_NOK) {
        return response;
    }
    switch (type.requestObject) {
        case RequestType::request::ACK_NOK:
        case RequestType::request::ACK_OK:
            return response;
        case RequestType::request::WRITE_OBJECT:
            return UniteInterpreter::getWriteObjectResponse(raw, response, start);
        case RequestType::request::READ_OBJECT:
            return UniteInterpreter::getReadObjectFrame(raw, response, start);
        case RequestType::request::READ_OBJECT_OK:
            return UniteInterpreter::getReadObjectResponse(raw, response, start);
    }
}

void UniteInterpreter::decodeAddress(std::vector<uint8_t> raw, DecodedResponse* response){
	response->setTransmitterStation(raw[8]);
    response->setTransmitterNetwork((uint8_t) ((raw[9] >> 4) & (uint8_t) 0x0F));
    response->setTransmitterPort((uint8_t) (raw[9] & (uint8_t) 0x0F));

    response->setReceiverStation(raw[10]);
    response->setReceiverNetwork((uint8_t) ((raw[11] >> 4) & (uint8_t) 0x0F));
    response->setReceiverPort((uint8_t) (raw[11] & (uint8_t) 0x0F));
}

DecodedResponse* UniteInterpreter::getReadObjectFrame(std::vector<uint8_t> raw, DecodedResponse* response, int start) {
    response->setStartAddr((raw[start + 5] << 8) + raw[start + 4]);
    std::vector<int> data;
    data.push_back((raw[start + 7] << 8) + raw[start + 6]);
    response->setData(data);
    return response;
}

DecodedResponse* UniteInterpreter::getReadObjectResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start) {
    std::vector<int> data;
    int offset = 0;
    for (int i = 0; i < (int)((raw.size() - 13) / 2); i++) {
        data.push_back((raw[start + 3 + offset] << 8) + raw[start + 2 + offset]);
        offset += 2;
    }
    response->setData(data);
    return response;
}

DecodedResponse* UniteInterpreter::getWriteObjectResponse(std::vector<uint8_t> raw, DecodedResponse* response, int start) {
    response->setStartAddr((raw[start + 5] << 8) + raw[start + 4]);
    int nbr = (raw[start + 7] << 8) + raw[start + 6];
    std::vector<int> data;
    int offset = 0;
    for (int i = 0; i < nbr; i++) {
        data.push_back((raw[start + 9 + offset] << 8) + raw[start + 8 + offset]);
        offset += 2;
    }
    response->setData(data);
    return response;
}

int UniteInterpreter::checkMagic(std::vector<uint8_t> raw){
	return raw[0] == 0x00 && raw[1] == 0x00 && raw[2] == 0x00 && raw[3] == 0x01 && raw[4] == 0x00;
}

int getSize(std::vector<uint8_t> raw) {
    return (raw[6] << 8) + raw[5];
}