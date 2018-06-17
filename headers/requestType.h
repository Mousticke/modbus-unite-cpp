#ifndef REQUEST_TYPE
#define REQUEST_TYPE

#include <iostream>


class RequestType {
public:
	enum request {
		WRITE_OBJECT = 0x37,
		READ_OBJECT = 0x36,
	    ACK_OK = 0xFE,
	    ACK_NOK = 0xFD,
	    READ_OBJECT_OK = 0x66
	};

	request requestObject;

	uint8_t _type;
	RequestType(uint8_t type){
		_type = type;
	}
};


#endif