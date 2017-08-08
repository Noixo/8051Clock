#include "LCD.h"
#include "DHT11.h"

void main()
{
	while(1)
	{
		//backlight_toggle();
		//write_byte = ''; // Write char directly
		write_string("Hello, World!");
		//delay(20);
		//backlight_light();
	}
}