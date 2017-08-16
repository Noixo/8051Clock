#include "external.h"
#include "LCD.h"
#include "timing.h"
//photoresistor

void photo_resistor()
{
	if (comparator == 0)	//If night time
	{
		backlight == 1;
	}
	else
	{
		backlight == 0;			//When daytime turn on light
	}
}

void lcd_button_press()
{
	if (lcd_button == 0 && comparator == 1)
	{
		backlight == 1;
		ms_delay();
		backlight == 0;
	}
}

void next_screen()
{
	if (next == 0)
	{
		//Go to next screen
	}
}
