/*
 * CParser.h
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#ifndef CPARSER_H_
#define CPARSER_H_

#include <vector>
#include "global.h"
#include "config.h"
#include "CPort.h"
#include "CPortFactory.h"
#include "ErrorHandler.h"

class CGateway
{
private:
	CPort *m_portA; /**< \brief Port A */
	CPort *m_portB; /**< \brief Port B */
	static uint8_t portASCLIN; /**< \brief UART port */
	static uint8_t portCAN; /**< \brief CAN port */
	static std::vector<CPort*> portsUsed; /**< \brief Vector of ports used */
	ErrorHandler &m_errorHandler; /**< \brief File handler */

public:
	/**
	 * Constructor taking explicit port objects
	 */
	CGateway(CPort &portA, CPort &portB, ErrorHandler &errorHandler);

	/**
	 * Contructor, using the default factory settings
	 */
	CGateway(CPortFactory::port_t portA, CPortFactory::port_t portB,
			ErrorHandler &errorHandler);
	/**
	 * @brief Constructor for CGateway class.
	 *
	 * @param portA Pointer to PortA.
	 * @param portB Pointer to PortB.
	 * @param errorHandler Reference to the error handler.
	 */
	CGateway(CPort *portA, CPort *portB, ErrorHandler &errorHandler);
	/**
	 * @brief Transmits data from PortA to PortB.
	 *
	 * This function initiates the transmission of data from PortA to PortB
	 * within the CGateway.
	 *
	 * @return RC_t Status code indicating the success or failure of the
	 * transmission.
	 */
	RC_t transmitFromAToB();
	/**
	 * @brief Virtual destructor for CGateway class.
	 *
	 * This virtual destructor is responsible for cleaning up resources
	 * associated with the CGateway instance.
	 * Subclasses should override this destructor to ensure proper resource
	 * release in derived classes.
	 */
	virtual ~CGateway();
	/**
	 * @brief Getter function for the m_portA member.
	 *
	 * This function provides a reference to the m_portA member variable,
	 * allowing external access
	 * to the PortA instance associated with the CGateway.
	 *
	 * @return CPort*& Reference to the PortA instance.
	 */
	CPort*& getMPortA();
	/**
	 * @brief Getter function for the m_portB member.
	 *
	 * This function provides a reference to the m_portB member variable,
	 * allowing external access
	 * to the PortB instance associated with the CGateway.
	 *
	 * @return CPort*& Reference to the PortB instance.
	 */
	CPort*& getMPortB();
	/**
	 * @brief Checks the validity of the CGateway's internal state.
	 *
	 * This function performs checks on the internal state of the CGateway
	 * to ensure
	 * its validity and consistency. It may throw exceptions or log errors
	 * if any issues are detected.
	 *
	 * @note The specific checks performed may depend on the implementation
	 * details.
	 */
	void checkValidity();

};

#endif /* CPARSER_H_ */
