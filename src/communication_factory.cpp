#include "../headers/communication_factory.h"
using namespace std;



CommunicationFactory::CommunicationFactory(
	int transmitterStation, 
	int transmitterNetwork, 
	int transmitterPort, 
	int receiverStation,
	int receiverNetwork, 
	int receiverPort){
	_transmitterStation = (uint8_t)transmitterStation;
	_transmitterNetwork = (uint8_t)transmitterNetwork;
	_transmitterPort = (uint8_t)transmitterPort;
	_receiverStation = (uint8_t)receiverStation;
	_receiverNetwork = (uint8_t)receiverNetwork;
	_receiverPort = (uint8_t)receiverPort;
}

CommunicationFactory::~CommunicationFactory(){
}

vector<uint8_t> CommunicationFactory::generateWriteVar(int startAddr, int* values){
	uint8_t _modbus_header[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x13, 0x00};
	uint8_t _npdu_header[] = {0xf0, 0x00, 0x00, 0x00, 0x00};
	uint8_t _data_header[] = {0x00, 0x00, 0x00, 0x00};
	vector<uint8_t> stream;
	vector<uint8_t> modbus_header (_modbus_header, _modbus_header + sizeof(_modbus_header)/sizeof(*_modbus_header));
	vector<uint8_t> npdu_header (_npdu_header, _npdu_header + sizeof(_npdu_header)/sizeof(*_npdu_header));
	vector<uint8_t> data_header (_data_header, _data_header + sizeof(_data_header)/sizeof(*_data_header));
	int size_array = sizeof(values) / sizeof(*values);
	vector<uint8_t> values_bytes (size_array * 2, 0x00);
	int bytes_count = 0;
	vector<uint8_t> end_of_frame;
	vector<uint8_t> frame;

	npdu_header[1] = _transmitterStation;
    npdu_header[2] = (uint8_t)(((_transmitterNetwork & 0x0F) << 4) + (_transmitterPort & 0x0F));
    npdu_header[3] = _receiverStation;
    npdu_header[4] = (uint8_t)(((_receiverNetwork & 0x0F) << 4) + (_receiverPort & 0x0F));
    data_header[0] = (uint8_t)(startAddr & 0x00FF);
    data_header[1] = (uint8_t)((startAddr & 0xFF00) >> 8);
    data_header[2] = (uint8_t)(size_array & 0x00FF);
    data_header[3] = (uint8_t)((size_array & 0xFF00) >> 8);

    int counter = 0;
    for (int data=0; data<size_array; data++) {
    	values_bytes[counter] = (data & 0x00FF);
    	values_bytes[counter + 1] = ((data & 0xFF00) >> 16);
    	counter += 2;
    }
	
	stream.reserve(npdu_header.size() + data_header.size());
    stream.insert(stream.end(), npdu_header.begin(), npdu_header.end());
    stream.insert(stream.end(), data_header.begin(), data_header.end());
    bytes_count = stream.size();
    end_of_frame = stream;

    stream.clear();

	modbus_header[5] = (uint8_t)(bytes_count & 0x00FF);
    modbus_header[6] = (uint8_t)(bytes_count & 0xFF00 >> 16);

    stream.reserve(modbus_header.size() + end_of_frame.size());
    stream.insert(stream.end(), modbus_header.begin(), modbus_header.end());
    stream.insert(stream.end(), end_of_frame.begin(), end_of_frame.end());

    //uint8_t* frame = (uint8_t*)malloc(stream.size()*sizeof(*frame));
    //copy(stream.begin(), stream.end(), frame);
    frame = stream;
    stream.clear();
	return frame;
}