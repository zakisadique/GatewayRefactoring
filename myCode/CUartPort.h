/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CUARTPORT_H
#define CUARTPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingBuffer.h"

#define UART_DEFAULTBUFFERSIZE 20

class CUartPort : public CPort {

public:

    enum port_t{
    	ASCLIN1,		/**< \brief ASCLIN Port 1, per default mapped to USB bridge */
		ASCLIN2, 		/**< \brief ASCLIN Port 2, can be mapped to PIN P12(0),PIN P12(2) */
		ASCLIN3, 		/**< \brief ASCLIN Port 3, can be mapped to PIN P12(3),PIN P12(4) */
		ASCLIN4, 		/**< \brief ASCLIN Port 4, can be mapped to PIN P12(1),PIN P12(5) */
		ASCLIN5, 		/**< \brief ASCLIN Port 5, can be mapped to PIN P12(6) */
		NONE,			/**< \brief default value no valid port */
    };

    enum parity_t{
    	ODD, 			/**< \brief ODD parity, will detect single bit transmission errors */
		EVEN, 			/**< \brief EVEN parity, will detect single bit transmission errors */
		NOPARITY,		/**< \brief NO parity check, only recommended for baudrates below 115200 */
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
    CUartPort(port_t port = NONE,
             uint32_t baudrate = 115200,
             uint8_t bits = 8,
             parity_t parity = NOPARITY,
             uint8_t stopbits = 1,
			 uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE
			 );

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
    RC_t writeByte_hw(CRingBuffer& buffer, uint8_t& data);

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
    RC_t readByte_hw(CRingBuffer& buffer, uint8_t& data);
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
	RC_t readPackage_hw(uint8_t* data);
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
	RC_t writePackage_hw(uint8_t* data);
	/**
	 * \brief Gets  the type of the port.
	 *
	 * Gets  the type of the port.
	 * \note The function is non-blocking.
	 * \return portType: type of port
	 */
	portType_t getType();
};

#endif /* CUARTPORT_H */
