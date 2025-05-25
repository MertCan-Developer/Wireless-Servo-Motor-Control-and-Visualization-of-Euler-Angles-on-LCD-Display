/*
 * Lcd_I2C.h
 *
 *  Created on: Jul 20, 2024
 *      Author: Mert
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "main.h"

#define LCD_MODULE_ADDR			0x27
#define LCD_MODULE_WRITE_ADDR	(LCD_MODULE_ADDR << 1)

#define I_D_SET		(0x1 << 1)
#define I_D_RESET	(0x0 << 1)
#define S_SET		(0X1 << 0)
#define S_RESET		(0x0 << 0)
#define D_SET		(0x1 << 2)
#define D_RESET		(0x0 << 2)
#define C_SET		(0x1 << 1)
#define C_RESET		(0x0 << 1)
#define B_SET		(0x1 << 0)
#define B_RESET		(0x0 << 0)
#define S_C_SET		(0x1 << 3)
#define S_C_RESET	(0x0 << 3)
#define R_L_SET		(0x1 << 2)
#define R_L_RESET	(0x0 << 2)
#define DL_SET		(0x1 << 4)
#define DL_RESET	(0x0 << 4)
#define N_SET		(0x1 << 3)
#define N_RESET		(0x0 << 3)
#define F_SET		(0x1 << 2)
#define F_RESET		(0x0 << 2)



void LCD_Init(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr);
void LCD_SendCommand(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char DATA);
void LCD_SendData(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char DATA);
void LCD_ClearScreen(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr);
void LCD_SetCursor(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, int row, int col);
void LCD_Send30h(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr);
void LCD_Device_Ready(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr);
void LCD_SendString(I2C_HandleTypeDef *hi2cx, uint32_t DevAddr, char *str);



#endif /* INC_LCD_I2C_H_ */
