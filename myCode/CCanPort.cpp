#include <iostream>
using namespace std;

#include "CCanPort.h"

CCanPort::CCanPort(port_t port, uint32_t baudrate, uint16_t bufferSizeRx,
		uint16_t bufferSizeTx) :
		CPort(bufferSizeTx, bufferSizeRx)
{
}
RC_t CCanPort::writeByte_hw(CRingBuffer &buffer, uint8_t &data)
{

	RC_t result;
	result = buffer.write(data);
	if (result == RC_SUCCESS)
	{
		cout << "Just wrote to CAN hardware: " << data << endl;
	}

	return result;
}
RC_t CCanPort::readByte_hw(CRingBuffer &buffer, uint8_t &data)
{

	RC_t result = buffer.read(data);

	if (result == RC_SUCCESS)
	{
		cout << "Just read from CAN hardware: " << data << endl;
	}

	return result;
}

RC_t CCanPort::readPackage_hw(uint8_t *data)
{

	RC_t result = externalBufferRx.read(this->getDriverPackageSize(), data);

	if (result == RC_SUCCESS)
	{
		cout << "Just read from CAN hardware: Package: ";
		cout << "[ ";
		for (int i = 0; i < this->getDriverPackageSize(); ++i)
		{

			if (data[i] != '0')
			{
				cout << data[i];
			}

		}
		cout << " ] ";
		cout << endl;
	}

	return result;

}

uint16_t CCanPort::getDriverPackageSize()
{
	return 8;
}

RC_t CCanPort::writePackage_hw(uint8_t *data)
{
	RC_t result;
	result = externalBufferTx.write(this->getDriverPackageSize(), data);

	if (result == RC_SUCCESS)
	{
		cout << "Just wrote to CAN hardware: Package: ";
		cout << "[ ";
		for (int i = 0; i < this->getDriverPackageSize(); ++i)
		{

			if (data[i] != '0')
			{
				cout << data[i];
			}

		}
		cout << " ] ";
		cout << endl;
	}

	return result;
}

portType_t CCanPort::getType()
{
	return CAN;
}
