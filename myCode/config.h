/*
 * config.h
 *
 *  Created on: 13-Jan-2024
 *      Author: zakisadique
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "CRingBuffer.h"
#define PORT_ASCLINMAX 10
#define PORT_CANMAX 2

extern uint16_t externalBufferSenderSize; /**< \brief External sender buffer size*/
extern uint16_t externalBufferReceiverSize; /**< \brief External receiver buffer size */
//
extern CRingBuffer externalBufferRx; /**< \brief External receiver buffer */
extern CRingBuffer externalBufferTx; /**< \brief External sender buffer*/

#endif /* CONFIG_H_ */
