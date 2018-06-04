#ifndef REQUEST_TYPE
#define REQUEST_TYPE

class RequestType {
public:
	enum request {
		WRITE_INTERNAL_WORD = 0x14,
		WRITE_OBJECT = 0x37,
		READ_OBJECT = 0x36,
	    ACK_OK = 0xFE,
	    ACK_NOK = 0xFD
	};
};


#endif