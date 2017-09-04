#ifndef _I2C_H_
#define _I2C_H_

sbit SDA = 0x82;	//Bank 0, pin 3
									//Data line
sbit SCL = 0x83;	//Bank 0, pin 2
									//Clock line

extern void i2c_setup();
//extern void i2c_clock();
extern void i2c_start();
extern void i2c_stop();
extern void i2c_write(unsigned char byte);
extern char i2c_device_id(char id, char rw);
extern void i2c_read_id();
extern unsigned char i2c_read(char last_byte);

//implement later
extern void i2c_slaveWrite();
extern void i2c_slaveRead();
#endif