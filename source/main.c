/*! \mainpage
* @Author Matthew Whiteley\n
* @Date 
* @brief 8051 clock and data logging program.
* \section Sensor specs:
*	- BMP280:\n
*	Pressure:\n
*		Range:300-1100hPa\n
*		Accuracy: +- 0.12hPa @ 25*C\n
*	Temperature:\n
*		Range: -40-85*C\n
*		Accuracy: +-1*C ?\n
*	\n
* - DS3231:
*	\n
* - DHT11
*		Temperature: \n
*			Range: 0-50*C\n
*			Accuracy: +- 2*C\n
*		Humidity:\n
*			Range: 20-90%RH
*			Accuracy: +- 5%
*	\n
*/

#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
#include "bmp280.h"
#include "eeprom.h"
#include "serial.h"
#include "uartCmd.h"
#include "display.h"
#include "eepromSubroutine.h"

//#include "GPSTime.h"
//#include "MAX7219.h"

/*	EEPROM SENSOR
	0: max temp			1 byte signed
	1: min temp			1 byte signed
	2: max humidity 1 byte singed/unsigned
	3: min humidity 1 byte singed/unsigned
	4-5: max pressure 2 bytes unsigned
	6-7: min pressure 2 bytes unsigned
	
	pos 0-7 used
	
*/

/* EEPROM HOURLY WRITE
STORE WITHOUT DECIMAL

temp:			1 byte
humidity:	1 byte
pressure:	2 bytes
*/

//global variables to store sensor data
volatile unsigned char *p_time;
volatile long bmpTemp;
volatile unsigned long bmpPressure;
volatile unsigned char *p_dht11;

//stores bmpTemp and bmpPressure without decimal
volatile unsigned short INTbmpTemp;
volatile unsigned short INTbmpPressure;

unsigned char screenNum;

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

/**
* runs and stores the latest data from sensors.
* next_screen takes the latest stored data from
* sensors and refreshes the current screen.
*/
void updateData()
{
	p_time = rtc_get_time();
	bmpTemp = bmp280GetTemp();
	bmpPressure = bmp280GetPressure();
	//p_dht11 = readDHT11();
	
	//removes decimal part
	INTbmpTemp = bmpTemp / 100;
	INTbmpPressure = bmpPressure / 100;
	
	//readDHT11();
	
		//refreshes the current screen
	if(screenNum > 2) //reset the screen if num > 2
		screenNum = 0;
	
	//Go to next screen	
	switch(screenNum)
	{
		case 0:
			screen1();
			break;
		case 1:
			screen2();
			break;
		case 2:
			screen3();
			break;
		//case 3:
		//	break;
	}
}

void main()
{
	//sets the variable to the location of where the hour data will be
	char checkHour = *p_time+2;
	
	EEPROMSizeLED = 1;
	
	init_timing();
	
	init_serial();
	
	//INTERRUPTS
	init_external();
	
	//LCD init
	init_lcd();
	backlight = 0;
	
	//I2C init
	init_i2c();
	
	//rescan to find where last write was
	//eepromScan();
	
	//assign ccgram pos 0 as degrees C symbol
	customChar(degreesC, 0);
	
	//matrixInit();
	//matrixClear();
//	matrixSend(1, 0x255);

	bmpReset();
	bmpSet(0x64, 0xF5);
	bmpSet(0xFF, 0xF4);
	
	//main, startup screen
	//screen1();
	//778.78 pressure
	//2203
	
	while(1)
	{
		//change screen if button pushed
		if(interruptBit == 1)
		{
			//reset interrupt bit
			interruptBit = 0;
			
			//allow next screen
			screenNum++;
			
			//clear screen to prevent garbage characters from old screens
			cmd(LCD_CLEAR);
		}
		
		//read and store sensor data as well as update display
		updateData();
		
		//check and store MAX and MIN sensor data
		writeSensorData();
		
		//check if UART command was sent
		uartCheck();

		//activate every hour when time changes
		if(*(p_time+2) != checkHour)
		{
			//write latest recorded data
			
			//writeHourData();
			
			//reset pin to activate next hour
			checkHour = *(p_time+2);
		}
		
		//delay to prevent excessive i2c reads
		
		ms_delay(250);
		ms_delay(250);
		
		//check_night();
	}
}

//LED to indicate write

/*
	--------------TODO---------------
	* Add interupt to break DHT11 if stuck for too long
	* make a check in main to see if timer is up. if so run dht11 method
	* then reset timer
	* use 8x8 matrix and make a binary clock
	* make ds3231 getData get temperature as well

error checking:
- bmp280 range -40-85*C temp
	pressue range 300-1100hpa	
*/


/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/

/*	BUGS
	
	* BMP280 pressure, decimal values. if value is 1007.3, it often means 1007.03
*/

/*	OPTIMISATION
		-i2c generic write function for bmp280,
		- replace hardware values with reg51.h
*/