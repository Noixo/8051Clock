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

void bmpSet(unsigned char settings, unsigned char reg)
{
	i2c_start();
	i2c_device_id(bmp280, 0);
	i2c_write(reg);
	
	//i2c_start();
	
	//i2c_device_id(bmp280, 0);
	i2c_write(settings);
	i2c_stop();
}

void bmpCalibration()
{
	char i;
	
	i2c_start();
		
	i2c_device_id(bmp280, 0);
		
	i2c_write(0x88);
		
	//quick start
	i2c_start();
	i2c_device_id(bmp280, 1);
	
	for(i = 0; i < 12; i++)
	{
		serial_convert(i2c_read(0));
		serial_send(' ');
		serial_convert(i2c_read(0));
		serial_send('\r');
		serial_send('\n');
	}
	
	serial_convert(i2c_read(1));
	i2c_stop();
	
	serial_send('\r');
	serial_send('\n');
	serial_send_array("END:");
	serial_send('\r');
	serial_send('\n');
}

//must read temp before reading pressure
//temp is stored as 3 bytes, (0xFA-0xFC)
int bmp280GetTemp()
{
	//Keil long = 4 bytes, int = 2
	static long adc_T = 0, var1 = 0, var2 = 0, t_fine = 0, T;
	
	i2c_start();
	i2c_device_id(bmp280, 0);

	i2c_write(0xFA);

	i2c_start();
	
	i2c_device_id(bmp280, 1);
	
	//shove temperature data into a 4 byte variable
	adc_T = i2c_read(0);
	adc_T <<= 8;
	adc_T |= i2c_read(0);
	adc_T <<= 8;
	adc_T |= i2c_read(1);
	i2c_stop();
	
	//conversion formula takes 20 bits
	adc_T >>= 4;

	//32bit-fixed point formula from BMP280 documentation -pg45-46 (8.2)
	var1 = ((((adc_T>>3) - ((long)dig_T1<<1))) * ((long)dig_T2)) >> 11;
  var2  = (((((adc_T>>4) - ((long)dig_T1)) * ((adc_T>>4) - ((long)dig_T1))) >> 12) * ((long)dig_T3)) >> 14;
	
	t_fine = var1+var2;
	T = (t_fine*5+128) >> 8;

	serial_convert(T/100);
	serial_send('.');
	serial_convert(T % 100);
	
	serial_send('\r');
	serial_send('\n');
	
  return (t_fine);
}

unsigned char* bmp280GetData()
{
	char i;
	unsigned char bmp280Data[5];
	
	//begin multi-byte data transfer
	i2c_start();
	(void) i2c_device_id(bmp280, 0);
	//start at 0xF7-0xFC
	i2c_write(0xFA);
	i2c_stop();
	
	i2c_start();
	(void) i2c_device_id(bmp280, 1);
	
	serial_convert(i2c_read(0));
	serial_send('\r');
	serial_send('\n');
	serial_convert(i2c_read(0));
	serial_send('\r');
	serial_send('\n');
	serial_convert(i2c_read(1));
	serial_send('\r');
	serial_send('\n');
	
	//7 registers 3 bytes sent per resister
	/*
	for(i = 0; i < 8; i++)	//22
	{
		bmp280Data[i] = i2c_read(0);
	}
	bmp280Data[i] = i2c_read(1);
	*/
	i2c_stop();
	/*
	//debug
	for(i = 0; i < 8; i++)
	{
		serial_convert(i);
		serial_send_array(": ");
		serial_convert(bmp280Data[i]);
		serial_send('\r');
		serial_send('\n');
	}
	serial_send('\r');
	serial_send('\n');
	//serial_convert(bmp280Temp[0]);
	//write_int(bmp280Temp[0]);
	*/
	return bmp280Data;
}

//void unsigned char*