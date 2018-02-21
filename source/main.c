/*! \mainpage
* @Author M Whiteley\n
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
#include "timing.h"
#include "i2c.h"
#include "ds3231.h"
#include "bmp280.h"
#include "eeprom.h"
#include "serial.h"
#include "uartCmd.h"
#include "display.h"
#include "eepromSubroutine.h"

#include "debug.h"

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

//---------------------------------------------------

//BMP280
#define CTRL_MEAS 0xF4
#define CONFIG 0xF5

//---------------------------------------------------

//global variables to store sensor data
volatile unsigned char *p_time;
volatile unsigned char *p_dht11;
volatile short bmpTemp;
volatile unsigned long bmpPressure;

//stores bmpTemp and bmpPressure without decimal
volatile char INTbmpTemp;
volatile unsigned short INTbmpPressure;

//idk if this is safe
unsigned char screenNum;
unsigned DHTcounter;

//2 = 0.5 second since 2, 250ms delays used
#define DELAYTIME 8

//pin blocks to pull up
//0x80 has no pullups
sfr blockOne = 0x90;
sfr blockTwo = 0xA0;
sfr blockThree = 0xB0;

sbit comparator = 0x92;
sbit next = 0x90;// 0x94;
sbit onBacklight = 0x91;
sbit backlight = 0x93;

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
	
	//check if 2.5 seconds have passed
	if(DHTcounter == DELAYTIME)
	{
		DHTcounter = 0;
		p_dht11 = readDHT11();
	}
	else
	{
		DHTcounter++;
	}
	
	//removes decimal part
	INTbmpTemp = bmpTemp / 100;
	INTbmpPressure = bmpPressure / 100;
	
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

//check button inputs
void buttonCheck()
{
	//check left button (backlight)
	
	//check right button (next screen)
	if(next == 1)
	{
			//allow next screen
			screenNum++;
			
			//clear screen to prevent garbage characters from old screens
			cmd(LCD_CLEAR);
	}
}

void main()
{
	//------------------------------------------------------------------
	//initalise components
		
	//pulling all pins high for power saving
	blockOne = 0xFF;
	blockTwo = 0xFF;
	blockThree = 0xFF;
	
	//pull button inputs low
	onBacklight = 0;
	next = 0;
	
	init_timing();
	
	init_serial();
	
	//init_external();
	backlight = 0;	//Turn on display
	
	//LCD init
	init_lcd();
	backlight = 0;
	
	//I2C init
	init_i2c();
	
	//assign ccgram pos 0 as degrees C symbol
	customChar(degreesC, 0);

	bmpReset();
	
	//setting up sampling parameters
	bmpSet(0x64, CONFIG); //standby time = 250ms, IIR filter = 
	bmpSet(0xFF, CTRL_MEAS); //x16 temperature oversampling, x16 pressure measurement, normal mode
	//------------------------------------------------------------------

	while(1)
	{
		//read and store sensor data as well as update display
		updateData();
		//debug();
		
		//check and store MAX and MIN sensor data
		//writeSensorData();
		
		//check if UART command was sent
		uartCheck();
		
		//delay to prevent excessive i2c reads
		ms_delay(250);
		buttonCheck();
		ms_delay(250);
		buttonCheck();
		ms_delay(250);
		
		//turns off LCD display if night time
		backlight =~ comparator;
	}
}

/*How writing time will work

check if a single key was sent e.g. c for clock
then go into a new subroutine where all stuff freezes
until a clock time is inputted or timeout occurs.

*/

/* focus TODO
	- DHT11 timer to prevent lock ups
	- finish writing sensor data
	- finish writing hourly sensor data
	- make space to add check0(); for screen3
*/

//ds3231 call BCD
// move BCD to subroutine

/*
	--------------TODO---------------
	* Add interupt to break DHT11 if stuck for too long
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