/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CRINGBUFFER.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include "global.h"

class CRingBuffer
{
private:
	uint8_t *m_pBuffer; /**< \brief Pointer to the buffer memory. */
	uint16_t m_size; /**< \brief Size of the buffer. */
	uint16_t m_readIdx; /**< \brief Index for reading data. */
	uint16_t m_writeIdx; /**< \brief Index for writing data. */
	uint16_t m_fillLevel; /**< \brief Current fill level of the buffer. */
public:
	/**
	 * \brief Constructor for CRingBuffer class.
	 * \param size Size of the buffer (default is 10).
	 */
	CRingBuffer(uint16_t size = 10);
	/**
	 * \brief Destructor for CRingBuffer class.
	 */
	~CRingBuffer();
	/**
	 * \brief Clears the contents of the buffer.
	 * \return RC_t Status code indicating the success or failure of the operation.
	 */
	RC_t clear();
	/**
	 * \brief Reads a single byte from the buffer.
	 * \param data Reference to store the read byte.
	 * \return RC_t Status code indicating the success or failure of the operation.
	 */
	RC_t read(uint8_t &data);
	/**
	 * \brief Writes a single byte to the buffer.
	 * \param data Byte to be written.
	 * \return RC_t Status code indicating the success or failure of the operation.
	 */
	RC_t write(uint8_t data);
	/**
	 * \brief Reads a package of bytes from the buffer.
	 * \param packageSize Number of bytes to read.
	 * \param data Pointer to the memory to store the read data.
	 * \return RC_t Status code indicating the success or failure of the operation.
	 */
	RC_t read(uint16_t packageSize, uint8_t *data);
	/**
	 * \brief Writes a package of bytes to the buffer.
	 * \param packageSize Number of bytes to write.
	 * \param data Pointer to the data to be written.
	 * \return RC_t Status code indicating the success or failure of the operation.
	 */
	RC_t write(uint16_t packageSize, uint8_t *data);

	/**
	 * \brief Overloaded less than operator for comparing CRingBuffer instances.
	 * \param internal Reference to the internal CRingBuffer.
	 * \param external Reference to the external CRingBuffer for comparison.
	 * \return bool True if the internal size is less than the external fill level.
	 */
	friend bool operator<(const CRingBuffer &internal,
			const CRingBuffer &external);
	/**
	 * \brief Overloaded equality operator for comparing CRingBuffer instances.
	 * \param external Reference to the external CRingBuffer for comparison.
	 * \param value Value to compare the external CRingBuffer's size with.
	 * \return bool True if the external CRingBuffer's size is equal to the provided value.
	 */
	friend bool operator==(const CRingBuffer &external, uint16_t value);
};
/********************
 **  CLASS END
 *********************/
#endif /* CRINGBUFFER_H */
