#include "LCD.h"
#include "DHT11.h"

void main()
{
	backlight = 0;
	
	init();
	
	while(1)
	{
		write_string("Hello, World!");
		//write_string("Test");
		//write_char('A',1);
	}
}