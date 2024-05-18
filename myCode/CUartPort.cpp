/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CUARTPORT.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CUartPort.h"
#include "CRingBuffer.h"

//Method Implementations

CUartPort::CUartPort(port_t port, uint32_t baudrate, uint8_t bits,
		parity_t parity, uint8_t stopbits, uint16_t bufferSizeRx,
		uint16_t bufferSizeTx) :
		CPort(bufferSizeTx, bufferSizeRx)
{
}

RC_t CUartPort::writeByte_hw(CRingBuffer &buffer, uint8_t &data)
{
	RC_t result;
	result = buffer.write(data);
	if (result == RC_SUCCESS)
	{
		cout << "Just wrote to UART hardware: " << data << endl;
	}

	return result;
}

RC_t CUartPort::readByte_hw(CRingBuffer &buffer, uint8_t &data)
{

	RC_t result = buffer.read(data);

	if (result == RC_SUCCESS)
	{
		cout << "Just read from UART hardware: " << data << endl;
	}

	return result;
}

RC_t CUartPort::readPackage_hw(uint8_t *data)
{

	RC_t result = externalBufferRx.read(this->getDriverPackageSize(), data);

	if (result == RC_SUCCESS)
	{
		for (int i = 0; i < this->getDriverPackageSize(); ++i)
		{
			cout << "Just read from UART hardware: Package: ";
			cout << "[ ";
			if (data[i] != '0')
			{
				cout << data[i];
			}

			cout << " ] ";
			cout << endl;
		}
	}

	return result;

}

uint16_t CUartPort::getDriverPackageSize()
{
	return 1;
}

RC_t CUartPort::writePackage_hw(uint8_t *data)
{
	RC_t result;
	result = externalBufferTx.write(this->getDriverPackageSize(), data);

	if (result == RC_SUCCESS)
	{

		for (int i = 0; i < this->getDriverPackageSize(); ++i)
		{
			if (data[i] != '0')
			{
				cout << "Just wrote to UART hardware: Package: ";
				cout << "[ ";
				cout << data[i];
				cout << " ] ";
			}
			else
			{
				result = RC_NODATA;
			}
		}
		cout << endl;
	}

	return result;
}

portType_t CUartPort::getType()
{
	return UART;
}
