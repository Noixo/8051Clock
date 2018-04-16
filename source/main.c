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
	0: RESERVED FOR Daylight savings or maybe status idk idc
	maybe bit to turn off DHT11 readings?
	1: max temp			1 byte signed
	2: min temp			1 byte signed
	3: max humidity 1 byte singed/unsigned
	4: min humidity 1 byte singed/unsigned
	5-6: max pressure 2 bytes unsigned
	7-8: min pressure 2 bytes unsigned
	
	pos 0-8 used
	
*/
//---------------------------------------------------

//BMP280
#define CTRL_MEAS 0xF4
#define CONFIG 0xF5

//MAIN
#define DELAYLENGTH 6 //length of the delay between screen updates
#define BACKLIGHTDELAY 10 //length of time delay for keeping the backlight on

//
#define MONTH 5	//define DS3231 month location
#define DAY 3 //define DS3231 day (mon,tues,wed ect) location
#define HOUR 2 // define DS3231 hour location

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

void daylightSavingCheck()
{
	if(*(p_time + MONTH) >= 10 && *(p_time + MONTH) < 4)	//check if month in daylight savings region
	{
		*(p_time + HOUR) += 1;		//increase if daylight savings

		if(*(p_time + HOUR) > 23) //correction to prevent invalid hour
		{
			*(p_time + HOUR) = 0;
			*(p_time + DAY) += 1;	//change day
		}	//WARNING: THIS CAN CAUSE A DODGY MONTH
	}
}

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
	
	DHTcounter--;
	
	//DHT11 requires 2 seconds between measurements
	//check if 2 seconds have approximately passed
	if(DHTcounter == 0)
	{
		DHTcounter = DHT11DELAYTIME;
		p_dht11 = readDHT11();
	}
	//check if it's daylight savings
	daylightSavingCheck();
	
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
	//500 ms delay to allow caps to charge
	ms_delay(0xFF);
	ms_delay(0xFF);
	
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
	
	//initial readings on power on (mostly used to ensure EEPROM gets correct value)
	p_dht11 = readDHT11();
	bmp280GetTemp();
	
	//------------------------------------------------------------------
	while(1)
	{		
		//check if UART command was sent
		uartCheck();
		
		//read and store sensor data as well as update display
		updateData();
		
		//check and store MAX and MIN sensor data
		writeSensorData();
		
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