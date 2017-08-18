//WARNING: Timer is off by approx 3us for 1 us
// 8ms for 1000us
// 8s for 1000ms

#include "timing.h"
//#include <intrins.h>

void ms_delay(unsigned char num)	//1 miliseconds
{
	unsigned char i;
	TMOD = 0x01;	//TMOD becomes mode: 1 (16 bit timer)
	
	// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
	//Time needed is 65536-x = value for TH & TL
	
	TH0 = 0xFC;	//Upper 8 bits
	TL0 = 0x17;	//Lower 8 bits
	
	TR0 = 1;           	//Starts the timer
	for(i = 0; i < num; i++)
	{
		while(TF0 == 0);		//loops till timer overflow bit = 1
		TF0 = 0;           	//clear the timer Over flow flag
	}
	TR0 = 0;						//Turns off the timer
}

void us_delay(unsigned char num)	//10 microsecond
{
	unsigned char i;
	TMOD = 0x01; //TMOD = 0x00;	//TMOD becomes mode: 0 (8 bit timer)
	
	TH0 = 0xFF;	// Upper 8 bits
	TL0 = 0xF5;	//Lower 8 bits
	
	TR0 = 1;		//Starts the timer
	for(i = 0; i < num; i++)
	{
		while(TF0 == 0);
		TF0 = 0;		//Clears overflow tag
	}
	TR0 = 0;		//Turns off timer
}