#include "external.h"
#include "timing.h"
#include "LCD.h"
//photoresistor


void check_night()
{
	if (comparator == 0)	//If night time
	{
		backlight = 1;	//Turn off LCD backlight
	}
	else
	{
		backlight = 0;			//When daytime turn on light
	}
}


void ex0_isr(void) interrupt 0
{
	unsigned char i;
	
	if (comparator == 0)	//If light is not on aka night time
	{
		backlight = 0;	//Sink current (pnp transistor)
		for(i = 0; i < 25; i++)
			ms_delay(200);	//5 second delay
		backlight = 1;	//Pull line high to turn off pnp transistor
	}
	//write_string("MAGIC IS HAPPENING");
}

void next_screen()
{
	/*
	if (next == 0)
	{
		//Go to next screen
	}
	*/
}
