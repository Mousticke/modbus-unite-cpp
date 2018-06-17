#include "../headers/communication_factory.h"
using namespace std;


/**
 * @brief Constructeur de la class CommunicationFactory
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
	_transmitterStation = (uint8_t)(transmitterStation & 0x00FF);
	_transmitterNetwork = (uint8_t)(transmitterNetwork & 0x0F);
	_transmitterPort = (uint8_t)(transmitterPort & 0x0F);
	_receiverStation = (uint8_t)(receiverStation & 0x00FF);
	_receiverNetwork = (uint8_t)(receiverNetwork & 0x0F);
	_receiverPort = (uint8_t)(receiverPort & 0x0F);
}

/**
 * @brief Destructor of the class CommunicationFactory
 */
CommunicationFactory::~CommunicationFactory(){
}

/**
 * @brief Generate a write var
 * @details Generate the frame for the write var.
 * @param startAddr [description]
 * @param values [description]
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateWriteVar(int startAddr, int* values){
	//Header get from extern defined in modbus.h
	uint8_t _modbus_header[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
	vector<uint8_t> stream;
    vector<uint8_t> end_of_frame;
    vector<uint8_t> frame;
    int bytes_count = 0;
	vector<uint8_t> apdu_header = CommunicationFactory::generateAPDU(RequestType::WRITE_OBJECT);
    vector<uint8_t> npdu_header = CommunicationFactory::generateNPDU();
	vector<uint8_t> data_header = CommunicationFactory::generateDATA(startAddr, values);
    vector<uint8_t> values_bytes = CommunicationFactory::generateVALUES(values);
    vector<uint8_t> modbus_header (_modbus_header, _modbus_header + sizeof(_modbus_header)/sizeof(*_modbus_header));
    stream = CommunicationFactory::mergeToFrame(npdu_header, apdu_header, data_header, values_bytes);
    bytes_count = stream.size();
    end_of_frame = stream;
    stream.clear();
	modbus_header[5] = (uint8_t)(bytes_count & 0x00FF);
    modbus_header[6] = (uint8_t)(bytes_count & 0xFF00 >> 8);
    stream.reserve(modbus_header.size() + end_of_frame.size());
    stream.insert(stream.end(), modbus_header.begin(), modbus_header.end());
    stream.insert(stream.end(), end_of_frame.begin(), end_of_frame.end());
    frame = stream;    
	return frame;
}

/**
 * @brief Generate a read var
 * @details Generate the frame for the read var.
 * @param values to send to the automate
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateReadVarResponse(int* values){
    //Header get from extern defined in modbus.h
    uint8_t _modbus_header[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    vector<uint8_t> stream;
    vector<uint8_t> end_of_frame;
    vector<uint8_t> frame;
    int bytes_count = 0;
    vector<uint8_t> apdu_header = CommunicationFactory::generateAPDU(RequestType::READ_OBJECT_OK);
    vector<uint8_t> npdu_header = CommunicationFactory::generateNPDU();
    vector<uint8_t> values_bytes = CommunicationFactory::generateVALUES(values);
    vector<uint8_t> modbus_header (_modbus_header, _modbus_header + sizeof(_modbus_header)/sizeof(*_modbus_header));
    stream = CommunicationFactory::mergeToFrame(npdu_header, apdu_header, values_bytes);
    bytes_count = stream.size();
    end_of_frame = stream;
    stream.clear();
    modbus_header[5] = (uint8_t)(bytes_count & 0x00FF);
    modbus_header[6] = (uint8_t)((bytes_count & 0xFF00) >> 8);
    stream.reserve(modbus_header.size() + end_of_frame.size());
    stream.insert(stream.end(), modbus_header.begin(), modbus_header.end());
    stream.insert(stream.end(), end_of_frame.begin(), end_of_frame.end());
    frame = stream;    
    return frame;
}


vector<uint8_t> CommunicationFactory::generateReadVar(int startAddr, int nbrToRead){
    //Header get from extern defined in modbus.h
    uint8_t _modbus_header[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    vector<uint8_t> stream;
    vector<uint8_t> end_of_frame;
    vector<uint8_t> frame;
    int bytes_count = 0;
    int arr[] = {0,0,0,0};
    vector<uint8_t> modbus_header (_modbus_header, _modbus_header + sizeof(_modbus_header)/sizeof(*_modbus_header));
    vector<uint8_t> apdu_header = CommunicationFactory::generateAPDU(RequestType::READ_OBJECT);
    vector<uint8_t> npdu_header = CommunicationFactory::generateNPDU();
    vector<uint8_t> values_bytes =  CommunicationFactory::generateVALUES(arr);
    values_bytes[0] = (uint8_t) (startAddr & 0x00FF);
    values_bytes[1] = (uint8_t) ((startAddr & 0xFF00) >> 8);
    values_bytes[2] = (uint8_t) (nbrToRead & 0x00FF);
    values_bytes[3] = (uint8_t) ((nbrToRead & 0xFF00) >> 8);
    stream = CommunicationFactory::mergeToFrame(npdu_header, apdu_header, values_bytes);
    bytes_count = stream.size();
    end_of_frame = stream;
    stream.clear();
    modbus_header[5] = (uint8_t)(bytes_count & 0x00FF);
    modbus_header[6] = (uint8_t)((bytes_count & 0xFF00) >> 8);
    stream.reserve(modbus_header.size() + end_of_frame.size());
    stream.insert(stream.end(), modbus_header.begin(), modbus_header.end());
    stream.insert(stream.end(), end_of_frame.begin(), end_of_frame.end());
    frame = stream;  
    return frame;
}


/****************************************PRIVATE***********************************************/

