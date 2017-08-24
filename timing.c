#include "timing.h"

void ms_delay(unsigned char num)	//1 miliseconds
{
	unsigned char i;
	TMOD = 0x01;	//TMOD becomes mode: 1 (16 bit timer)
	
	// Time is 1/(crystal(mhz)/12(prescaler)) = x uS
	//Time needed is 65536-x = value for TH & TL

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

void us_delay(unsigned char num)	//30 microsecond
{
	//unsigned char i;
	
	//for(i = 0; i < num; i++)
		//_nop_();
	TMOD = 0x01; //TMOD = 0x00;	//TMOD becomes mode: 0 (8 bit timer)
	
	//for(i = 0; i < num; i++)
	//{
	TH0 = 0xFF;	// Upper 8 bits
	TL0 = 0xF1;	//Lower 8 bits
	TR0 = 1;		//Starts the timer

	while(TF0 == 0);
	TR0 = 0;		//Turns off timer
	TF0 = 0;		//Clears overflow tag
	//}
}

void timer2(void)	//For fixing DHT11 freezes
{
	//TMOD
}