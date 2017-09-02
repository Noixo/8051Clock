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

	us_delay(1);
	SDA = 0;
	us_delay(1);
	SCL = 0;
	us_delay(1);
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

char i2c_device_id(char id, char rw)
{
	char i, ACK;
	
	//Starting at 1 to avoid 8th bit
	for(i = 1; i < 8; i++)
	{
		SDA = ((id << i) & 0x80);	//Sends a 1 or 0 to SDA
		
		//Pulses the clock
		i2c_clock();
	}
	
	//pulses the read/write bit
	//rw low for write and high for read
	SDA = rw;
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

unsigned char i2c_read(char last_byte)
{
	char i, byte = 0;
	
	//7 bits because read/write bit not included
	for(i = 0; i < 8; ++i)
	{	
		//bitshift byte by 1
		byte <<= 1;
		
		us_delay(1);
		SCL = 1;
		
		us_delay(1);
		
		//OR byte bit with SDA
		byte |= SDA;
		//i2c_clock();
		SCL = 0;
	
		//us_delay(1);
		
		////pulse the clock
		//i2c_clock();
	}
	
	//9th bit
	
	//SDA = 1;
	
	us_delay(1);
	SCL = 1;
	
	//acknowledge data transfer/indicate last byte
	if(last_byte == 1)
		SDA = 1;
	else
		SDA = 0;
	
	us_delay(1);
	SCL = 0;
	//us_delay(1);
	
	return byte;
}

void i2c_write(unsigned char byte)
{
	char i, ACK;
	for(i = 0; i < 8; i++)
	{
		//bit shifts data by i and ANDs it to convert it to boolean
		SDA = ((byte << i) & 0x80);	//Sends a 1 or 0 to SDA
		
		//pulse the clock
		i2c_clock();
	}
	
	//For ack bit
	SDA = 1;
	
	us_delay(1);
	SCL = 1;
	//Get ack bit
	ACK = SDA;
	
	us_delay(1);
	SCL = 0;
	us_delay(1);
}

//scans the bus to find all i2c devices
void i2c_read_id()
{
	char i, ACK;
	
	//search through all valid i2c addresses 
	for(i = 8; i < 120; i++)	//7 bit addressing
	{
		i2c_start();
		
		ACK = i2c_device_id(i, 0);	//gets the ACK bit after sending i2c device address
		
		i2c_stop();
		
		//if ACK = 0 then device was found
		if(ACK == 0)
		{
			write_int(i);
			write_char(' ');
		}
	}
}
