#include "../headers/modbus.h"
#include <arpa/inet.h>
using namespace std;

/**
* Main contructor of Modbus
* @param host IP address of host
* @param port Port for connection
* @return
*/
Modbus::Modbus(const char* host, int port){
	HOST = host;
	PORT = port;
	_connected = 1;
}

/**
* Overload Modbus contructor with default port at 502
* @param host IP address of host
* @return
*/
Modbus::Modbus(const char* host){
	Modbus(host, 502);
}

/**
 * @brief destructor of the class Modbus
 * @return 
 */
Modbus::~Modbus(void){
}


/**
 * @brief Connect the socket
 * @details Create a connection between client and server with TCP protocol
 * @return bool
 */
bool Modbus::ModbusConnected(){
	if(PORT == 0){
		cout << "Missing port or host" << endl;
		_connected = false;
		return _connected;
	}else{
		cout << "Found host : " << HOST << " and port : " << PORT << endl;
	}
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(_socket == -1){
		cout << "Error opening socket" << endl;
		_connected = false;
		return _connected;
	}else{
		cout << "Socket opened successfully" << endl;
	}

	_server.sin_family = AF_INET;
	_server.sin_addr.s_addr = inet_addr(HOST);
	_server.sin_port = htons(PORT);

	if(connect(_socket, (struct sockaddr*)&_server, sizeof(_server)) < 0){
		cout << "Connection error" << endl;
		_connected = false;
		return _connected;
	}
	cout << "Connected" << endl;
	_connected = true;
	return true;
}

/**
 * @brief Server create
 * @details Create a connection between client and server with TCP protocol
 * @return bool
 */
bool Modbus::ModbusConnectedServer(){
	if(PORT == 0){
		cout << "Missing port" << endl;
		return false;
	}
	_socketserver = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socketserver == -1){
		cout << "Error opening socket" << endl;
		return false;
	}else{
		cout << "Socket opened successfully" << endl;
	}
	bzero((char*) &_server_server, sizeof(_server_server));
	_server_server.sin_family = AF_INET;
	_server_server.sin_addr.s_addr = inet_addr(HOST);
	_server_server.sin_port = htons(PORT);
	if(bind(_socketserver, (struct sockaddr *)&_server_server, sizeof(_server_server)) < 0){
        cerr << "Cannot bind" << endl;
        return false;
    }
    listen(_socketserver, 5);
    while(true){
    	socklen_t len = sizeof(_server);
    	int connFd = accept(_socketserver, (struct sockaddr *)&_server, &len);
    	if (connFd < 0){
            cerr << "Cannot accept connection" << endl;
            return 0;
        }else{
            cout << "Connection successful" << endl;
        }
    }
    return true;
}


/**
 * @brief Close connexion
 * @details Close connexion
 */
void Modbus::ModbusClose(){
	close(_socket);
	cout << "Socket closed" << endl;
}

/**
 * @brief Use send from socket lib
 * @details send the message to the server
 * @param to_send message to send
 * @param length length of the message
 * @return integer positif or negative
 */
ssize_t Modbus::ModbusSend(vector<uint8_t> to_send, size_t length){
	ssize_t result = send(_socket, static_cast<const void*>(to_send.data()), length, 0);
	if(result < 0)
		cout << "Something went wrong in the send function." << endl;
	else{
		cout << "Send function successfull" << endl;
	}
	return result;

}

void Modbus::threadRequest(vector<uint8_t> to_send, size_t length){
	Modbus::ModbusSend(to_send, length);
	Modbus::ModbusReceive();
}

/**
 * @brief Use recv from socket lib
 * @details receive the message from the API
 * @param buffer message from the server
 * @return integer positif or negative
 */
ssize_t Modbus::ModbusReceive(){
	Modbus::clear();
	_buffer.resize(261, 0x00);
	cout << "Receiving frame..." << endl;
	ssize_t res = recv(_socket, _buffer.data(), _buffer.size(), 0);
	if(res >= 0){
		_buffer.resize(res);
		cout << "Received a frame " << endl;
	}else{
		cout << "Something went wrong in the receive function" << endl;
	}
	return res;
}

/**
 * @brief Get message from automate
 * @details get the vector of bytes of the message received by the socket
 * @return vector
 */
vector<uint8_t> Modbus::GetMessageFromAutomate(){
	return _buffer;
}
/**************************PRIVATE ************************************************/
/**
 * @brief clear vector of receive message
 */
void Modbus::clear(){
	_buffer.clear();
}