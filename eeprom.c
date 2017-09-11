#include "eeprom.h"
#include "i2c.h"

void eepromWriteByte(unsigned char addr1, unsigned char addr2, unsigned char value)
{
	i2c_start();
	i2c_device_id(at24, 0);
	i2c_write(addr1 & 0x0F);
	i2c_write(addr2);
	
	i2c_write(value);
	i2c_stop();
}

void eepromWritePage(unsigned char* addr, unsigned char value)
{
	unsigned char i;
	
	//for(i = 0; i < )
}

//unsigned char eepromSequencial

unsigned char eepromReadByte(unsigned char addr1, unsigned char addr2)
{
	unsigned char value;
	
	i2c_start();
	i2c_device_id(at24,0);
	
	i2c_write(addr1 & 0x0F);
	i2c_write(addr2);
	
	//i2c_stop();
	i2c_start();
	
	i2c_device_id(at24, 1);
	value = i2c_read(1);
	i2c_stop();
	
	return value;
}
/*
unsigned char* eepromReadPage(unsigned char* addr)
{
	return 0;
}
*/