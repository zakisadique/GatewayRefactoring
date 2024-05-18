/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPORT.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

//System Include Files
//Own Include Files
#include "CPort.h"
#include <iostream>
using namespace std;

//Method Implementations

CPort::CPort(uint16_t txSize, uint16_t rxSize) :
		m_ringBufferTx(txSize), m_ringBufferRx(rxSize)
{
}

RC_t CPort::writeByteStream(string const &data)
{
	RC_t result = RC_ERROR;

	for (uint16_t i = 0; i < data.length(); i++)
	{
		result = m_ringBufferTx.write(data[i]);

		if (RC_SUCCESS != result)
			return RC_ERROR;
	}

	return result;

}

RC_t CPort::readByteStream(string &data)
{
	string dataFromDriver = "";

	RC_t result = RC_ERROR;
	do
	{
		uint8_t ldata = 0;
		result = m_ringBufferRx.read(ldata);
		if (RC_SUCCESS == result)
		{
			dataFromDriver += (char) ldata;
		}
	} while (RC_SUCCESS == result);

	data = dataFromDriver;

	return RC_SUCCESS;
}

RC_t CPort::portTx_isr()
{

	RC_t result = RC_ERROR;
	RC_t result_hw = RC_ERROR;
	uint16_t packageSize = this->getDriverPackageSize();
	do
	{
		uint8_t dataPackage[packageSize];

		for (int i = 0; i < packageSize; ++i)
		{
			dataPackage[i] = '0';
		}

		result = m_ringBufferTx.read(packageSize, dataPackage);

		if (RC_SUCCESS == result)
		{
			result_hw = writePackage_hw(dataPackage);
		}

	} while (RC_SUCCESS == result && result_hw == RC_SUCCESS);

	return result;

}

RC_t CPort::portRx_isr()
{

	RC_t readrResult = RC_ERROR;
	RC_t writeResult = RC_ERROR;
	uint16_t packageSize = this->getDriverPackageSize();

	do
	{
		uint8_t dataPackage[packageSize];
		for (int i = 0; i < packageSize; ++i)
		{
			dataPackage[i] = '0';
		}

		readrResult = readPackage_hw(dataPackage);

		if (RC_SUCCESS == readrResult)
		{
			writeResult = m_ringBufferRx.write(packageSize, dataPackage);

		}

	} while (RC_SUCCESS == readrResult && RC_SUCCESS == writeResult);

	return readrResult;

}
