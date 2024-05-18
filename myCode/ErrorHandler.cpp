/*
 * errorHandler.cpp
 *
 *  Created on: Jan 15, 2024
 *      Author: zakis
 */

#include <iostream>
#include "ErrorHandler.h"

void ErrorHandler::operator ()(error_t errorCode)
{
	if (errorCode == RC_PORT_EXCEEDED){
		std::cerr << "Number of ports exceeded. Program will terminate" << std::endl;
		std::terminate();
	} else if (errorCode == RC_NULL_PORT){
		std::cerr << "NULL port detected. Program will terminate" << std::endl;
		std::terminate();
	} else if (errorCode == RC_PORT_OCCUPIED){
		try {
			throw customException("Port already occupied");
		} catch (const customException& e) {
			std::cerr << "Caught an exception: " << e.what() << std::endl;
		}
		std::cerr << "Port already occupied. Program will terminate" << std::endl;;
		std::terminate();
	}
}

