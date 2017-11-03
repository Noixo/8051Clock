#include "external.h"
#include "timing.h"
//#include "LCD.h"

char screenNum = 0;

bit interruptBit = 0;

//screen1, 2 & 3 belong to main
extern void screen1();
extern void screen2();
extern void screen3();

//void screen1();
//void screen2();

void external_setup()
{
	//EXT0 for backlight
	IT0 = 1;
	EX0 = 1;
	
	//turn on 'global?' interrupts
	EA = 1;
	
	//EXT1 for next screen
	IT1 = 1;
	EX1 = 1;
	
	backlight = 0;	//Turn on display
}

void check_night()
{
	backlight =~ comparator;
	/*
	if (comparator == 0)	//If night time
	{
		backlight = 1;			//Turn off LCD backlight
	}
	else
	{
		backlight = 0;			//When daytime turn on light
	}
	*/
}

//change so that it runs timer 2 to turn on/off
void lcdBacklight() interrupt 2
{
	unsigned char i;
	
	if (comparator == 0)	//If light is not on aka night time
	{
		backlight = 0;			//Sink current (pnp transistor)
		for(i = 0; i < 25; i++);
		//	ms_delay(200);		//5 second delay
		backlight = 1;			//Pull line high to turn off pnp transistor
	}
}

//if user wants to change screen
//only changes a bit to avoid potential problems
//with exiting whatver subroutine
void nextScreen() interrupt 0
{
	interruptBit = 1;
	
	//prevents spamming
	//ms_delay(255);
	//ms_delay(255);
}

void next_screen()
{
	//reset the screen if num > 2
	screenNum &= 3;
	//if(screenNum > 2)
		//screenNum = 0;
		
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
		case 3:
			break;
	}
}
