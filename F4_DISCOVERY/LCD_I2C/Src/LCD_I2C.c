/*
 * LCD_I2C.c
 *
 *  Created on: Jul 20, 2024
 *      Author: Mert
 */

#include "LCD_I2C.h"

HAL_StatusTypeDef status;


/* 	I2C modülünde D0-D3 arası pinler üzerinden veri aktarımı yapılmıyor
 *	D4-D7 arası pinler üzerinden veri aktarımı yapılabiliyor
 *	Bu sebeple LCD kullanımı 4 pin ile gerçekleştirildi
 */


void LCD_Device_Ready(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr)
{
	status = HAL_I2C_IsDeviceReady(hi2cx, DevAddr, 3, 1000);

	if(status == HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	}
	else
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
			HAL_Delay(250);
		}
	}

}


void LCD_Send30h(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr)
{
	for(uint8_t i=0; i<3; i++)
	{
		HAL_Delay(20);
		HAL_I2C_Master_Transmit(hi2cx, DevAddr, (uint8_t *)0x30, sizeof(0x30), 1000);
	}
	HAL_Delay(20);
}

void LCD_SendCommand(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char DATA)
{
	char data_1 = 0;
	char data_2 = 0;
	uint8_t data_t[4] = {0};

	// KOMUT GÖNDERİMİ
	data_1 = (DATA & 0xF0);
	data_2 = (DATA & 0x0F) << 4;

	data_t[0] = data_1|(0x0C); // EN=1, RS=0
	data_t[1] = data_1|(0x08); // EN=0, RS=0
	data_t[2] = data_2|(0x0C); // EN=1, RS=0
	data_t[3] = data_2|(0x08); // EN=0, RS=0
	HAL_I2C_Master_Transmit(hi2cx, DevAddr, data_t, 4, 1000);
}

void LCD_SendData(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char DATA)
{
	char data_1 = 0;
	char data_2 = 0;
	uint8_t data_t[4] = {0};

	// KOMUT GÖNDERİMİ
	data_1 = (DATA & 0xF0);
	data_2 = (DATA & 0x0F) << 4;

	data_t[0] = data_1|(0x0D); // EN=1, RS=0
	data_t[1] = data_1|(0x09); // EN=0, RS=0
	data_t[2] = data_2|(0x0D); // EN=1, RS=0
	data_t[3] = data_2|(0x09); // EN=0, RS=0
	HAL_I2C_Master_Transmit(hi2cx, DevAddr, data_t, 4, 1000);
	HAL_Delay(30);
}

void LCD_ClearScreen(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr)
{
	LCD_SendCommand(hi2cx, DevAddr, 0x01);
	HAL_Delay(20);
}

void LCD_SetCursor(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, int row, int col)
{
	switch(row)
	{
	case 0:
		col |= 0x80;
		break;

	case 1:
		col |= 0xC0;
		break;

	default:
		break;
	}
	LCD_SendCommand(hi2cx, DevAddr, col);
}


void LCD_Init(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr)
{
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x30);
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x30);
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x30);
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x20);	//4 bit modu
	HAL_Delay(20);

	//Ekran ayarlamaları
	LCD_SendCommand(hi2cx, DevAddr, 0x28);	// Fonksiyon seçimi
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x08);	// Ekran kapalı
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x01);	// Ekranı temizle
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x06);	// Giriş kipi ayarlaması
	HAL_Delay(20);
	LCD_SendCommand(hi2cx, DevAddr, 0x0C);	// Ekran açık
	HAL_Delay(20);
}

void LCD_SendString(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char *str)
{
	while(*str != '\0')
	{
		LCD_SendData(hi2cx, DevAddr, *str++);
		HAL_Delay(20);
	}
}
