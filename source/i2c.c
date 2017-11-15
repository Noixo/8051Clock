#include "i2c.h"
#include "timing.h"
//#include "lcd.h"

void init_i2c()
{
	SDA = 1;
	SCL = 1;
}

void i2c_clock()
{
	SCL = 1;
	us_delay();
	SCL = 0;
}

void i2c_start()
{
	//Clock stays high and SDA pulled low
	SDA = 1;
	SCL = 1;

	us_delay();
	SDA = 0;
	us_delay();
	SCL = 0;
}

void i2c_stop()
{
	//clock goes low before data
	SCL = 0;
	SDA = 0;
	us_delay();
	
	SCL = 1;
	us_delay();
	SDA = 1;
}

char i2c_device_id(char id, char rw)
{
	char i, ACK;
	
	//check if valid i2c address
	if(id < 8 || id > 120)
		return 2;
	
	//Starting at 7 to avoid last bit
	//for(i = 1; i < 8; i++)
	for(i = 7; i > 0; i--)
	{
		id <<= 1;
		SDA = id & 0x80;	//Sends a 1 or 0 to SDA
		
		//Pulses the clock
		i2c_clock();
	}
	//8th bit. pulses the read/write bit
	//rw low for write and high for read
	SDA = rw;
	
	//pulse the clock
	i2c_clock();
	
	//9th bit
	//Pull sda high to ack bit
	SDA = 1;
	i2c_clock();
	ACK = SDA;
	
	/*
	us_delay();
	SCL = 1;
	//Get ack bit
	
	us_delay();
	SCL = 0;
	*/
	return ACK;
}

unsigned char i2c_read(char last_byte)
{
	char i, byte = 0;
	SDA = 1;
	
	for(i = 8; i > 0; i--)
	{	
		SCL = 1;
		//bitshift byte by 1
		byte <<= 1;
		
		//OR byte bit with SDA
		byte |= SDA;
		i2c_clock();
		//us_delay();
		
		//SCL = 0;
	}
	
	//9th bit master acknowledges data transfer or indicates last byte
	SDA = last_byte;	
	
	i2c_clock();
	//SDA = 1;
	return byte;
}

void i2c_write(unsigned char byte)
{
	char i;//, ACK;
	for(i = 8; i > 0; i--)
	{
		//bit shifts data by i and ANDs it to convert it to boolean
		SDA = byte & 0x80;	//Sends a 1 or 0 to SDA
		
		//pulse the clock
		i2c_clock();
		
		byte <<= 1;
	}
	
	//set to high to detect ack bit
	SDA = 1;
	
	i2c_clock();

	/*
	Get ack bit
	ACK = SDA;
	*/
}
/*
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
*/