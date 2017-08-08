#include "LCD.h"
#include "DHT11.h"

void main()
{
	backlight = 0;
	
	init();
	
	while(1)
	{
		write_char(0x80, 0);
		write_string("Hello, World!");
		write_char(0xC0, 0);
		//write_string("Test");
		//write_char('A',1);
	}
}

/*
	* Add timer
	* Add interupt
	* send screen clear command, start of init()
*/
