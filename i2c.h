#ifndef _I2C_H_
#define _I2C_H_

sbit SDA = 0xB7;	//Bank 0, pin 3
									//Data line
sbit SCL = 0xB6;	//Bank 0, pin 2
									//Clock line

extern void i2c_setup();
extern void i2c_start();
extern void i2c_stop();
extern void i2c_read_id();
extern void i2c_write(unsigned char word);
extern unsigned char i2c_read();

//implement later
extern void i2c_slaveWrite();
extern void i2c_slaveRead();
#endif