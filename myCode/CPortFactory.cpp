/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPORTFACTORY.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

//System Include Files

//Own Include Files
#include "CPortFactory.h"

//Method Implementations

CPort* CPortFactory::createCanPort(CCanPort::port_t port, uint32_t baudrate,
		uint16_t bufferSizeRx, uint16_t bufferSizeTx)
{
	return new CCanPort(port, baudrate, bufferSizeRx, bufferSizeTx);
}

CPort* CPortFactory::createUartPort(CUartPort::port_t port, uint32_t baudrate,
		uint8_t bits, CUartPort::parity_t parity, uint8_t stopbits,
		uint16_t bufferSizeRx, uint16_t bufferSizeTx)
{
	return new CUartPort(port, baudrate, bits, parity, stopbits, bufferSizeRx,
			bufferSizeTx);
}

CPort* CPortFactory::createPort(port_t port)
{
	switch (port)
	{
	case UART:
		return createUartPort();
	case CAN:
		return createCanPort();
	default:
		break;
	}

	return 0;
}
