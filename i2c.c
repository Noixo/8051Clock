#include "i2c.h"
#include "lcd.h"

void i2c_start()
{
	SCL = 1;
	SDA = 0;
}

void i2c_end()
{
	SCL = 0;
	SDA = 0;
	
	SCL = 1;
	SDA = 1;
}

void i2c_read_id()
{
	unsigned char id, i;
	
	i2c_start();
	
	for(i = 0x00; i < 0xFF; i++)	//From 0 to 255
	{
		i2c_write(i);
		if(i2c_read() == 1)
			write_int(i);			//Rewrite code later
	}
	i2c_stop();
}

void i2c_write(unsigned char word)
{
	
}

unsigned char i2c_read()
{
	unsigned char byte;
	return byte;
}