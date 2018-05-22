#ifndef MODBUS_EXCEPTION_H
#define MODBUS_EXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

//https://en.wikipedia.org/wiki/Modbus

/**
 * @class ModbusException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief  Modbus exception
 */
class ModbusException : public std::exception {
public:
	std::string message;
	virtual const char* what() const throw() {
		return "An error in modbus happened";
	}
};

/**
 * @class ModbusConnectException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Connection issue in class
 */
class ModbusConnectException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "Modbus connection issue";
	}
};

/**
 * @class ModbusIllegalFunctionException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Illegal Function 	Error Response Function 0x01
 */
class ModbusIllegalFunctionException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Illegal Function (code 0x01 ) === Function code received in the query is not recognized or allowed by slave";
	}
};

/**
 * @class ModbusIllegalDataAddressException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Illegal Address. 	Error Response Function 0x02
 */
class ModbusIllegalDataAddressException : public ModbusException{
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Illegal Data Address (code 0x02) === Data address of some or all the required entities are not allowed or do not exist in slave";
	}
};

/**
 * @class ModbusIllegalDataValueException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Illegal Data Vlaue. 	Error Response Function 0x03
 */
class ModbusIllegalDataValueException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Illegal Data Value (code 0x03) === Value is not accepted by slave";
	}
};

/**
 * @class ModbusSlaveDeviceFailureException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Server Failure. 	Error Response Function 0x04
 */
class ModbusSlaveDeviceFailureException : public ModbusException{
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Slave Device Failure (code 0x04) === Server Failure. Unrecoverable error occurred while slave was attempting to perform requested action";
	}
};

/**
 * @class ModbusAcknowledgeException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Acknowledge 	Error Response Function 0x05
 */
class ModbusAcknowledgeException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Acknowledge (code 0x05) === Slave has accepted request and is processing it, but a long duration of time is required";
	}
};

/**
 * @class ModbusSlaveDeviceBusyException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Server busy 	Error Reponse Function 0x06
 */
class ModbusSlaveDeviceBusyException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Slave Device Busy (code 0x06) === Slave is engaged in processing a long-duration command. Master should retry later";
	}
};

/**
 * @class ModbusNegativeAcknowledgeException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Negative Acknowledge. 	Error Response Function 0x07
 */
class ModbusNegativeAcknowledgeException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Negative Acknowledge (code 0x07) === Slave cannot perform the programming functions. Master should request diagnostic or error information from slave";
	}
};

/**
 * @class ModbusMemoryParityErrorException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Memory error.		Error Response Function 0x08
 */
class ModbusMemoryParityErrorException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Memory Parity Error (code 0x08) === Slave detected a parity error in memory. Master can retry the request, but service may be required on the slave device";
	}
};

/**
 * @class ModbusGatewayPathUnavailableException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Gate Way Problem		Error Response Function 0x0A
 */
class ModbusGatewayPathUnavailableException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Gateway Path Unavailable (code 0x0A) === Specialized for Modbus gateways. Indicates a misconfigured gateway";
	}
};

/**
 * @class ModbusGatewayTargetDeviceFailedToRespondException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Gate Way Problem		Error Response Function 0x0B
 */
class ModbusGatewayTargetDeviceFailedToRespondException : public ModbusException {
public:
	virtual const char* what() const throw() {
		return "=== EXCEPTION Gateway Target Device Failed to Respond (code 0x0B) === Specialized for Modbus gateways. Sent when slave fails to respond";
	}
};

/**
 * @class ModbusBufferException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Buffer is too small
 */
class ModbusBufferException : public ModbusException {
public:
	virtual const char* what() const throw() {
	return "=== EXCEPTION Buffer === Size of buffer to small";
	}
};

/**
 * @class ModbusDataException
 * @author mousticke
 * @date 21/05/18
 * @file modbus_exceptions.h
 * @brief Address or Amount Input is Wrong
 */
class ModbusDataException : public ModbusException {
public:
	virtual const char* what() const throw() {
	return "=== EXCEPTION Data amount === Too many data";
	}
};

#endif 