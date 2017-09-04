#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
#include "serial.h"
#include "math.h"

/*
ATTACH SERIAL TO TIMER 0
TIMER 1 CHECKS DHT11

*/
void main()
{
	unsigned char *p_time, *p_temp;
	char *dht11;
	
	init_serial();
	//init_serial();
	init_timing();
	//SETUP
	
	//INTERRUPTS
	external_setup();
	
	//LCD init
	lcd_init();
	backlight = 0;
	
	//I2C init
	i2c_setup();

	while(1)
	{
		/*
		p_temp = rtc_get_temp();
		write_int(*p_temp);
		write_char(' ');
		write_int(*(p_temp)+1);
		new_line();
		*/
		/*
		dht11 = readDHT11();
		
		write_int(*(dht11));
		write_char(' ');
		write_int(*(dht11+1));
		write_char(' ');

		cmd(LCD_HOME);
		serial_send_array("H: ");
		serial_convert(*(dht11));
		serial_send_array("T: ");
		serial_convert(*(dht11+1));
		serial_send('\r');
		*/
		//new_line();
		
		p_time = rtc_get_time();
		/*
		//hours
		serial_convert(*(p_time+2) & 0x3F);
		serial_send(':');
		//minutes
		serial_convert(*(p_time+1));
		serial_send(':');
		//seconds
		serial_convert(*(p_time) & 0x7F);
		serial_send(' ');
		
		//day
		serial_convert(*(p_time+4));
		serial_send('/');
		//month
		serial_convert(*(p_time+5));
		serial_send('/');
		//year
		serial_convert(*(p_time+6));
		serial_send('\r');
		*/
		//cmd(LCD_CLEAR);
		//time
		//hours
		write_int(*(p_time+2));
		write_char(':');
		//minutes
		write_int(*(p_time+1));
		write_char(':');
		//seconds
		write_int(*(p_time));
		write_char(' ');

		//date
		//day
		write_int(*(p_time+4));
		write_char('/');
		//month
		write_int(*(p_time+5));
		write_char('/');
		//year
		write_int(*(p_time+6));
		write_char(' ');
		
		cmd(LCD_HOME);
		
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		
		//check_night();
		//readDHT11();
		//a[0] = (a[0] & 0x0F) + (((a[0] & 0x70) >> 4) * 10);

	}
}

/*
	--------------TODO---------------
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	BMP280
		- DS3231
	* Add interupt to break DHT11 if stuck for too long
	* make a check in main to see if timer is up. if so run dht11 method
	* then reset timer
*/

/*
	---------------Small issues--------------
	* ds3231 not printing data correctly
	* poor ds3231 code quality and size
	* i2c.c needs lcd.c to print variable. Not efficient
*/

/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/