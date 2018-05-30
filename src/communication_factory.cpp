#include "../headers/communication_factory.h"
using namespace std;


/**
 * @brief Constructeur de la class CommunicationFactory
 * 
 * @param transmitterStation [description]
 * @param transmitterNetwork [description]
 * @param transmitterPort [description]
 * @param receiverStation [description]
 * @param receiverNetwork [description]
 * @param receiverPort [description]
 */
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

/**
 * @brief Destructor of the class CommunicationFactory
 */
CommunicationFactory::~CommunicationFactory(){
}

/**
 * @brief Generate a write var
 * @details Generate the frame for the write var.
 * 
 * @param startAddr [description]
 * @param values [description]
 * 
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateWriteVar(int startAddr, int* values){
	//Header get from extern defined in modbus.h
	uint8_t _modbus_header[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x13, 0x00};
	uint8_t _npdu_header[] = {0xf0, 0x00, 0x00, 0x00, 0x00};
	uint8_t _data_header[] = {0x00, 0x00, 0x00, 0x00};
    //APDU : Code requete + Cat 6 + seg + type
	uint8_t _apdu_header[] = {0x37, 0x06, 0x68, 0x07};

    //Declare vector of bytes
	vector<uint8_t> stream;
	vector<uint8_t> modbus_header (_modbus_header, _modbus_header + sizeof(_modbus_header)/sizeof(*_modbus_header));
	vector<uint8_t> npdu_header (_npdu_header, _npdu_header + sizeof(_npdu_header)/sizeof(*_npdu_header));
    vector<uint8_t> apdu_header (_apdu_header, _apdu_header + sizeof(_apdu_header)/sizeof(*_apdu_header));
	vector<uint8_t> data_header (_data_header, _data_header + sizeof(_data_header)/sizeof(*_data_header));
	vector<uint8_t> end_of_frame;
	vector<uint8_t> frame;
	int bytes_count = 0;
	int size_array = (sizeof(values) / sizeof(values[0])) + 1;
	vector<uint8_t> values_bytes ((size_array) * 2, 0x00);

	npdu_header[1] = _transmitterStation;
    npdu_header[2] = (uint8_t)(((_transmitterNetwork & 0x0F) << 4) + (_transmitterPort & 0x0F));
    npdu_header[3] = _receiverStation;
    npdu_header[4] = (uint8_t)(((_receiverNetwork & 0x0F) << 4) + (_receiverPort & 0x0F));
    data_header[0] = (uint8_t)(startAddr & 0x00FF);
    data_header[1] = (uint8_t)((startAddr & 0xFF00) >> 8);
    data_header[2] = (uint8_t)(size_array & 0x00FF);
    data_header[3] = (uint8_t)((size_array & 0xFF00) >> 8);

    int counter = 0;
    for (int data=0; data<(size_array); data++) {
    	values_bytes[counter] = (values[data] & 0x00FF);
    	values_bytes[counter + 1] = ((values[data] & 0xFF00) >> 16);
    	counter += 2;
    }
	
	stream.reserve(npdu_header.size() + apdu_header.size() + data_header.size() + values_bytes.size());
    stream.insert(stream.end(), npdu_header.begin(), npdu_header.end());
    stream.insert(stream.end(), apdu_header.begin(), apdu_header.end());
    stream.insert(stream.end(), data_header.begin(), data_header.end());
    stream.insert(stream.end(), values_bytes.begin(), values_bytes.end());
    bytes_count = stream.size();
    end_of_frame = stream;

    stream.clear();

	modbus_header[5] = (uint8_t)(bytes_count & 0x00FF);
    modbus_header[6] = (uint8_t)(bytes_count & 0xFF00 >> 16);

    stream.reserve(modbus_header.size() + end_of_frame.size());
    stream.insert(stream.end(), modbus_header.begin(), modbus_header.end());
    stream.insert(stream.end(), end_of_frame.begin(), end_of_frame.end());

    frame = stream;
    
    /*stream.clear();
    modbus_header.clear();
    npdu_header.clear();
    apdu_header.clear();
    data_header.clear();
    values_bytes.clear();
    end_of_frame.clear();
    
    vector<uint8_t>(modbus_header).swap(modbus_header);
    vector<uint8_t>(stream).swap(stream);
    vector<uint8_t>(npdu_header).swap(npdu_header);
    vector<uint8_t>(apdu_header).swap(apdu_header);
    vector<uint8_t>(data_header).swap(data_header);
    vector<uint8_t>(values_bytes).swap(values_bytes);
	vector<uint8_t>(end_of_frame).swap(end_of_frame);*/
	return frame;
}