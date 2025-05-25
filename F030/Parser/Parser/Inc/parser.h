/*
 * parser.h
 *
 *  Created on: May 19, 2025
 *      Author: Mert
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "stm32f0xx.h"
#include "string.h"
#include "main.h"


#define PACKET_MAX_LEN	30

HAL_StatusTypeDef ParsePacket_Global(char* Packet);
HAL_StatusTypeDef ParsePacket(char* Packet);

#endif /* INC_PARSER_H_ */
