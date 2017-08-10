//WARNING: Timer is off by approx 3us for 1 us
// 8ms for 1000us
// 8s for 1000ms

#include "timing.h"

void ms_delay(unsigned int ms_delay)
{
	unsigned int i;
	TMOD = 0x01;	//TMOD becomes mode: 1 (16 bit timer)
	
	// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
	//Time needed is 65536-x = value for TH & TL
	
	// = 1ms
	TH0 = 0XFC;
	TL0 = 0X18;
	for(i = 0; i < ms_delay; i++)
	{
		TR0 = 1;           	//Starts the timer
		while(TF0 == 0);		//loops till timer overflow bit = 1
		TR0 = 0;						//Turns off the timer
		TF0 = 0;           	//clear the timer Over flow flag
	}
}

void us_delay(unsigned int us_delay)
{
	unsigned int i;
	TMOD = 0x01;	//TMOD becomes mode: 1 (16 bit timer)
	
	TH0 = 0XFF;	//1us hopefully
	TL0 = 0XFE;
	
	for(i = 0; i < us_delay; i++)
	{
		TR0 = 1;		//Starts the timer
		while(TR0 == 0);
		TR0 = 0;		//Turns off timer
		TF0 = 0;		//Clears overflow tag
	}
}