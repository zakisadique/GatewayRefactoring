// Standard (system) header files
#include <iostream>
#include <stdlib.h>
#include <map>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "CGateway.h"
#include "CPortFactory.h"
#include "ErrorHandler.h"

#include "CPort.h"
#include "CCanPort.h"
#include "CUartPort.h"

uint16_t externalBufferSenderSize = 26;
uint16_t externalBufferReceiverSize = 64;
//
CRingBuffer externalBufferRx(externalBufferSenderSize);
CRingBuffer externalBufferTx(externalBufferReceiverSize);

// Main program
int main(void)
{
	ErrorHandler errorHandler;

	RC_t errorMessage;

	uint8_t data = 'A';
	do
	{
		errorMessage = externalBufferRx.write(data++);
	} while (errorMessage == RC_SUCCESS);

	CGateway simpleGateway(CPortFactory::UART, CPortFactory::CAN, errorHandler);

	simpleGateway.getMPortA()->portRx_isr();
	simpleGateway.transmitFromAToB();
	simpleGateway.getMPortB()->portTx_isr();

	cout << "........................................" << endl;

	simpleGateway.getMPortA()->portRx_isr();
	simpleGateway.transmitFromAToB();
	simpleGateway.getMPortB()->portTx_isr();

	cout << "........................................" << endl;

//	CGateway gateway5(nullptr, nullptr, errorHandler);
//
	CPort *port1 = new CUartPort(CUartPort::ASCLIN1, 22, 2,
			CUartPort::parity_t::EVEN, 0, 11, 11);
	CPort *port2 = new CUartPort(CUartPort::ASCLIN1, 22, 2,
			CUartPort::parity_t::EVEN, 0, 11, 11);

	CPort *port3 = new CCanPort(CCanPort::CAN1, 332, 22, 22);
	CPort *port4 = new CCanPort(CCanPort::CAN2, 332, 22, 22);

	CGateway gateway3(port1, port2, errorHandler);
	CGateway gateway4(port1, port4, errorHandler);
	return 0;
}
