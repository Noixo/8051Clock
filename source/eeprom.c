#include "eeprom.h"
#include "i2c.h"
#include "timing.h"

//Code for the AT24C32

//must have 10ms delay minimum after writing a byte
void eepromWriteByte(unsigned char addr1, unsigned char addr2, unsigned char value)
{
	//ensures user doesn't input an invalid address space
	addr2 &= 0x0F;
	
	i2c_start();
	i2c_device_id(at24, 0);
	i2c_write(addr1);
	i2c_write(addr2);
	
	i2c_write(value);
	i2c_stop();
	
	ms_delay(10);
}

unsigned char readByte()
{
	unsigned char value;
	i2c_start();
	i2c_device_id(at24, 1);
	value = i2c_read(1);
	i2c_stop();
	
	return value;
}

unsigned char eepromRandomRead(unsigned char addr1, unsigned char addr2)
{
	//dummy write
	i2c_start();
	i2c_device_id(at24,0);
	
	//writing to address you want to read
	i2c_write(addr1);
	i2c_write(addr2);
	
	return readByte();
}