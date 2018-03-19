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

//#include "debug.h"

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
//---------------------------------------------------

//BMP280
#define CTRL_MEAS 0xF4
#define CONFIG 0xF5

//MAIN
#define DELAYLENGTH 6 //length of the delay between screen updates
#define BACKLIGHTDELAY 10 //length of time delay for keeping the backlight on


//UPDATEDATA
//delay 2 seconds / delay time = DHT11DELAYTIME
#define DHT11DELAYTIME 6

//---------------------------------------------------

//global variables to store sensor data
volatile unsigned char *p_time;
volatile unsigned char *p_dht11;
volatile short bmpTemp;
volatile unsigned long bmpPressure;

//stores bmpTemp and bmpPressure without decimal
volatile char INTbmpTemp;
volatile unsigned short INTbmpPressure;

unsigned char screenNum;	//stores current screen number
unsigned char DHTcounter;	//stores num of cycles until DHT11 can be read again

unsigned char backlightBool;

//---------------------------------------------------

//pin blocks to pull up
//0x80 has no pullups
sfr blockOne = 0x90;
sfr blockTwo = 0xA0;
sfr blockThree = 0xB0;

sbit comparator = 0x92;		//op-amp comparator output
sbit next = 0x90;					//loads the next display
sbit onBacklight = 0x91;	//backlight buton
sbit backlight = 0x93;		//connected to display 

//---------------------------------------------------

/**
* runs and stores the latest data from sensors.
* next_screen takes the latest stored data from
* sensors and refreshes the current screen.
*/
void updateData()
{
	//pulls data from sensors
	p_time = rtc_get_time();
	bmpTemp = bmp280GetTemp();
	bmpPressure = bmp280GetPressure();
	
	DHTcounter++;
	
	//DHT11 requires 2 seconds between measurements
	//check if 2 seconds have approximately passed
	if(DHTcounter == DHT11DELAYTIME)
	{
		DHTcounter = 0;
		p_dht11 = readDHT11();
	}
	
	//removes decimal part
	INTbmpTemp = bmpTemp / 100;
	
	if(screenNum > 2) //reset the screen if num > 2
		screenNum = 0;
	
	//Go to next screen/refresh current with latest data
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
	}
}

//check button inputs
void buttonCheck()
{
	//check left button (backlight)
	if(onBacklight == 1)	//if button pushed, turn on backlight
	{
			backlightBool = 1;	//indicate that the timer is on
			backlight = 0;	//logic low turns on display
	}
	
	//check right button (next screen)
	if(next == 1)
	{
			//allow next screen
			screenNum++;
			
			//clear screen to prevent garbage characters from old screens
			cmd(LCD_CLEAR);
		
			//prevent skipping of screens
			ms_delay(100);
	}
}

void daylightSavingCheck()
{
	if(*(p_time + 5) >= 10 && *(p_time + 5) <= 4)	//check if month in daylight savings region
	{
		if(*(p_time + 3) == 7)	//if day is sunday
		{
			*(p_time + 2) += 1;		//increase if daylight savings. Won't cause issue since time reset every cycle
			
			if(*(p_time + 2) > 24) //correction to prevent invalid hour
				*(p_time + 2) = 0;
		}
			//*(p_time + 4)++;		//increase date if daylight savings
	}
	//no daylight savings. Do nothing
}

void main()
{
	//for delay length loop
	char i;
	unsigned char backlightCount; //stores the number of counts the backlight has been on for
	
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
		//check if it's daylight savings
		daylightSavingCheck();
		
		//read and store sensor data as well as update display
		updateData();
		
		//check and store MAX and MIN sensor data
		//writeSensorData();
		
		//check if UART command was sent
		uartCheck();
		
		//delay to prevent excessive i2c reads and checks if button input
		for(i = 0; i < DELAYLENGTH; i++)	//delay per screen update
		{
			ms_delay(100);
			buttonCheck();
		}
		
		//check if backlight has been on for correct amount of time and resets if so
		if(backlightCount > BACKLIGHTDELAY)
		{
			//reset counters
			backlightCount = 0;
			backlightBool = 0;
		}
		
		//start counting if flag is set
		if(backlightBool == 1)
			backlightCount++;

		//turns off LCD display if night time and button delay expired
		if(onBacklight == 0 && !backlightCount)
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

/*	BUGS
	
	* BMP280 pressure, decimal values. if value is 1007.3, it often means 1007.03
*/

/*	OPTIMISATION
		-i2c generic write function for bmp280,
		- replace hardware values with reg51.h
*/