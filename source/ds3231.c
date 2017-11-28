#include "ds3231.h"
#include "i2c.h"
/*
unsigned char decToBcd(unsigned char convert)
{
	return ((convert / 10 * 16) + (convert % 10));
}
*/
unsigned char bcdToDec(unsigned char convert)
{
	return ((convert / 16 * 10) + (convert % 16));
}

/*
void ds3231Alarm()
{
	//point to the ALARM1 reg
	i2c_start();
	i2c_device_id(ds3231, 0);
	i2c_write(0x0A);
	
	//write ALARM1 setting
	i2c_start();
	i2c_device_id(ds3231, 0);
	//seconds & minutes
	i2c_write(12);
	
	i2c_stop();
	
	//turn on INT output from DS3231
	i2c_start();
	i2c_device_id(ds3231, 0);
	i2c_write(0x0E);
	
	i2c_start();
	i2c_device_id(ds3231, 0);
	i2c_write(1);
	
	i2c_stop();
}
*/

/*
unsigned char* rtc_get_temp()
{
	unsigned char i;
	//static unsigned char temp[1];
	
	i2c_start();
	(void) i2c_device_id(0x68, 0);
	i2c_write(0x11);	//point 1st temp register
	i2c_stop();
	i2c_start();
	
	(void) i2c_device_id(0x68, 1);
	
	i = i2c_read(0) << 8;
	i |= i2c_read(1);
	//get data, convert to two's compliment and then store in array
	//temp[0] = i2c_read(0);//toTwosComplement(i2c_read(0));
	//temp[1] = i2c_read(1);//toTwosComplement(i2c_read(1));	//last piece of data to grab
	i2c_stop();
	
	return i;
}
*/
unsigned char* rtc_get_time()
{
	static unsigned char time[8];
	char i;
	
	i2c_start();
	(void) i2c_device_id(ds3231,0);	//send address + write bit
	
	i2c_write(0);	//point to location i of DS3231
	
	//i2c_stop();
	i2c_start();
	
	(void) i2c_device_id(ds3231, 1);	//send address + read bit
	
	for(i = 0; i < 7; i++)
	{
			time[i] = bcdToDec(i2c_read(0));
	}
	time[i] = bcdToDec(i2c_read(1));	//set to not ack when 6th loop
	
	i2c_stop();
	return time;
}

void rtc_set_time(unsigned char* setTime)
{
	char i;
	//multi-byte set time
	
	i2c_start();
	(void) i2c_device_id(ds3231, 1);
	i2c_write(0);	//point to seconds
	
	//i2c_start();
	
	for(i = 0; i < 7; i++)//setTime[i] != '\0'; i++)
	{
		i2c_write(setTime[i]);
	}
	i2c_stop();
}