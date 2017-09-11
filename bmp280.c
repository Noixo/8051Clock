#include "bmp280.h"
#include "i2c.h"
#include "lcd.h"
unsigned char* bmp280GetData()
{
	static unsigned char bmp280Temp[3];
	//unsigned char temp[1];
	i2c_start();
	
	(void) i2c_device_id(0x76, 0);
	//get temp
	i2c_write(0xD0);//0xFA);
	i2c_stop();
	
	i2c_start();
	(void) i2c_device_id(0x76, 1);
	bmp280Temp[0] = i2c_read(1);
	
	//bmp280Temp[1] = i2c_read(0);
	//bmp280Temp[2] = i2c_read(1);
	i2c_stop();
	write_int(bmp280Temp[0]);
	return bmp280Temp;
}

//void unsigned char*