/*
 * parser.c
 *
 *  Created on: May 19, 2025
 *      Author: Mert
 */
#include "parser.h"

/*Uart Buffer's parser function*/
HAL_StatusTypeDef ParsePacket(char* Packet)
{
	if((Packet[0] != '$') || (Packet[1] != ';'))
	{
		return HAL_ERROR;
	}
	if((Packet[5] != ',') || (Packet[9] != ';'))
	{
		return HAL_ERROR;
	}
	if((Packet[10] != '!'))
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}


/*Global Buffer's Parser function*/
HAL_StatusTypeDef ParsePacket_Global(char* Packet)
{
	if((Packet[0] != '$') || (Packet[1] != ';'))
	{
		return HAL_ERROR;
	}
	if((Packet[2] != 'S') || (Packet[3] != ':'))
	{
		return HAL_ERROR;
	}
	if((Packet[8] != ',') || (Packet[13] != ','))
	{
		return HAL_ERROR;
	}
	if((Packet[18] != ';') || (Packet[19] != 'M'))
	{
		return HAL_ERROR;
	}
	if((Packet[20] != ':') || (Packet[24] != ','))
	{
		return HAL_ERROR;
	}
	if((Packet[28] != ';') || (Packet[29] != '!'))
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}
