/*
 * global.h
 *
 *  Created on: 18.10.2019
 *      Author: Fromm
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "ErrorHandler.h"
#include "customException.h"

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef signed int sint32_t;
typedef signed short sint16_t;
typedef signed char sint8_t;

/**
 * \enum RC_t
 * \brief Enumeration of return codes.
 */
enum RC_t{
	RC_SUCCESS, /**< \brief Operation completed successfully. */
	RC_ERROR, /**< \brief General error. */
	RC_WRONGPARAM, /**< \brief Incorrect parameters provided. */
	RC_BUFFEROVERFLOW, /**< \brief Buffer overflow occurred. */
	RC_BUFFERUNDERFLOW, /**< \brief Buffer underflow occurred. */
	RC_PERIPHERALOCCUPIED, /**< \brief  Peripheral already occupied. */
	RC_NODATA /**< \brief No data available. */
};

/**
 * \enum portType_t
 * \brief Enumeration of port types.
 */
enum portType_t{
	UART, /**< \brief UART port type. */
	CAN, /**< \brief CAN port type. */
	NONE /**< \brief No specific port type. */
};

//class myExeptions : public std::exception {
//private:
//	const char* errorMessage;
//public:
//
//public:
//	myExeptions (const char* errorMessage) : errorMessage(errorMessage){
//
//	}
//	const char* what() const noexcept override{
//		std::cerr << "Caught myExeptions: " << errorMessage << std::endl;
//		std::cerr << "Application will be terminated" << std::endl;
//		std::abort();
//		return errorMessage;
//	}
//};

#endif /* GLOBAL_H_ */
