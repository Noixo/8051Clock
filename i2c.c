#include "i2c.h"
#include "timing.h"
#include "lcd.h"

void i2c_setup()
{
	SDA = 1;
	SCL = 1;
}

void i2c_clock()
{
	us_delay(1);
	SCL = 1;
	us_delay(1);
	SCL = 0;
	us_delay(1);
}

void i2c_start()
{
	//Clock stays high and SDA pulled low
	SDA = 1;
	SCL = 1;

	us_delay(0);
	SDA = 0;
	us_delay(0);
	SCL = 0;
	us_delay(0);
}

void i2c_stop()
{
	//clock goes low before data
	SCL = 0;
	SDA = 0;
	us_delay(1);
	
	SCL = 1;
	us_delay(1);
	SDA = 1;
	us_delay(1);
}

char i2c_device_id(char id)
{
	char i, ACK;
	
	for(i = 1; i < 8; i++)
	{
		SDA = ((id << i) & 0x80);	//Sends a 1 or 0 to SDA
		
		//Pulses the clock
		i2c_clock();
	}
	//pulses the read/write bit
	SDA = 0;
	//pulse the clock
	i2c_clock();
	
	//Pull sda high to ack bit
	SDA = 1;
	
	us_delay(1);
	SCL = 1;
	//Get ack bit
	ACK = SDA;
	
	us_delay(1);
	SCL = 0;
	us_delay(1);
	
	return ACK;
}

unsigned char i2c_read(char ack)
{
	char i, byte = 0;
	
	SDA = 1;
	
	for(i = 0; i < 8; i++)
	{
		//us_delay(1);
		SCL = 1;
		us_delay(1);
		
		byte <<= 1;
		byte |= SDA;
		
		SCL = 0;
	}
	
	SCL = 1;
	us_delay(1);
	SDA = ack;
	SCL = 0;
	
	return byte;
}

void i2c_write(unsigned char byte)
{
	char i;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		us_delay(1);
		
		SDA = (byte & 0x80);	//1 or 0
		byte <<= 1;
		us_delay(1);
		SCL = 1;
	}
	
	//For ack bit
	SDA = 1;
}

//scans the bus to find all i2c devices
void i2c_read_id()
{
	char i, ACK;
	
	for(i = 8; i < 120; i++)	//7 bit addressing
	{
		i2c_start();
		
		ACK = i2c_device_id(i);	//gets the ACK bit after sending i2c device address
		
		i2c_stop();
		
		//if ACK = 0 then device was found
		if(ACK == 0)
		{
			write_int(i);
			write_char(' ');
		}
	}
}
