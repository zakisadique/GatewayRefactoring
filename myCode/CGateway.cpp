/*
 * CParser.cpp
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#include "CGateway.h"

#include <string>
#include "CPort.h"
#include <algorithm>
using namespace std;

CGateway::CGateway(CPort &portA, CPort &portB, ErrorHandler &errorHandler) :
		m_errorHandler(errorHandler)
{
	checkValidity();

	m_portA = &portA;
	m_portB = &portB;
}
CGateway::CGateway(CPort *portA, CPort *portB, ErrorHandler &errorHandler) :
		m_portA(portA), m_portB(portB), m_errorHandler(errorHandler)
{
	checkValidity();
}

RC_t CGateway::transmitFromAToB()
{

	if (0 == m_portA || 0 == m_portB)
	{
		return RC_ERROR;
	}

	RC_t result = RC_ERROR;
	//Transmit from A to B
	string data;

	//Read the data
	result = m_portA->readByteStream(data);

	//Do something with the data

	//Write the data
	result = m_portB->writeByteStream(data);

	return result;
}

CGateway::CGateway(CPortFactory::port_t portA, CPortFactory::port_t portB,
		ErrorHandler &errorHandler) :
		m_portA(CPortFactory::createPort(portA)), m_portB(
				CPortFactory::createPort(portB)), m_errorHandler(errorHandler)
{

	checkValidity();
}

CPort*& CGateway::getMPortA()
{
	return m_portA;
}

CPort*& CGateway::getMPortB()
{
	return m_portB;
}

CGateway::~CGateway()
{
	m_portA = 0;
	m_portB = 0;
}

uint8_t CGateway::portASCLIN = 0;
uint8_t CGateway::portCAN = 0;
std::vector<CPort*> CGateway::portsUsed;

void CGateway::checkValidity()
{

	if (m_portA == nullptr || m_portB == nullptr)
	{
		m_errorHandler(ErrorHandler::RC_NULL_PORT);

	}

	if (m_portA->getType() == UART)
	{
		++portASCLIN;
	}
	else if (m_portA->getType() == CAN)
	{
		++portCAN;
	}

	if (m_portB->getType() == UART)
	{
		++portASCLIN;
	}
	else if (m_portB->getType() == CAN)
	{
		++portCAN;
	}

	if (portASCLIN > PORT_ASCLINMAX || portCAN > PORT_CANMAX)
	{
		m_errorHandler(ErrorHandler::RC_PORT_EXCEEDED);
	}

	portsUsed.push_back(m_portA);
	portsUsed.push_back(m_portB);

	int countPortA = std::count(portsUsed.begin(), portsUsed.end(), m_portA);
	int countPortB = std::count(portsUsed.begin(), portsUsed.end(), m_portB);

	if (countPortA > 1 || countPortB > 1)
	{
		m_errorHandler(ErrorHandler::RC_PORT_OCCUPIED);
	}

}
