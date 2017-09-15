#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
#include "bmp280.h"
#include "eeprom.h"
#include "serial.h"
#include "MAX7219.h"
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
	a = 0;
	write_int(*(p_time+2));
	a= 1;
	write_char(':');
	//minutes
	write_int(*(p_time+1));	
	write_char(':');
	//seconds
	write_int(*(p_time));
	write_char(' ');

	//readDHT11();
	//print_temp();
	
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

	
	//cmd(LCD_LINE_2);
	
	print_pressure();
}

void main()
{
	unsigned char i, j;
	unsigned char *p_bmp280;
	
	//init_serial();
	init_timing();
	
	//start up delay
	ms_delay(255);
	
	init_serial();
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
	
	//unsigned char arrs[2];// = {0,0};
	//eepromWriteByte(0,0, 0x7F);
	
	//delay so eeprom can process data
	//ms_delay(30);
	//eepromWriteByte(0,1, 0x05);
	//ms_delay(30);
	//eepromWriteByte(1,1,0x05);
	//ms_delay(10);
	while(1)
	{
		if(serial_receive() == 'd')
		{
			dumpRom();
		}
		//serial_convert(eepromRandomRead(0,1));
		/*
		for(i = 0; i < 0xF; i++)
		{
			for(j = 0; j < 0xFF; j++)
			{
				eepromWriteByte(i,j,j);
				ms_delay(15);
			}
			serial_convert(i);
		}
		
		//(void) wearCheck();
		serial_send_array(" BEGIN\n");
		serial_send('\r');
		
	
		while(1);
		*/
		/*
		for(i = 0; i < 0xFF; i++)
		{
			serial_convert(i);
			serial_send(' ');
		}
		*/
		//while(1);
		
		/*
		write_int(*p_bmp280);
		write_char(' ');
		//write_int(*(p_bmp280)+1);
		write_char(' ');
		//write_int(*(p_bmp280)+2);
		write_char(' ');
		//write_string(bmp280GetData());
		*/
		
		//cmd(LCD_HOME);//CLEAR);
		//print_screen();
		//readDHT11();
		
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		//check_night();
	}
}

/*
	--------------TODO---------------
	* i2c bit banging
		-	BMP280
	* Add interupt to break DHT11 if stuck for too long
	* make a check in main to see if timer is up. if so run dht11 method
	* then reset timer
	* use 8x8 matrix and make a binary clock
*/

/*
	---------------Small issues--------------
	* i2c.c needs lcd.c to print variable. Not efficient
*/

/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/

/*	BUGS
	* DHT11 prints correct data when printing in dht11 method but
			priting pointer reference does not
	* eeprom saved data in multiples of 2
*/