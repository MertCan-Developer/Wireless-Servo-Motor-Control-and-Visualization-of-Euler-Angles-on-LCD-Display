#include "bno055_port.h"

extern I2C_HandleTypeDef hi2c1;

s8 bno055_write (u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 wr_len)
{
	dev_addr = ((dev_addr << 1U) | 0x0U);
	HAL_I2C_Mem_Write(&hi2c1, dev_addr, reg_addr, 1U, reg_data, wr_len, 100);
	return ( BNO055_SUCCESS );
}

s8 bno055_read (u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 wr_len)
{
	dev_addr = ((dev_addr << 1U) | 0x1U);
	HAL_I2C_Mem_Read(&hi2c1, dev_addr, reg_addr, 1U, reg_data, wr_len, 100);
	return ( BNO055_SUCCESS );
}

void bno055_delay(u32 period)
{
	HAL_Delay(period);
}

















