#include "ds3231.h"
#include "i2c.h"

void test()
{
	//getTime.seconds = 10;
	
	//write_int(&getTime.seconds);
}

unsigned char rtcDecToBcd(unsigned char convert)
{
	return ((convert / 10 * 16) + (convert % 10));
}

unsigned char rtcBcdToDec(unsigned char convert)
{
	return ((convert / 16 * 10) + (convert % 16));
}

/*
unsigned char* rtc_temp()	//rewrite
{
	unsigned char temp[1];
	
	i2c_start();
	i2c_device_id(0x68, 0);
	i2c_write(0x11);
	i2c_stop();
	
	i2c_start();
	i2c_device_id(0x68, 1);
	temp[0] = i2c_read(0);
	
	i2c_start();
	
	i2c_device_id(0x68, 0);
	i2c_write(0x12);
	i2c_stop();
	
	i2c_start();
	i2c_device_id(0x68, 1);
	temp[1] = i2c_read(0) >> 6;
	
	return temp;
}
*/
unsigned char* rtc_get_time()	//rewrite
{
	static unsigned char time[6];
	char i;
	
	//make multi-btye access work
	for(i = 0; i < 7; i++)
	{
		i2c_start();
		i2c_device_id(0x68, 0);
		i2c_write(i);
		i2c_stop();
		i2c_start();
		i2c_device_id(0x68, 1);
		time[i] = rtcBcdToDec(i2c_read(0));
		i2c_stop();
	}
	return time;
}

void rtc_set_time()
{
	char ack;
	//multi-byte set time
	
	i2c_start();
	ack = i2c_device_id(0x68, 1);
	i2c_write(0);	//point to seconds
	
	i2c_start();
	
	i2c_write(0);
	
}