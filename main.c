//#include <reg51.h>
#include "LCD.h"

void main()
{
	//D0 = P1^7;
	//backlight = 1;	//Set pin to detect high.
	
	while(1)
	{
		//backlight_toggle();
		//write_byte = ''; // Write char directly
		write_string("Hello, World!");
		//delay(20);
		//backlight_light();
	}
}