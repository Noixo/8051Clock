#include <reg51.h>
#include "LCD.h"

sbit RS = P0^0;
sbit E = P0^1;

sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;

sbit backlight = P2^3;
sbit lcd_button = P2^0;

//void Delay(int k);

void main()
{
	//D0 = P1^7;
	//backlight = 1;	//Set pin to detect high.
	
	while(1)
	{
		backlight_toggle();
		Delay(20);
		backlight_button();
	}
}