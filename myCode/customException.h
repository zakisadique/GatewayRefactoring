/*
 * customException.h
 *
 *  Created on: Jan 15, 2024
 *      Author: zakis
 */

#ifndef CUSTOMEXCEPTION_H_
#define CUSTOMEXCEPTION_H_
#include <stdexcept>
class customException: public std::exception
{
private:
	const char *message; /**< \brief Message associated with the exception. */
public:
	/**
	 * \brief Constructor for customException class.
	 * \param message a string providing additional information about the exception.
	 */
	customException(const char *message) :
			message(message)
	{
	}

	/**
	 * \brief Returns a C-style character string describing the exception.
	 * \return const char* A pointer to the exception message.
	 */
	const char* what() const noexcept override;
};

#endif /* CUSTOMEXCEPTION_H_ */
