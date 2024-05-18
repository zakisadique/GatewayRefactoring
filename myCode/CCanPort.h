/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CCANPORT.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CCANPORT_H
#define CCANPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingBuffer.h"
#include "CUartPort.h"
class CRingBuffer;

#define CAN_DEFAULTBUFFERSIZE 64

class CCanPort: public CPort
{

public:

	enum port_t
	{
		CAN1, /**< \brief CAN Port 1 */
		CAN2, /**< \brief CAN Port 2 */
		NONE, /**< \brief default value no valid port */
	};

	/**
	 * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers
	 *
	 *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers
	 *  Please check the hardware limitations to ensure proper configuration parameters
	 *
	 *  \param port_t port = NONE			: IN	The hardware port to be used
	 *  \param uint16_t baudrate = 115200	: IN	The baudrate of the device. Check the hardware manual for valid values.
	 *  \param uint8_t bits = 8				: IN	The number of data bits, typically 7 or 8
	 *  \param parity_t parity = NONE		: IN	Parity, ODD, EVEN or NONE
	 *  \param uint8_t stopbits = 1			: IN	Number of Stopbits, 1 or 2
	 *  \param uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer
	 *  \param uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer
	 */
	CCanPort(port_t port = NONE, uint32_t baudrate = 1000000,
			uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE);

private:
	/**
	 * \brief Sends one Byte to the hardware
	 *
	 * Sends one Byte to the hardware.
	 * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
	 *       Therefore the function preferably should be called through an ISR
	 * \param uint8_t data	: IN	Byte to be transmitted
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was transmitted
	 * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
	 */
	RC_t writeByte_hw(CRingBuffer &buffer, uint8_t &data);

	/**
	 * \brief Receive one Byte from the hardware
	 *
	 * Receive one Byte from the hardware.
	 * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
	 *       Therefore the function preferably should be called through an ISR
	 * \param uint8_t& data	: OUT	Byte received
	 * \return RC_t:
	 * 		 RC_SUCCESS - byte was received
	 * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
	 */
	RC_t readByte_hw(CRingBuffer &buffer, uint8_t &data);

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
	RC_t readPackage_hw(uint8_t *data);

	/**
	 * \brief Returns driver package size
	 * \note The function is non-blocking.
	 * \return uint16_t:
	 */
	uint16_t getDriverPackageSize();
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
	RC_t writePackage_hw(uint8_t *data);
	/**
	 * \brief Gets  the type of the port.
	 *
	 * Gets  the type of the port.
	 * \note The function is non-blocking.
	 * \return portType: type of port
	 */
	portType_t getType();
};

#endif /* CCANPORT_H */
