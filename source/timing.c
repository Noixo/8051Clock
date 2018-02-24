#include "timing.h"
#include <intrins.h>

void init_timing()
{
	TMOD |= 0x01;	//Turns on mode 1 16 bit timer for timer 0
}

// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
//Time needed is 65536-x = value for TH & TL
void ms_delay(unsigned char num)	//1 miliseconds
{
	unsigned char i;

	//for(i = 0; i < num; i++)
	for(i = num; i > 0; i--)
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

//31us delay?
void dht11Delay()
{
	TH0 = 0xFF;
	TL0 = 0xF1;
	
	TR0 = 1;	//start timer
	
	while(TF0 == 0);		//loops till timer overflow bit = 1
	TR0 = 0;						//Turns off the timer
	TF0 = 0;           	//clear the timer Over flow flag
}

//approx 41.2us?
void lcdDelay()
{
	TH0 = 0xFF;	//Upper 8 bits
	TL0 = 0xE3;	//Lower 8 bits
	TR0 = 1;		//Starts the timer

	while(TF0 == 0);		//loops till timer overflow bit = 1
	TR0 = 0;						//Turns off the timer
	TF0 = 0;           	//clear the timer Over flow flag
}
/*
//start timer, when overflow jump to a counter. When counter reaches number, cancel
void dhtInterrupt() 
{
	TMOD = 0x10;//0x10; // mode 1 timer for timer 1?
	
	ET1 = 1;
	
	TH1 = 0x00;
	TL1 = 0x00;
	
	TR1 = 1;	//starts the timer
}
*/