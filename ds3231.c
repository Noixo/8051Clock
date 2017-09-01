#include "ds3231.h"
#include "i2c.h"
#include "LCD.h"

void test()
{
	//getTime.seconds = 10;
	
	//write_int(&getTime.seconds);
}

unsigned char rtcDecToBcd(unsigned char convert)
{
	//convert seconds, minutes, hours
	//date, month, years
	
	return 0;
}

unsigned char rtcBcdToDec(unsigned char convert)
{
	return 0;//(convert / (convert >> 4)) + (convert % (convert >> 4));
}

struct time rtc_get_time()
{
	//getTime;
	//char ack;
	struct time getTime;
	
	//getTime.seconds = i2c_read(0);
	i2c_start();
	
	i2c_device_id(0x68, 0);
	i2c_write(0);
	i2c_start();
	i2c_device_id(0x68, 1);
	//getTime.seconds = i2c_read(0);
	
	i2c_start();
	i2c_device_id(0x68, 0);
	i2c_write(1);
	i2c_start();
	i2c_device_id(0x68, 1);
	//getTime.minutes = i2c_read(0);
	
	i2c_start();
	i2c_device_id(0x68, 0);
	i2c_write(2);
	i2c_start();
	i2c_device_id(0x68, 1);
	//getTime.hours = rtcBcdToDec(i2c_read(0));
	
	i2c_stop();
	//multibyte request for data
	//between 0 and 7
	
	return getTime;
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

void rtc_temp()
{
	
}