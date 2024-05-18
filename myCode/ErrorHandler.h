/*
 * errorHandler.h
 *
 *  Created on: Jan 15, 2024
 *      Author: zakis
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include "global.h"



class ErrorHandler
{

public:
    /**
     * \brief Enumeration for error codes.
     */
	enum error_t {
		RC_PORT_EXCEEDED, /**< \brief Error code for exceeding the maximum number of ports. */
		RC_NULL_PORT, /**< \brief Error code for encountering a null port. */
		RC_PORT_OCCUPIED /**< \brief Error code for attempting to use an already occupied port. */
	};
    /**
     * \brief Overloaded function call operator to handle error codes.
     * \param errorCode The error code to be processed.
     */
	void operator() (error_t errorCode);
};

#endif /* ERRORHANDLER_H_ */
