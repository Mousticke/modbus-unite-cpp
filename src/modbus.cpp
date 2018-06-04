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
	_slaveID  =  1;
	_messageID = 1;
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
 * @brief set slave id 
 * @param id id of the slave to set in the server
 */
void Modbus::ModbusSetSlaveID(int id){
	_slaveID = id;
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
 * 
 * @param to_send message to send
 * @param length length of the message
 * 
 * @return integer positif or negative
 */
ssize_t Modbus::ModbusSend(vector<uint8_t> to_send, size_t length){
	_messageID++;
	/*for (vector<uint8_t>::const_iterator i = to_send.begin(); i != to_send.end(); ++i){
    	cout << (int)*i << ' ';
	}*/
	ssize_t result = send(_socket, static_cast<const void*>(to_send.data()), length, 0);
	if(result < 0)
		cout << "Something went wrong in the send function." << endl;
	else{
		cout << "Send function successfull" << endl;
	}
	return result;

}

int Modbus::GetMessageID(){
	return _messageID;
}

vector<uint8_t> Modbus::GetMessageFromAutomate(){
	return _buffer;
}

void Modbus::clear(){
	_buffer.clear();
}

/**
 * @brief Use recv from socket lib
 * @details receive the message from the API
 * 
 * @param buffer message from the server
 * @return integer positif or negative
 */
ssize_t Modbus::ModbusReceive(){
	Modbus::clear();
	_buffer.resize(261, 0x00);
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
 * @brief Get the modbus trame
 * @return  message  if everything is fine. Otherwise an error
 */
string Modbus::GetMessageToSend(){
	if(_connected == 1){
		return _modbus_trame;
	}
	else{
		string error_message("Can't get the message to send. Socket is not connected.");
		return error_message;
	}
}

/**
 * @brief Set the message to send
 * @details set the message to send to the server with the tcp protocol.
 * 
 * @param message 
 */
void Modbus::SetMessageToSend(string& message){
	if(_connected == 1){
		_modbus_trame = message;
	}
	else{
		return;
	}
}
