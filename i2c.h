#ifndef _I2C.H_
#define _I2C.H_


extern void i2c_start();
extern void i2c_end();
extern void i2c_read_sig();
extern void i2c_write(char word);
extern void i2c_read();
#endif