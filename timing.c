#include "timing.h"
#include <intrins.h>
#include "external.h"
#include "lcd.h"
#include "i2c.h"
//#include <reg51.h>
void init_timing()
{
	TMOD |= 0x01;	//Turns on mode 1 16 bit timer for timer 0
}

// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
//Time needed is 65536-x = value for TH & TL
void ms_delay(unsigned char num)	//1 miliseconds
{
	unsigned char i;

	for(i = 0; i < num; i++)
	{
		TH0 = 0xFC;	//Upper 8 bits
		TL0 = 0x17;	//Lower 8 bits
		TR0 = 1;           	//Starts the timer

		while(TF0 == 0);		//loops till timer overflow bit = 1
		TF0 = 0;           	//clear the timer Over flow flag
	}
	TR0 = 0;						//Turns off the timer
}

void msDelayCheck()	//1 miliseconds
{
	unsigned char i;
	SDA = 0;
	SDA = 1;
	for(i = 0; i < 255; i++)
	{
		TH1 = 0;	//Upper 8 bits
		TL1 = 0;	//Lower 8 bits
		TR1 = 1;           	//Starts the timer

		while(TF1 == 0)		//loops till timer overflow bit = 1
		{
			//if button pushed
			/*
			if(lcd_button == 1)
			{
				lcdBacklight();
				break;
			}
			*/
			
			if(next_screenVar == 1)
			{
				cmd(LCD_CLEAR);			//Wipe screen
				screenNum++;
				next_screen();
				TF1 = 0;
			}
			
		}
		TF1 = 0;           	//clear the timer Over flow flag
	}
	TR1 = 0;						//Turns off the timer
	SDA = 1;
}
#pragma SAVE
#pragma OPTIMIZE(8)
void us_delay()	//37 microsecond timer
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	//_nop_();
	//_nop_();
	/*
	TH0 = 0xFF;	// Upper 8 bits
	TL0 = 0xFF;//EE;//0xF8;	//Lower 8 bits
	TR0 = 1;		//Starts the timer

	while(TF0 == 0);
	TR0 = 0;		//Turns off timer
	TF0 = 0;		//Clears overflow tag
	*/
}
#pragma RESTORE
void dhtTimer()
{
	TH0 = 0xFF;
	TL0 = 0xF1;
	TR0 = 1;
	
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void dhtInterrupt1()
{
	/*
	TMOD &= 0xF0;
	TMOD |= 0x02;
	
	TH1 = 0x05;
	TL1 = 0x05;
	
	ET1 = 1;
	EA = 1;
	
	TR1 = 1;
	*/
}
/*
void dhtInterrupt() interrupt 1
{
	//clear interrupt
	TF1 = 0;
	//stop timer
	TR1 = 0;
	//main();
}
*/
/*
void us()	//4 peek-to-peek - 6us rise to fall @ 
{
	;
}
*/
void timeout()	//For fixing DHT11 freezes
{
	//TMOD
}