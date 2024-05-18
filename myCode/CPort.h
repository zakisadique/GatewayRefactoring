/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPORT.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CPORT_H
#define CPORT_H

#include "global.h"
#include "config.h"
#include "CRingBuffer.h"
#include <string>

class CPort
{
protected:
	/**@link aggregationByValue
	 * @supplierCardinality 1*/
	CRingBuffer m_ringBufferTx;

	/**@link aggregationByValue
	 * @supplierCardinality 1*/
	CRingBuffer m_ringBufferRx;
public:

	CPort(uint16_t txSize = 10, uint16_t rxSize = 10);

	/**
	 * \brief Sends one Byte to the buffer
	 *
	 * \param string data	: IN	Byte to be transmitted
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was transmitted
	 * 		 RC_BUFFEROVERFLOW - in case of full buffer
	 */
	RC_t writeByteStream(std::string const &data);

	/**
	 * \brief Receive one Byte from the buffer
	 *
	 * \param string& data	: OUT	Byte received
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was received
	 * 		 RC_BUFFERUNDERFLOW - in case of empty buffer
	 */
	RC_t readByteStream(std::string &data);

	/**
	 * \brief Will transmit all data from TX buffer to hardware
	 * \return
	 * 		RC_SUCCESS - all ok
	 * 		Specific error code in case of error
	 */
	RC_t portTx_isr();

	/**
	 * \brief Will transmit all data from RX hardware to buffer
	 * \return
	 * 		RC_SUCCESS - all ok
	 * 		Specific error code in case of error
	 */
	RC_t portRx_isr();

	/**
	 * \brief Gets  the type of the port.
	 *
	 * Gets  the type of the port.
	 * \note The function is non-blocking.
	 * \return portType: type of port
	 */
	virtual portType_t getType() = 0;
	/**
	 * \brief Destructor
	 * \note The function is non-blocking.
	 */
	~CPort();
private:

	/**
	 * \brief Sends one Byte to the hardware
	 *
	 * \param uint8_t data	: IN	Byte to be transmitted
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was transmitted
	 * 		 Device specific ErrorCode - in case of error
	 */
	virtual RC_t writeByte_hw(CRingBuffer &buffer, uint8_t &data) = 0;

	/**
	 * \brief Receive one Byte from the hardware
	 *
	 * \param uint8_t& data	: OUT	Byte received
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was received
	 * 		 Device specific ErrorCode - in case of error
	 */
	virtual RC_t readByte_hw(CRingBuffer &buffer, uint8_t &data) = 0;
	/**
	 * \brief Sends package to the hardware
	 *
	 * Sends one package to the hardware.
	 * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
	 *       Therefore the function preferably should be called through an ISR
	 * \param uint8_t data	: IN	package to be transmitted
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was transmitted
	 * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
	 */
	virtual RC_t writePackage_hw(uint8_t *data) = 0;
	/**
	 * \brief Receive one package from the hardware
	 *
	 * Receive one package from the hardware.
	 * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
	 *       Therefore the function preferably should be called through an ISR
	 * \param uint8_t* data	: OUT	Package received
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was received
	 * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
	 */
	virtual RC_t readPackage_hw(uint8_t *data) = 0;
	/**
	 * \brief Returns driver package size
	 * \note The function is non-blocking.
	 * \return uint16_t:
	 */
	virtual uint16_t getDriverPackageSize() = 0;

};
/********************
 **  CLASS END
 *********************/
#endif /* CPORT_H */
