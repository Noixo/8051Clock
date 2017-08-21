#include "i2c.h"
#include "lcd.h"

void i2c_setup()
{
	SCL = 1;
	SDA = 1;
}

void i2c_start()
{
	SDA = 1;
	SCL = 1;
	
	SDA = 0;
	SCL = 0;
}

void i2c_stop()
{
	SCL = 0;
	SDA = 0;
	
	SCL = 1;
	SDA = 1;
}

void i2c_ack()
{
	SDA = 0;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}

void i2c_read_id()
{
	unsigned char i;
	
	for(i = 0x00; i < 0xFF; i++)	//From 0 to 255
	{
		//i2c_start();
		
		i2c_write(i);
		
		if(i2c_read() == 1)
			write_int(i);			//Rewrite code later
	}
	i2c_stop();
}

void i2c_write(unsigned char word)
{
	unsigned char i;
	
	for(i = 0; i < 8; i++)
	{
		if((word & 0x80))
			SDA = 1;
		else
			SDA = 0;
		
		word <<= 1;
		
		SCL = 1;
		SCL = 0;
	}
//	SCL = 1;
	while(SCL);
	
	//SCL = 1;
	SCL = 0;
}

unsigned char i2c_read()
{
	unsigned char byte, i;
	
	for(i = 0; i < 8; i++)
	{
		byte <<= 1;
		SCL = 1;
		byte |= SDA;
		SCL = 0;
	}
	return byte;
}