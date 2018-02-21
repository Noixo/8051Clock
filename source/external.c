//#include "external.h"
//#include "timing.h"
//#include "serial.h"
//#include "display.h"

//char screenNum = 0;

//volatile char interruptBit = 0;

/*
//screen1, 2 & 3 belong to main
extern void screen1();
extern void screen2();
extern void screen3();
*/
//void screen1();
//void screen2();
/*
void init_external()
{
	//EXT0 for next screen
	IT0 = 1;
	EX0 = 1;
	
	//turn on 'global?' interrupts
	EA = 1;
	
	//EXT1 for backlight
	IT1 = 1;
	EX1 = 1;
	
	backlight = 0;	//Turn on display
}
*/
/*
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
	
}
*/
/*
//when physical button pushed
void backlightInterrupt() interrupt 2
{
	//turn on display
	backlight = 0;
	
	//set timer values
	TH1 = 0;
	TL1 = 0;
	
	//start timer 1
	TR1 = 1;
}
*/
/*
//runs when timer overruns
void backlightTimerInterrupt() interrupt 3
{
	//turn off backlight
	backlight = 1;

	//clear overflow
	TF1 = 0;
	//turn off timer
	TR1 = 0;
}
*/
//change so that it runs timer 2 to turn on/off
//TODO: start timer2 to run for 5 seconds in background
/*
void lcdBacklight() //interrupt 2
{
	//turn on display
	backlight = 0;
	
	//start timer 2 interrupt
	backlightInterrupt();
	//unsigned char i;
/*	
	if (comparator == 0)	//If light is not on aka night time
	{
		backlight = 0			//Sink current (pnp transistor)
		for(i = 0; i < 25; i++);
			ms_delay(200);		//5 second delay
		backlight = 1;			//Pull line high to turn off pnp transistor
	}
}
	*/

//if user wants to change screen
//only changes a bit to avoid potential problems
//with exiting whatver subroutine
/*
void nextScreen() interrupt 0
{
	interruptBit = 1;
}
*/