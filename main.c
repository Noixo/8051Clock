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

	/*
	matrixSend(0x01, bcdToDec(*(p_time)));
	
	matrixSend(0x02, bcdToDec(*(p_time+1)));
	matrixSend(0x03, bcdToDec(*(p_time+2)));
	*/
	
	//seconds
	matrixSend(0x01, (*(p_time) & 0x0F));
	serial_convert((*(p_time) & 0x0F));

	matrixSend(0x02, (*(p_time)/10 & 0x0F));
	serial_convert((*(p_time)/10 & 0x0F));
	serial_send(' ');
	
	//minutes
	matrixSend(0x03, (*(p_time+1) & 0x0F));
	serial_convert((*(p_time+1) & 0x0F));
	
	matrixSend(0x04, (*(p_time+1)/10 & 0x0F));
	serial_convert((*(p_time+1)/10 & 0x0F));
	serial_send(' ');
	
	//hours
	matrixSend(0x05, (*(p_time+2) & 0x0F));
	serial_convert((*(p_time+2) & 0x0F));
	
	matrixSend(0x06, (*(p_time+2)/10 & 0x0F));
	serial_convert((*(p_time+2)/10 & 0x0F));
	serial_send(' ');
	
	serial_send('\r');
	serial_send('\n');
	
		/*
		maxTest(0x04, (*(p_time)+4));
		maxTest(0x05, (*(p_time)+5));
		maxTest(0x06, (*(p_time)+6));
		maxTest(0x07, (*(p_time)+3));
	*/
	//cmd(LCD_LINE_2);
	
	print_pressure();
}

void main()
{
	unsigned char i, j = 0;
	//unsigned char *p_bmp280;
//	unsigned char *p_time;
	
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
	
	//ms_delay(100);
	//bmpReset();
	
	matrixInit();
	matrixClear();
//	matrixSend(1, 0x255);
	//ms_delay(255);
	//x8 prssure oversample, x8 temperature oversample & forced mode
	bmpSet(0x92);
	
	//first is column second is value for column
	while(1)
	{
		
		(void) bmp280GetData();
		//cmd(LCD_HOME);//CLEAR);
		//print_screen();
		//print_screen();
		
		//(void) readDHT11();
		/*
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		ms_delay(255);
		*/
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
	* make ds3231 getData get temperature as well
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
*/