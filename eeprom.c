#include "eeprom.h"
#include "i2c.h"
#include "timing.h"

//Code for the AT24C32 

//must have 10ms delay minimum after writing a byte
void eepromWriteByte(unsigned char addr1, unsigned char addr2, unsigned char value)
{
	//turns off interrupts to protect data saving
	EA = 0;
	
	i2c_start();
	i2c_device_id(at24, 0);
	i2c_write(addr1);
	i2c_write(addr2);
	
	//i2c_stop();
	
	i2c_write(value);
	i2c_stop();
	
	EA = 1;
}
/*
void eepromWritePage(unsigned char* addr, unsigned char value)
{
	unsigned char i;
	
	//for(i = 0; i < )
}
*/

/*
char wearCheck()
{
	unsigned char i, j, wear = 0;
	
	// fill each location in eeprom, alternating 0 and 1
	for(i = 0; i <  0xF; i++)
	{
		for(j = 0; j < 0xFF; j++)
		{
			eepromWriteByte(i, j, wear);
			wear ^= 1;
			
			serial_convert(i);
			serial_send(' ');
			//if(eepromReadByte() != wear)
				//return -1;
			ms_delay(10);
		}
	}
	//check if value is not 1 or 0
	return 0;
}
*/

unsigned char readByte()
{
	unsigned char value;
	i2c_start();
	i2c_device_id(at24, 1);
	value = i2c_read(1);
	i2c_stop();
	
	//write_int(value);
	
	return value;
}

unsigned char eepromRandomRead(unsigned char addr1, unsigned char addr2)
{
	//dummy write
	i2c_start();
	i2c_device_id(at24,0);
	
	i2c_write(addr1);
	i2c_write(addr2);
	
	return readByte();
}
/*
unsigned char* eepromReadPage(unsigned char* addr)
{
	return 0;
}
*/