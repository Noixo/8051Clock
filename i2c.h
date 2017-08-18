#ifndef _I2C_H_
#define _I2C_H_

sbit SDA = 0xB6;	//Bank 3, pin 6
									//Clock line
sbit SCL = 0xB5;	//Bank 3, pin 5
									//Data line

extern void i2c_start();
extern void i2c_stop();
extern void i2c_read_id();
extern void i2c_write(unsigned char word);
extern unsigned char i2c_read();
#endif