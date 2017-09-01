#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"

void main()
{
	//char ack;
	//unsigned char arr[3];
	//struct time getTime();
	//struct time getTime;
	//SETUP
	
	//INTERRUPTS
	external_setup();
	
	//LCD init
	init();
	
	//I2C init
	i2c_setup();

//	struct time getTime;
	//write_string("Hello, World!\n");
	
	//rw low for write and high for read
	while(1)
	{
		//getTime = &rtc_get_time();
		
		write_int(getTime->hours);
		write_char(':');
		write_int(getTime->minutes);
		write_char(':');
		write_int(getTime->seconds);
		/*
		i2c_start();
		
		ack = i2c_device_id(0x68, 0);
		
		//i2c_start();
		
		i2c_write(0);
		
		i2c_stop();
		
		i2c_start();
		ack = i2c_device_id(0x68, 1);
		
		arr[0] = i2c_read(0);
		arr[1] = i2c_read(0);
		arr[2] = i2c_read(1);
	
		i2c_stop();
		
		arr[0] = (arr[0] & 0x0F) + (((arr[0] & 0x70) >> 4) * 10);
		arr[1] = (arr[1] & 0x0F) + (((arr[1] & 0x70) >> 4) * 10);
		//arr[2] = ((arr[2] / (arr[2] >> 4)) + (arr[2] % a[2] >> 4));
		
		write_int(arr[2]);
		write_char(':');
		write_int(arr[1]);
		write_char(':');
		write_int(arr[0]);
		*/
		//test();
		//write_int(setTime.seconds);
		//write_int(getTime.minutes);
		//write_int(getTime.hours);
		
		//check_night();
		//readDHT11();
		//i2c_read_id();
		/*
		a[0] = (a[0] & 0x0F) + (((a[0] & 0x70) >> 4) * 10);
		a[1] = (a[1] & 0x0F) + (((a[1] & 0x70) >> 4) * 10);
		a[2] = (a[2] & 0x01) + (((a[2] & 0x10) >> 4) * 10);
		a[2] += (a[2] & 0x02) + (((a[2] & 0x20) >> 4) * 20);
		
		write_int(a[2]);
		write_char(':');
		write_int(a[1]);
		write_char(':');
		write_int(a[0]);
		*/
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		cmd(LCD_HOME);
	}
}

/*
	--------------TODO---------------
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	BMP280
		- DS3231
	* Add interupt to break DHT11 if stuck for too long
	* 
*/

/*
	---------------Small issues--------------
	* timer not accurate
	* i2c.c needs lcd.c to print variable. Not efficient
*/

/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/