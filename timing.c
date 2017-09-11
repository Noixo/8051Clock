#include "timing.h"

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

void us_delay()	//37 microsecond timer
{
	TH0 = 0xFF;	// Upper 8 bits
	TL0 = 0xEE;//0xF8;	//Lower 8 bits
	TR0 = 1;		//Starts the timer

	while(TF0 == 0);
	TR0 = 0;		//Turns off timer
	TF0 = 0;		//Clears overflow tag
}

void dhtTimer()
{
	TH0 = 0xFF;
	TL0 = 0xF1;
	TR0 = 1;
	
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

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