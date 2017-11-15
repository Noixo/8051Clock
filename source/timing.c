#include "timing.h"
#include <intrins.h>
#include "i2c.h"

//#include <reg51.h>
void init_timing()
{
	TMOD |= 0x01;	//Turns on mode 1 16 bit timer for timer 0
	//EAÅ = 1;
}

// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
//Time needed is 65536-x = value for TH & TL
void ms_delay(unsigned char num)	//1 miliseconds
{
	unsigned char i;

	for(i = 0; i < num; i++)
	//for(i = num; i > 0; i--)
	{
		TH0 = 0xFC;	//Upper 8 bits
		TL0 = 0x17;	//Lower 8 bits
		TR0 = 1;           	//Starts the timer

		while(TF0 == 0);		//loops till timer overflow bit = 1
		TF0 = 0;           	//clear the timer Over flow flag
	}
	TR0 = 0;						//Turns off the timer
}

//aaprox 5.43us
void us_delay()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

//approx 41.2
void lcdDelay()
{
	TH0 = 0xFF;	//Upper 8 bits
	TL0 = 0xE3;	//Lower 8 bits
	TR0 = 1;		//Starts the timer

	while(TF0 == 0);		//loops till timer overflow bit = 1
	TF0 = 0;           	//clear the timer Over flow flag
	
	TR0 = 0;						//Turns off the timer
}

/*
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
	
}
*/