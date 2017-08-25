#include "i2c.h"
#include "timing.h"
#include "lcd.h"

void i2c_setup()
{
	SDA = 1;
	SCL = 1;
}

void i2c_start()
{
	SCL = 1;	//Clock stays high and SDA pulled low
	ms_delay(1);
	SDA = 0;
}

void i2c_stop()
{
	SCL = 0;
	SDA = 0;
	
	SCL = 1;
	ms_delay(1);
	SDA = 1;
}

unsigned char i2c_read()
{
	char i, byte;
	for(i = 0; i < 8; i++)
	{
		byte <<= 1;
		byte |= SDA;	//??
		SCL = 1;
		ms_delay(1);
		SCL = 0;
	}
	return byte;
}

void i2c_write(unsigned char byte)
{
	char i, ACK;
	for(i = 0; i < 8; i++)
	{
		if(byte & 0x80)
			SDA = 1;
		else
			SDA = 0;
		
		byte <<= 1;
		
		SCL = 0;
		ms_delay(1);
		SCL = 1;
	}
	if(SDA == 0)
		ACK = -1;	//fail
	else
		ACK = 1;	//Pass
	
	SCL = 1;
	ms_delay(1);
	SCL = 0;
}

void i2c_read_id()
{
	char i;
	
	for(i = 0; i < 127; i++)	//7 bit addressing
		i2c_write(i);
	if(i2c_read() > 0)	//If value
		write_int(i);
}
