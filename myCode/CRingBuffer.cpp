

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CRingBuffer.h"

//Method Implementations

CRingBuffer::CRingBuffer(uint16_t size)
{
	cout << "just created buffer having size " << size << endl;

	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	//Todo: check range
	m_size = size;

	m_pBuffer = new uint8_t[size];
}


CRingBuffer::~CRingBuffer()
{
	delete[] m_pBuffer;
}

RC_t CRingBuffer::read(uint8_t& data)
{
	if (m_fillLevel > 0)
	{
		data = m_pBuffer[m_readIdx++];

		m_readIdx %= m_size;
		m_fillLevel--;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}

}

#if 0
RC_t CRingBuffer::write(uint8_t data)
{
	if (m_fillLevel < m_size)
	{
		m_pBuffer[m_writeIdx++] = data;

		m_writeIdx %= m_size;
		m_fillLevel++;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}
}
#endif
RC_t CRingBuffer::write(uint8_t data)
{
	if (m_fillLevel < m_size)
	{
		m_pBuffer[m_writeIdx++] = data;

		m_writeIdx %= m_size;
		m_fillLevel++;

		if (m_fillLevel == m_size){
			return RC_BUFFEROVERFLOW;
		}

		return RC_SUCCESS;


	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}
}

RC_t CRingBuffer::clear()
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	return RC_SUCCESS;
}

RC_t CRingBuffer::read(uint16_t packageSize, uint8_t* data){
	uint16_t currentByte = 0;



	if (m_fillLevel > 0){
		while (currentByte < packageSize)
		{
			data[currentByte] = m_pBuffer[m_readIdx++];

			m_readIdx %= m_size;
			m_fillLevel--;

			++currentByte;



			if (m_fillLevel == 0){
				return RC_SUCCESS;
			}
		}
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}



	return RC_SUCCESS;

#if 0
		while (currentByte < packageSize){
			if (m_fillLevel > 0)
			{
				data[currentByte] = m_pBuffer[m_readIdx++];

				m_readIdx %= m_size;
				m_fillLevel--;

				++currentByte;


			}
			else
			{
				return RC_BUFFERUNDERFLOW;
			}

		}
#endif
}

RC_t CRingBuffer::write(uint16_t packageSize, uint8_t* data){
	uint16_t currentByte = 0;
	while (currentByte < packageSize){
		if (m_fillLevel < m_size)
		{
			m_pBuffer[m_writeIdx++] = data[currentByte];

			m_writeIdx %= m_size;
			m_fillLevel++;
			++currentByte;

			if (m_fillLevel == m_size){
				return RC_SUCCESS;
			}

		}
		else
		{
			return RC_BUFFERUNDERFLOW;
		}
	}
//	cout << ":" << data << " : " << endl;
	return RC_SUCCESS;


}

bool operator< (const CRingBuffer& internal, const CRingBuffer& external){

	return internal.m_size < external.m_fillLevel;

}

bool operator== (const CRingBuffer& external, uint16_t value){
	return external.m_fillLevel == value;

}