/**
 * @brief merge frame
 * @details merge npdu, apdu and values
 * @param npdu vector<uint8_t>
 * @param apdu vector<uint8_t>
 * @param values vector<uint8_t>
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::mergeToFrame(vector<uint8_t> npdu, vector<uint8_t> apdu, vector<uint8_t> values){
    vector<uint8_t> stream;
    stream.reserve(npdu.size() + apdu.size() +  values.size());
    stream.insert(stream.end(), npdu.begin(), npdu.end());
    stream.insert(stream.end(), apdu.begin(), apdu.end());
    stream.insert(stream.end(), values.begin(), values.end());
    return stream;
}

/**
 * @brief merge frame
 * @details merge npdu, apdu and values
 * @param npdu vector<uint8_t>
 * @param apdu vector<uint8_t>
 * @param data vector<uint8_t>
 * @param values vector<uint8_t>
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::mergeToFrame(vector<uint8_t> npdu, vector<uint8_t> apdu, vector<uint8_t> data, vector<uint8_t> values){
    vector<uint8_t> stream;
    stream.reserve(npdu.size() + apdu.size() + data.size() + values.size());
    stream.insert(stream.end(), npdu.begin(), npdu.end());
    stream.insert(stream.end(), apdu.begin(), apdu.end());
    stream.insert(stream.end(), data.begin(), data.end());
    stream.insert(stream.end(), values.begin(), values.end());
    return stream;
}

vector<uint8_t> CommunicationFactory::generateNPDU(){
    uint8_t _npdu_header[] = {0xf0, 0x00, 0x00, 0x00, 0x00};
    vector<uint8_t> npdu_header (_npdu_header, _npdu_header + sizeof(_npdu_header)/sizeof(*_npdu_header));
    npdu_header[1] = _transmitterStation;
    npdu_header[2] = (uint8_t)(((_transmitterNetwork & 0x0F) << 4) + (_transmitterPort & 0x0F));
    npdu_header[3] = _receiverStation;
    npdu_header[4] = (uint8_t)(((_receiverNetwork & 0x0F) << 4) + (_receiverPort & 0x0F));
    return npdu_header;
}

/**
 * @brief generate APDU
 * @details generate apdu segment which contains the request type
 * @param req RequestType
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateAPDU(RequestType::request req){
    if(req == 0x36){
        uint8_t _apdu_header[] = {req, 0x06, 0x68, 0x07};
        vector<uint8_t> apdu_header (_apdu_header, _apdu_header + sizeof(_apdu_header)/sizeof(*_apdu_header));
        return apdu_header;
    }else if(req == 0x66){
        uint8_t _apdu_header[] = {req, 0x07};
        vector<uint8_t> apdu_header (_apdu_header, _apdu_header + sizeof(_apdu_header)/sizeof(*_apdu_header));
        return apdu_header;
    }else{
        uint8_t _apdu_header[] = {req, 0x06, 0x68, 0x07};
        vector<uint8_t> apdu_header (_apdu_header, _apdu_header + sizeof(_apdu_header)/sizeof(*_apdu_header));
        return apdu_header;
    }

}

/**
 * @brief generate DATA
 * @details generate DATA segment which contains the start address and the size array of values
 * @param startAddr int
 * @param values int[]
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateDATA(int startAddr, int* values){
    uint8_t _data_header[] = {0x00, 0x00, 0x00, 0x00};
    int size_array = (sizeof(values) / sizeof(values[0])) + 1;
    vector<uint8_t> data_header (_data_header, _data_header + sizeof(_data_header)/sizeof(*_data_header));
    data_header[0] = (uint8_t)(startAddr & 0x00FF);
    data_header[1] = (uint8_t)((startAddr) >> 8);
    data_header[2] = (uint8_t)(size_array & 0x00FF);
    data_header[3] = (uint8_t)((size_array) >> 8);
    return data_header;
}

/**
 * @brief generate VALUES
 * @details generate VALUES segment which translate int to bytes
 * @param values int[]
 * @return vector<uint8_t>
 */
vector<uint8_t> CommunicationFactory::generateVALUES(int* values){
    int size_array = (sizeof(values) / sizeof(values[0])) + 1;
    vector<uint8_t> values_bytes ((size_array) * 2, 0x00);
    int counter = 0;
    for (int data=0; data<(size_array); data++) {
        values_bytes[counter] = (values[data] & 0x00FF);
        values_bytes[counter + 1] = ((values[data] & 0xFF00) >> 8);
        counter += 2;
    }
    return values_bytes;
}