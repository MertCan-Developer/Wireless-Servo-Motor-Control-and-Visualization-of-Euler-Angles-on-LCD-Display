#ifndef BNO055_PORT_BNO055_PORT_H_
#define BNO055_PORT_BNO055_PORT_H_

#include "stm32f0xx.h"
#include "bno055.h"


s8 bno055_write (u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 wr_len);
s8 bno055_read (u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 wr_len);
void bno055_delay(u32 period);


#endif /* BNO055_PORT_BNO055_PORT_H_ */
