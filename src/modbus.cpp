#include "../headers/modbus.h"
#include <arpa/inet.h>

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
 * @brief set _connected true is socket is connected
 * @return bool 
 */
bool Modbus::ModbusConnected(){
	if(PORT == 0){
		std::cout << "Missing port or host" << std::endl;
		_connected = false;
		return _connected;
	}else{
		std::cout << "Found host : " << HOST << " and port : " << PORT << std::endl;
	}

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(_socket == -1){
		std::cout << "Error opening socket" << std::endl;
		_connected = false;
		return _connected;
	}else{
		std::cout << "Socket opened successfully" <<std::endl;
	}

	_server.sin_family = AF_INET;
	_server.sin_addr.s_addr = inet_addr(HOST);
	_server.sin_port = htons(PORT);

	if(connect(_socket, (struct sockaddr*)&_server, sizeof(_server)) < 0){
		std::cout << "Connection error" << std::endl;
		_connected = false;
		return _connected;
	}

	std::cout << "Connected" << std::endl;
	_connected = true;
	return true;
}

/**
 * @brief close connection
 */
void Modbus::ModbusClose(){
	close(_socket);
	std::cout << "Socket closed" << std::endl;
}

/**
 * @brief Get the modbus trame
 * @return  message
 */
std::string Modbus::GetMessageToSend(){
	if(_connected == 1){
		return modbus_trame;
	}
	else{
		std::string error_message("Can't get the message to send. Socket is not connected.");
		return error_message;
	}
}

/**
 * @brief Set the message to send
 * @param message
 */
void Modbus::SetMessageToSend(std::string& message){
	if(_connected == 1){
		modbus_trame = message;
	}
	else{
		return;
	}
}

/**
 * @brief Send the modbus yrame
 */
void Modbus::ModbusSend(){
	if(_connected == 1){
		send(_socket, modbus_trame.c_str(), modbus_trame.length(), 0);
	}
	else{
		return;
	}
}

/**
 * @brief Receive the message in buffer from the server after we send the trame. 
 */
void Modbus::ModbusReceive(){
	if(_connected == 1){
		recv(_socket, buffer, strlen(buffer), 0);
	}else{
		return;
	}

}

/**
 * @brief Fet the message we have from the automate
 * @return buffer is everything is fine. Otherwise an error
 */
std::string Modbus::GetMessageFromAutomate(){
	if(_connected == 1){
		return buffer;
	}
	else{
		std::string error_message("Can't get the message from automate. Socket is not connected.");
		return error_message;
	}
}