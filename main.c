#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
#include "bmp280.h"
#include "eeprom.h"
#include "serial.h"
//#include "MAX7219.h"
/*
ATTACH SERIAL TO TIMER 0
TIMER 1 CHECKS DHT11

*/

/*	EEPROM
	0: max temp			1 byte signed
	1: min temp			1 byte signed
	2: max humidity 1 byte singed/unsigned
	3: min humidity 1 byte singed/unsigned
	4: max pressure 3 bytes unsigned
	5: min pressure 3 bytes unsigned
	
	pos 0-10 used
	
*/

unsigned char *p_time;
long bmpTemp;
long bmpPressure;

const unsigned char code max[] = "MAX/MIN: ";
//const char screenNum = 0;

/*
void print_temp()
{
	//unsigned char *p_temp;
	
	//get temp and humidty
	//p_temp = readDHT11();
	
	//print temp
	write_int(*(p_temp)+2);
	write_char(0);
	write_char(' ');
	
	//print humidity
	write_int(*(p_temp));
	write_char('%');
}
*/

//void check

//if time is < 10 add 0. e.g. 05
void check0(char number)
{
	if(number < 10)
		write_int(0);
}

void screen1()
{
	//reset to line 1 of LCD, pos 0
	//cmd(LCD_LINE_1);
	cmd(LCD_HOME);

	//--------------print the time-------------
	//hours
	check0(*(p_time + 2));
	write_int(*(p_time+2));
	write_char(':');
	
	//minutes
	check0(*(p_time + 1));
	write_int(*(p_time+1));	
	write_char(':');
	
	//seconds
	check0(*(p_time));
	write_int(*(p_time));
	write_char(' ');
	
	//cmd(LCD_LINE_2);
	
	//readDHT11();
	//print_temp();
	//ms_delay(4);
	//print temp
	write_int(bmpTemp/100);
	write_char('.');
	write_int(bmpTemp % 100);
	//write temperature symbol *c
	write_char(0);
	//write_char(' ');
	
	cmd(LCD_LINE_2);
	
	//day
	check0(*(p_time+4));
	write_int(*(p_time+4));	
	write_char('/');
	//month
	check0(*(p_time+5));
	write_int(*(p_time+5));
	write_char('/');
	//year
	check0(*(p_time+6));
	write_int(*(p_time+6));
	write_char(' ');

	write_int(bmpPressure/1000);
	write_int((bmpPressure % 1000) / 100);
	write_char('.');
	write_int(bmpPressure % 100);
	write_char(' ');
}

//show max and min temp
void screen2()
{
	unsigned char value;
	cmd(LCD_HOME);

	write_string(max);
	//get max temp
	
	value = eepromRandomRead(0,0);
	write_int(value);
	//serial_convert(value);
	write_char(0);
	
	write_char(' ');
	
	
	//get min temp
	value = eepromRandomRead(0,1);
	write_int(value);
	//serial_convert(value);
	write_char(0);
	
	//get humidity
	cmd(LCD_LINE_2);
	write_string(max);
	
	value = eepromRandomRead(0,2);
	write_int(value);
	//serial_convert(value);
	write_char('%');
	write_char(' ');
	
	value = eepromRandomRead(0,3);
	write_int(value);
	//serial_convert(value);
	write_char('%');
	
}

void screen3()
{
	char i;
	write_string("MAX: ");
	
	for(i = 4; i < 7; i++)
	{
		write_int(eepromRandomRead(0,i));
	}
	cmd(LCD_LINE_2);
	
	write_string("MIN: ");
	
	for(i = 7; i < 10; i++)
	{
		write_int(eepromRandomRead(0,i));
	}
}

//Update the values
void updateData()
{
	p_time = rtc_get_time();
	bmpTemp = bmp280GetTemp();
	bmpPressure = bmp280GetPressure();
	
	//refreshes the current screen
	switch(screenNum)
	{
		case 0:
			screen1();
			break;
		case 1:
			screen2();
			break;
	}
}

void main()
{
	init_timing();
	
	//start up delay
	ms_delay(255);
	
	init_serial();
	
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
	
	//matrixInit();
	//matrixClear();
//	matrixSend(1, 0x255);

	bmpReset();
	bmpSet(0x64, 0xF5);
	bmpSet(0xFF, 0xF4);
	
	//main, startup screen
	screen1();
	
	//first is column second is value for column
	while(1)
	{
		updateData();
		
		//cmd(LCD_LINE_1);
		
		/*
		write_int(30);
		write_int(50);
		write_int(4);
		cmd(LCD_LINE_2);
		write_int(20);
		*/
		
		
		//FIX DHT11 + INTERRUPT
		// REPLACE VARIABLES WITH reg52.h
		//readDHT11();

		//(void) readDHT11();
		
		//ms_delay(255);
		//delays + checks if button pushed
		msDelayCheck();
		msDelayCheck();
		msDelayCheck();
		//ms_delay(255);
		//ms_delay(255);
		
		//check_night();
	}
}

/*
	--------------TODO---------------
	* Add interupt to break DHT11 if stuck for too long
	* make a check in main to see if timer is up. if so run dht11 method
	* then reset timer
	* use 8x8 matrix and make a binary clock
	* make ds3231 getData get temperature as well
	
	* implement daylightsavings time 
	* time defaults to 00 rather than 0
*/

/*
	---------------Small issues--------------
	* i2c.c needs lcd.c to print variable. Not efficient
	* clean up code
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
	* BMP280 pressure, decimal values. if value is 1007.3, it often means 1007.03
	* *c symbol appears twice when seconds hand loops over e.g. 0:40:0
	* value 2 is being sent over uart
*/

/*	OPTIMISATION
		-i2c generic write function for bmp280,
		- remove redundant function from serial.c/move to sunroputine
		- replace hardware values with reg51.h
		- reduce size of bmp280 formula code
		- remove uneeded header files
*/