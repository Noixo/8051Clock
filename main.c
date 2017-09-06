#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
//#include "serial.h"
/*
ATTACH SERIAL TO TIMER 0
TIMER 1 CHECKS DHT11

*/
void print_pressure()
{
	write_string(" PPPPhPa");
}

void print_temp()
{
	unsigned char *p_temp;
	
	//cmd(LCD_LINE_1);
	
	//cmd(LCD_CURSOR_RIGHT);
	//get temp and humidty
	p_temp = readDHT11();
	
	//print temp
	write_int(*(p_temp)+2);
	write_char(0);
	write_char(' ');
	
	//print humidity
	write_int(*(p_temp));
	write_char('%');
}

void print_screen()
{
	unsigned char *p_time;
	
	cmd(LCD_LINE_1);
	//get the time
	p_time = rtc_get_time();
	
	//print the time.
	
	//hours
	write_int(*(p_time+2));
	write_char(':');
	//minutes
	write_int(*(p_time+1));	
	write_char(':');
	//seconds
	write_int(*(p_time));
	write_char(' ');
	
	//readDHT11();
	print_temp();
	
	cmd(LCD_LINE_2);
	
	//day
	write_int(*(p_time+4));	
	write_char('/');
	//month
	write_int(*(p_time+5));
	write_char('/');
	//year
	write_int(*(p_time+6));
	//write_char(' ');
	
	print_pressure();
}

void main()
{
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

	//assign ccgram pos 0 as degrees C symbol
	customChar(degreesC, 0);
	while(1)
	{
		cmd(LCD_CLEAR);
		print_screen();
		//readDHT11();

		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		//ms_delay(255);
		//check_night();
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