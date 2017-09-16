#include "bmp280.h"
#include "i2c.h"
#include "lcd.h"
#include "serial.h"

void bmpReset()
{
	i2c_start();
	(void) i2c_device_id(bmp280, 0);
	i2c_write(0xE0);
	
	i2c_start();
	(void) i2c_device_id(bmp280, 0);
	i2c_write(0xB6);
	i2c_stop();
}

unsigned char* bmp280GetData()
{
	char i;
	unsigned char bmp280Data[22];
	
	//begin multi-byte data transfer
	i2c_start();
	(void) i2c_device_id(bmp280, 0);
	//start at 0xF0-0xFC
	i2c_write(0xF0);
	
	i2c_start();
	(void) i2c_device_id(0x76, 1);
	
	//7 registers 3 bytes sent per resister
	for(i = 0; i < 22; i++)
	{
		if(i == 21)
		{
			bmp280Data[i] = i2c_read(1);
		}
		else
		{
			bmp280Data[i] = i2c_read(0);
		}
	}
	i2c_stop();
	//debug
	for(i = 0; i < 22; i++)
	{
		serial_send(i);
		serial_send_array(": ");
		serial_convert(bmp280Data[i]);
		serial_send('\r');
		serial_send('\n');
	}
	//serial_convert(bmp280Temp[0]);
	write_int(bmp280Temp[0]);
	
	return bmp280Data;
}

//void unsigned char*