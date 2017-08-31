#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"

void main()
{
	unsigned char a[7];
	char ack, i;
	//SETUP
	
	//INTERRUPTS
		//EXT0 for backlight
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	
	//EXT1 for next screen
	IT1 = 1;
	EX1 = 1;
	//--------------
	
	backlight = 0;	//Turn on display
	
	//LCD init
	init();
	
	//I2C init
	i2c_setup();
	//write_string("Hello, World!\n");
	
	
	//rw low for write and high for read
	while(1)
	{
		//check_night();
		//readDHT11();
		//i2c_read_id();
		
		i2c_start();
		//write to 0x68
		ack = i2c_device_id(0x68, 0x00);
		i2c_write(0);
		
		i2c_start();
		
		ack = i2c_device_id(0x68, 0x01);
		
		//i2c_write(3);
		a[0] = i2c_read();
		
		//NEW---------------------------
		i2c_start();
		//write to 0x68
		ack = i2c_device_id(0x68, 0x00);
		i2c_write(1);
		
		i2c_start();
		
		ack = i2c_device_id(0x68, 0x01);
		
		a[1] = i2c_read();
		
		
		//NEW---------------------------
		i2c_start();
		//write to 0x68
		ack = i2c_device_id(0x68, 0x00);
		i2c_write(2);
		
		i2c_start();
		
		ack = i2c_device_id(0x68, 0x01);
		
		a[2] = i2c_read();
		
		i2c_stop();

		a[0] = (a[0] & 0x0F) + (((a[0] & 0x70) >> 4) * 10);
		a[1] = (a[1] & 0x0F) + (((a[1] & 0x70) >> 4) * 10);
		a[2] = (a[2] & 0x01) + (((a[2] & 0x10) >> 4) * 10);
		a[2] += (a[2] & 0x02) + (((a[2] & 0x20) >> 4) * 20);
		
		write_int(a[2]);
		write_char(':');
		write_int(a[1]);
		write_char(':');
		write_int(a[0]);
		
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		cmd(LCD_CLEAR);
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